#!/usr/bin/env bash
#
#
#    Copyright (c) 2023 Project CHIP Authors
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#        http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.
#

#
# The script to check or format source code of NXP Matter files.
#
# Format c/c++:
#
#     make-pretty.sh format
#
# Check only:
#
#     make-pretty.sh check
#

set -e

if [ -z ${PW_PROJECT_ROOT} ]; then
    MATTER_ROOT=$(dirname "$(readlink -f "$0")")/../../../
    source "$MATTER_ROOT/scripts/activate.sh"
fi

readonly BUILD_JOBS=$(getconf _NPROCESSORS_ONLN)
readonly INCLUDE_DIRS=(
    src/platform/nxp/common
    src/platform/nxp/k32w0
    src/platform/nxp/mcxw71_k32w1
    src/platform/nxp/rt
    src/platform/nxp/zephyr
    examples/all-clusters-app/nxp/common
    examples/all-clusters-app/nxp/rt
    examples/all-clusters-app/nxp/zephyr
    examples/contact-sensor-app/nxp/common
    examples/contact-sensor-app/nxp/k32w0
    examples/contact-sensor-app/nxp/k32w1
    examples/contact-sensor-app/nxp/mcxw71
    examples/lighting-app/nxp/common
    examples/lighting-app/nxp/k32w0
    examples/lighting-app/nxp/k32w1
    examples/lighting-app/nxp/mcxw71
    examples/platform/nxp/common
    examples/platform/nxp/k32w0
    examples/platform/nxp/mcxw71_k32w1
    examples/platform/nxp/pw_sys_io
    examples/platform/nxp/rt
    third_party/nxp
)
readonly CLANG_SOURCES=('*.c' '*.cpp' '*.h' '*.hpp')

do_clang_format()
{
    echo -e '========================================'
    echo -e '     format c/c++ (clang-format)'
    echo -e '========================================'

    echo "Formatting..."

    file_list=$(git ls-files "${CLANG_SOURCES[@]}" | grep -E "^($(echo "${INCLUDE_DIRS[@]}" | tr ' ' '|'))")
    # echo $file_list
    for i in $(echo $file_list); do
        echo $i
        clang-format -style=file -i $i
    done
    echo "Formatting done."
    echo "Checking git status:"
    echo

    git status
}

do_clang_format_check()
{
    echo -e '========================================'
    echo -e '     check c/c++ (clang-format)'
    echo -e '========================================'

    echo "Checking..."

    set +e
    git ls-files "${CLANG_SOURCES[@]}"                              \
        | grep -E "^($(echo "${INCLUDE_DIRS[@]}" | tr ' ' '|'))"    \
        | xargs -n3 -P"${BUILD_JOBS}" clang-format -style=file --dry-run --Werror
    error_code=$?
    set -e

    if [ "$error_code" == "0" ]; then
        echo "All files are formatted as expected."
    else
        echo "Formatting is required, run ./scripts/tools/nxp/make-pretty.sh to apply required formatting."
        exit $error_code
    fi
}

main()
{
    if [ $# == 0 ]; then
        do_clang_format
    elif [ "$1" == 'format' ]; then
        do_clang_format
    elif [ "$1" == 'check' ] || [ "$1" == 'pre-commit-check' ]; then
        do_clang_format_check $1
    else
        echo >&2 "Unsupported action: $1. Supported: format, check"
        # 128 for Invalid arguments
        exit 128
    fi
}

main "$@"
