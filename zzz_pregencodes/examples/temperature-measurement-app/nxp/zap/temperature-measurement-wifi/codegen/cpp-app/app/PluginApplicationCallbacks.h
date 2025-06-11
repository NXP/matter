#pragma once
void MatterAccessControlPluginServerInitCallback();
void MatterAdministratorCommissioningPluginServerInitCallback();
void MatterBasicInformationPluginServerInitCallback();
void MatterDescriptorPluginServerInitCallback();
void MatterFixedLabelPluginServerInitCallback();
void MatterGeneralCommissioningPluginServerInitCallback();
void MatterGeneralDiagnosticsPluginServerInitCallback();
void MatterGroupKeyManagementPluginServerInitCallback();
void MatterIdentifyPluginServerInitCallback();
void MatterLocalizationConfigurationPluginServerInitCallback();
void MatterNetworkCommissioningPluginServerInitCallback();
void MatterOperationalCredentialsPluginServerInitCallback();
void MatterOtaSoftwareUpdateRequestorPluginServerInitCallback();
void MatterTemperatureMeasurementPluginServerInitCallback();
void MatterTimeFormatLocalizationPluginServerInitCallback();
void MatterUnitLocalizationPluginServerInitCallback();
void MatterUserLabelPluginServerInitCallback();
void MatterWiFiNetworkDiagnosticsPluginServerInitCallback();

#define MATTER_PLUGINS_INIT \
    MatterAccessControlPluginServerInitCallback(); \
    MatterAdministratorCommissioningPluginServerInitCallback(); \
    MatterBasicInformationPluginServerInitCallback(); \
    MatterDescriptorPluginServerInitCallback(); \
    MatterFixedLabelPluginServerInitCallback(); \
    MatterGeneralCommissioningPluginServerInitCallback(); \
    MatterGeneralDiagnosticsPluginServerInitCallback(); \
    MatterGroupKeyManagementPluginServerInitCallback(); \
    MatterIdentifyPluginServerInitCallback(); \
    MatterLocalizationConfigurationPluginServerInitCallback(); \
    MatterNetworkCommissioningPluginServerInitCallback(); \
    MatterOperationalCredentialsPluginServerInitCallback(); \
    MatterOtaSoftwareUpdateRequestorPluginServerInitCallback(); \
    MatterTemperatureMeasurementPluginServerInitCallback(); \
    MatterTimeFormatLocalizationPluginServerInitCallback(); \
    MatterUnitLocalizationPluginServerInitCallback(); \
    MatterUserLabelPluginServerInitCallback(); \
    MatterWiFiNetworkDiagnosticsPluginServerInitCallback();

