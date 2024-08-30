#
#   Copyright (c) 2024 Project CHIP Authors
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#

cmake_minimum_required(VERSION 3.30)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

get_filename_component(CHIP_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../../ REALPATH)
get_filename_component(GEN_DIR ${CHIP_ROOT}/zzz_generated/ REALPATH)
get_filename_component(OPENTHREAD_ROOT ${CHIP_ROOT}/third_party/openthread/repo REALPATH)

list(APPEND EXTRA_MCUX_MODULES ${CHIP_ROOT}/config/nxp/chip-cmake-freertos)

set(CONF_FILE ${CONF_FILE} ${CMAKE_CURRENT_SOURCE_DIR}/prj.conf)

set(KCONFIG_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/Kconfig)

find_package(McuxSDK 3.0.0)

# Get compiler flags and includes and pass them to CHIP target
list(APPEND CONFIG_CHIP_EXTERNAL_TARGETS McuxSDK)

get_filename_component(LIGHTING_APP_NXP_COMMON_DIR ${CHIP_ROOT}/examples/lighting-app/nxp/common REALPATH)
get_filename_component(LIGHTING_APP_NXP_PLATFORM_DIR ${CHIP_ROOT}/examples/lighting-app/nxp/${CONFIG_CHIP_NXP_APP_FOLDER_NAME} REALPATH)
get_filename_component(EXAMPLE_PLATFORM_NXP_COMMON_DIR ${CHIP_ROOT}/examples/platform/nxp/common REALPATH)
get_filename_component(EXAMPLE_PLATFORM_NXP_PLATFORM_DIR ${CHIP_ROOT}/examples/platform/nxp/${CONFIG_CHIP_NXP_PLATFORM_FOLDER_NAME} REALPATH)

if(EXISTS ${EXAMPLE_PLATFORM_NXP_PLATFORM_DIR}/util/LedOnOff.cpp)
    set(LED_ON_OFF_PATH ${EXAMPLE_PLATFORM_NXP_PLATFORM_DIR}/util/LedOnOff.cpp)
else()
    # Use the example provided by mcxw71_k32w1 platform until a better common solution is proposed.
    set(LED_ON_OFF_PATH ${EXAMPLE_PLATFORM_NXP_PLATFORM_DIR}/../mcxw71_k32w1/util/LedOnOff.cpp)
endif()

if(EXISTS ${EXAMPLE_PLATFORM_NXP_PLATFORM_DIR}/ota/OtaUtils.cpp)
    set(OTA_UTILS_PATH ${EXAMPLE_PLATFORM_NXP_PLATFORM_DIR}/ota/OtaUtils.cpp)
else()
    # Use the example provided by mcxw71_k32w1 platform until a common solution is proposed.
    set(OTA_UTILS_PATH ${EXAMPLE_PLATFORM_NXP_PLATFORM_DIR}/../mcxw71_k32w1/ota/OtaUtils.cpp)
endif()

# Include the nxp_sdk_reconfigure.cmake to customize the SDK for Matter application
include(${CHIP_ROOT}/third_party/nxp/nxp_matter_support/examples/platform/${CONFIG_CHIP_NXP_PLATFORM_FOLDER_NAME}/nxp_sdk_reconfig.cmake)

project(chip-nxp-lighting-app-example)

target_compile_definitions(app PRIVATE
    APP_QUEUE_TICKS_TO_WAIT=pdMS_TO_TICKS\(10\)
    EXTERNAL_FACTORY_DATA_PROVIDER_HEADER=\"platform/nxp/common/factory_data/legacy/FactoryDataProvider.h\"
    EXTERNAL_BLEMANAGERIMPL_HEADER=\"platform/nxp/${CONFIG_CHIP_NXP_PLATFORM_FOLDER_NAME}/BLEManagerImpl.h\"
)

if (CONFIG_CHIP_OTA_REQUESTOR AND (CONFIG_CHIP_NXP_PLATFORM_K32W1 OR CONFIG_CHIP_NXP_PLATFORM_MCXW71))
    target_compile_definitions(app PRIVATE
        # The status LED and the external flash CS pin are wired together. The OTA image writing may fail if used together.
        LED_MANAGER_ENABLE_STATUS_LED=0
    )
endif()

#**********************************************************
# Add Application files to the build
include(${CHIP_ROOT}/src/app/chip_data_model.cmake)

target_include_directories(app
    PRIVATE
    ${LIGHTING_APP_NXP_COMMON_DIR}
    ${LIGHTING_APP_NXP_COMMON_DIR}/include
    ${LIGHTING_APP_NXP_PLATFORM_DIR}/include/config
    ${EXAMPLE_PLATFORM_NXP_COMMON_DIR}/app_task/include
    ${EXAMPLE_PLATFORM_NXP_COMMON_DIR}/matter_button/include
    ${EXAMPLE_PLATFORM_NXP_COMMON_DIR}/clusters/include
    ${EXAMPLE_PLATFORM_NXP_COMMON_DIR}/device_callbacks/include
    ${EXAMPLE_PLATFORM_NXP_COMMON_DIR}/device_manager/include
    ${EXAMPLE_PLATFORM_NXP_COMMON_DIR}/factory_data/include
    ${EXAMPLE_PLATFORM_NXP_COMMON_DIR}/led_widget/include
    ${EXAMPLE_PLATFORM_NXP_COMMON_DIR}/operational_keystore/include
    ${EXAMPLE_PLATFORM_NXP_COMMON_DIR}/rpc/include
    ${EXAMPLE_PLATFORM_NXP_COMMON_DIR}/ui_feedback/include
    ${EXAMPLE_PLATFORM_NXP_COMMON_DIR}/app_ble/include
    ${GEN_DIR}/app-common
)

target_sources(app
    PRIVATE
    ${LIGHTING_APP_NXP_COMMON_DIR}/AppTask.cpp
    ${LIGHTING_APP_NXP_COMMON_DIR}/DeviceCallbacks.cpp
    ${LIGHTING_APP_NXP_COMMON_DIR}/main.cpp
    ${EXAMPLE_PLATFORM_NXP_COMMON_DIR}/app_ble/source/BLEApplicationManagerEmpty.cpp
    ${EXAMPLE_PLATFORM_NXP_COMMON_DIR}/app_task/source/AppTaskBase.cpp
    ${EXAMPLE_PLATFORM_NXP_COMMON_DIR}/app_task/source/AppTaskFreeRTOS.cpp
    ${EXAMPLE_PLATFORM_NXP_COMMON_DIR}/clusters/source/ZclCallbacks.cpp
    ${EXAMPLE_PLATFORM_NXP_COMMON_DIR}/device_callbacks/source/CommonDeviceCallbacks.cpp
    ${EXAMPLE_PLATFORM_NXP_COMMON_DIR}/device_manager/source/CHIPDeviceManager.cpp
    ${EXAMPLE_PLATFORM_NXP_COMMON_DIR}/matter_button/source/ButtonApp.cpp
    ${EXAMPLE_PLATFORM_NXP_COMMON_DIR}/matter_button/source/ButtonBle.cpp
    ${EXAMPLE_PLATFORM_NXP_COMMON_DIR}/matter_button/source/ButtonManager.cpp
    ${EXAMPLE_PLATFORM_NXP_COMMON_DIR}/matter_button/source/ButtonRegistrationAppAndBle.cpp
    ${EXAMPLE_PLATFORM_NXP_COMMON_DIR}/matter_button/source/ButtonWithTimer.cpp
    ${EXAMPLE_PLATFORM_NXP_COMMON_DIR}/operational_keystore/source/OperationalKeystoreS200.cpp
    ${EXAMPLE_PLATFORM_NXP_COMMON_DIR}/ui_feedback/source/LedManager.cpp
    ${LED_ON_OFF_PATH}
)

# TODO: remove this workaround and use a file from default implementation
if(CONFIG_CHIP_NXP_PLATFORM_MCXW72)
    target_sources(app
        PRIVATE
        ${EXAMPLE_PLATFORM_NXP_COMMON_DIR}/factory_data/source/AppFactoryDataDefaultImpl.cpp
    )
else()
    # Maybe this special case should be removed and use the default implementation from common code.
    target_sources(app
        PRIVATE
        ${EXAMPLE_PLATFORM_NXP_PLATFORM_DIR}/factory_data/source/AppFactoryDataExample.cpp
    )
endif()


if(CONFIG_CHIP_OTA_REQUESTOR)
    target_include_directories(app
        PRIVATE
        ${EXAMPLE_PLATFORM_NXP_COMMON_DIR}/ota_requestor/include
    )

    target_sources(app
        PRIVATE
        ${EXAMPLE_PLATFORM_NXP_COMMON_DIR}/ota_requestor/source/OTARequestorInitiatorMultiImage.cpp
        ${OTA_UTILS_PATH}
    )
endif()

chip_configure_data_model(app
    INCLUDE_SERVER
    ZAP_FILE ${LIGHTING_APP_NXP_COMMON_DIR}/../zap/lighting-on-off.zap
)
