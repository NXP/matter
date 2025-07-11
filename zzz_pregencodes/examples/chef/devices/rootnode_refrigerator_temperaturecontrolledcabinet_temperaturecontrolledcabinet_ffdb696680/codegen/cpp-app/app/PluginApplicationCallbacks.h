#pragma once
void MatterAccessControlPluginServerInitCallback();
void MatterAdministratorCommissioningPluginServerInitCallback();
void MatterBasicInformationPluginServerInitCallback();
void MatterDescriptorPluginServerInitCallback();
void MatterGeneralCommissioningPluginServerInitCallback();
void MatterGeneralDiagnosticsPluginServerInitCallback();
void MatterGroupKeyManagementPluginServerInitCallback();
void MatterNetworkCommissioningPluginServerInitCallback();
void MatterOperationalCredentialsPluginServerInitCallback();
void MatterRefrigeratorAlarmPluginServerInitCallback();
void MatterRefrigeratorAndTemperatureControlledCabinetModePluginServerInitCallback();
void MatterTemperatureControlPluginServerInitCallback();
void MatterTemperatureMeasurementPluginServerInitCallback();
void MatterUnitLocalizationPluginServerInitCallback();
void MatterWiFiNetworkDiagnosticsPluginServerInitCallback();
void MatterAccessControlPluginServerShutdownCallback();
void MatterAdministratorCommissioningPluginServerShutdownCallback();
void MatterBasicInformationPluginServerShutdownCallback();
void MatterDescriptorPluginServerShutdownCallback();
void MatterGeneralCommissioningPluginServerShutdownCallback();
void MatterGeneralDiagnosticsPluginServerShutdownCallback();
void MatterGroupKeyManagementPluginServerShutdownCallback();
void MatterNetworkCommissioningPluginServerShutdownCallback();
void MatterOperationalCredentialsPluginServerShutdownCallback();
void MatterRefrigeratorAlarmPluginServerShutdownCallback();
void MatterRefrigeratorAndTemperatureControlledCabinetModePluginServerShutdownCallback();
void MatterTemperatureControlPluginServerShutdownCallback();
void MatterTemperatureMeasurementPluginServerShutdownCallback();
void MatterUnitLocalizationPluginServerShutdownCallback();
void MatterWiFiNetworkDiagnosticsPluginServerShutdownCallback();

#define MATTER_PLUGINS_INIT \
    MatterAccessControlPluginServerInitCallback(); \
    MatterAdministratorCommissioningPluginServerInitCallback(); \
    MatterBasicInformationPluginServerInitCallback(); \
    MatterDescriptorPluginServerInitCallback(); \
    MatterGeneralCommissioningPluginServerInitCallback(); \
    MatterGeneralDiagnosticsPluginServerInitCallback(); \
    MatterGroupKeyManagementPluginServerInitCallback(); \
    MatterNetworkCommissioningPluginServerInitCallback(); \
    MatterOperationalCredentialsPluginServerInitCallback(); \
    MatterRefrigeratorAlarmPluginServerInitCallback(); \
    MatterRefrigeratorAndTemperatureControlledCabinetModePluginServerInitCallback(); \
    MatterTemperatureControlPluginServerInitCallback(); \
    MatterTemperatureMeasurementPluginServerInitCallback(); \
    MatterUnitLocalizationPluginServerInitCallback(); \
    MatterWiFiNetworkDiagnosticsPluginServerInitCallback();

#define MATTER_PLUGINS_SHUTDOWN \
    MatterAccessControlPluginServerShutdownCallback(); \
    MatterAdministratorCommissioningPluginServerShutdownCallback(); \
    MatterBasicInformationPluginServerShutdownCallback(); \
    MatterDescriptorPluginServerShutdownCallback(); \
    MatterGeneralCommissioningPluginServerShutdownCallback(); \
    MatterGeneralDiagnosticsPluginServerShutdownCallback(); \
    MatterGroupKeyManagementPluginServerShutdownCallback(); \
    MatterNetworkCommissioningPluginServerShutdownCallback(); \
    MatterOperationalCredentialsPluginServerShutdownCallback(); \
    MatterRefrigeratorAlarmPluginServerShutdownCallback(); \
    MatterRefrigeratorAndTemperatureControlledCabinetModePluginServerShutdownCallback(); \
    MatterTemperatureControlPluginServerShutdownCallback(); \
    MatterTemperatureMeasurementPluginServerShutdownCallback(); \
    MatterUnitLocalizationPluginServerShutdownCallback(); \
    MatterWiFiNetworkDiagnosticsPluginServerShutdownCallback();

