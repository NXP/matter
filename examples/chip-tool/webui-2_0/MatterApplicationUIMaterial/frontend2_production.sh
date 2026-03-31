#!/bin/bash
set -e
set -x

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BASE_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"
FRONTEND2_DIR="${BASE_DIR}/frontend2"
DIST_DIR="${SCRIPT_DIR}/dist/matter-application-uimaterial"

cd "${SCRIPT_DIR}"

npm install --legacy-peer-deps
ng build --configuration production

rm -rf "${FRONTEND2_DIR:?}"/*
cp "${DIST_DIR}/3rdpartylicenses.txt" "${FRONTEND2_DIR}/"
cp -r "${DIST_DIR}/browser/"* "${FRONTEND2_DIR}/"
