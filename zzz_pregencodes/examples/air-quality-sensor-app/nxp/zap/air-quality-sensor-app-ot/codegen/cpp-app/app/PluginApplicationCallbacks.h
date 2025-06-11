#pragma once
void MatterAccessControlPluginServerInitCallback();
void MatterAdministratorCommissioningPluginServerInitCallback();
void MatterAirQualityPluginServerInitCallback();
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
void MatterThreadNetworkDiagnosticsPluginServerInitCallback();
void MatterTimeFormatLocalizationPluginServerInitCallback();
void MatterUnitLocalizationPluginServerInitCallback();
void MatterUserLabelPluginServerInitCallback();

#define MATTER_PLUGINS_INIT \
    MatterAccessControlPluginServerInitCallback(); \
    MatterAdministratorCommissioningPluginServerInitCallback(); \
    MatterAirQualityPluginServerInitCallback(); \
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
    MatterThreadNetworkDiagnosticsPluginServerInitCallback(); \
    MatterTimeFormatLocalizationPluginServerInitCallback(); \
    MatterUnitLocalizationPluginServerInitCallback(); \
    MatterUserLabelPluginServerInitCallback();

