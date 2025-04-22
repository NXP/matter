#pragma once
void MatterAccessControlPluginServerInitCallback();
void MatterAdministratorCommissioningPluginServerInitCallback();
void MatterBasicInformationPluginServerInitCallback();
void MatterDescriptorPluginServerInitCallback();
void MatterDeviceEnergyManagementPluginServerInitCallback();
void MatterDeviceEnergyManagementModePluginServerInitCallback();
void MatterGeneralCommissioningPluginServerInitCallback();
void MatterGeneralDiagnosticsPluginServerInitCallback();
void MatterGroupKeyManagementPluginServerInitCallback();
void MatterIdentifyPluginServerInitCallback();
void MatterLocalizationConfigurationPluginServerInitCallback();
void MatterNetworkCommissioningPluginServerInitCallback();
void MatterOperationalCredentialsPluginServerInitCallback();
void MatterPowerSourcePluginServerInitCallback();
void MatterThermostatPluginServerInitCallback();
void MatterTimeFormatLocalizationPluginServerInitCallback();
void MatterUnitLocalizationPluginServerInitCallback();
void MatterWaterHeaterManagementPluginServerInitCallback();
void MatterWaterHeaterModePluginServerInitCallback();
void MatterWiFiNetworkDiagnosticsPluginServerInitCallback();

#define MATTER_PLUGINS_INIT \
    MatterAccessControlPluginServerInitCallback(); \
    MatterAdministratorCommissioningPluginServerInitCallback(); \
    MatterBasicInformationPluginServerInitCallback(); \
    MatterDescriptorPluginServerInitCallback(); \
    MatterDeviceEnergyManagementPluginServerInitCallback(); \
    MatterDeviceEnergyManagementModePluginServerInitCallback(); \
    MatterGeneralCommissioningPluginServerInitCallback(); \
    MatterGeneralDiagnosticsPluginServerInitCallback(); \
    MatterGroupKeyManagementPluginServerInitCallback(); \
    MatterIdentifyPluginServerInitCallback(); \
    MatterLocalizationConfigurationPluginServerInitCallback(); \
    MatterNetworkCommissioningPluginServerInitCallback(); \
    MatterOperationalCredentialsPluginServerInitCallback(); \
    MatterPowerSourcePluginServerInitCallback(); \
    MatterThermostatPluginServerInitCallback(); \
    MatterTimeFormatLocalizationPluginServerInitCallback(); \
    MatterUnitLocalizationPluginServerInitCallback(); \
    MatterWaterHeaterManagementPluginServerInitCallback(); \
    MatterWaterHeaterModePluginServerInitCallback(); \
    MatterWiFiNetworkDiagnosticsPluginServerInitCallback();

