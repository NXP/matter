#pragma once
void MatterAccessControlPluginServerInitCallback();
void MatterAdministratorCommissioningPluginServerInitCallback();
void MatterBasicInformationPluginServerInitCallback();
void MatterCommodityPricePluginServerInitCallback();
void MatterDescriptorPluginServerInitCallback();
void MatterElectricalGridConditionsPluginServerInitCallback();
void MatterGeneralCommissioningPluginServerInitCallback();
void MatterGeneralDiagnosticsPluginServerInitCallback();
void MatterGroupKeyManagementPluginServerInitCallback();
void MatterIdentifyPluginServerInitCallback();
void MatterLocalizationConfigurationPluginServerInitCallback();
void MatterMeterIdentificationPluginServerInitCallback();
void MatterNetworkCommissioningPluginServerInitCallback();
void MatterOperationalCredentialsPluginServerInitCallback();
void MatterOtaSoftwareUpdateRequestorPluginServerInitCallback();
void MatterUnitLocalizationPluginServerInitCallback();
void MatterAccessControlPluginServerShutdownCallback();
void MatterAdministratorCommissioningPluginServerShutdownCallback();
void MatterBasicInformationPluginServerShutdownCallback();
void MatterCommodityPricePluginServerShutdownCallback();
void MatterDescriptorPluginServerShutdownCallback();
void MatterElectricalGridConditionsPluginServerShutdownCallback();
void MatterGeneralCommissioningPluginServerShutdownCallback();
void MatterGeneralDiagnosticsPluginServerShutdownCallback();
void MatterGroupKeyManagementPluginServerShutdownCallback();
void MatterIdentifyPluginServerShutdownCallback();
void MatterLocalizationConfigurationPluginServerShutdownCallback();
void MatterMeterIdentificationPluginServerShutdownCallback();
void MatterNetworkCommissioningPluginServerShutdownCallback();
void MatterOperationalCredentialsPluginServerShutdownCallback();
void MatterOtaSoftwareUpdateRequestorPluginServerShutdownCallback();
void MatterUnitLocalizationPluginServerShutdownCallback();

#define MATTER_PLUGINS_INIT \
    MatterAccessControlPluginServerInitCallback(); \
    MatterAdministratorCommissioningPluginServerInitCallback(); \
    MatterBasicInformationPluginServerInitCallback(); \
    MatterCommodityPricePluginServerInitCallback(); \
    MatterDescriptorPluginServerInitCallback(); \
    MatterElectricalGridConditionsPluginServerInitCallback(); \
    MatterGeneralCommissioningPluginServerInitCallback(); \
    MatterGeneralDiagnosticsPluginServerInitCallback(); \
    MatterGroupKeyManagementPluginServerInitCallback(); \
    MatterIdentifyPluginServerInitCallback(); \
    MatterLocalizationConfigurationPluginServerInitCallback(); \
    MatterMeterIdentificationPluginServerInitCallback(); \
    MatterNetworkCommissioningPluginServerInitCallback(); \
    MatterOperationalCredentialsPluginServerInitCallback(); \
    MatterOtaSoftwareUpdateRequestorPluginServerInitCallback(); \
    MatterUnitLocalizationPluginServerInitCallback();

#define MATTER_PLUGINS_SHUTDOWN \
    MatterAccessControlPluginServerShutdownCallback(); \
    MatterAdministratorCommissioningPluginServerShutdownCallback(); \
    MatterBasicInformationPluginServerShutdownCallback(); \
    MatterCommodityPricePluginServerShutdownCallback(); \
    MatterDescriptorPluginServerShutdownCallback(); \
    MatterElectricalGridConditionsPluginServerShutdownCallback(); \
    MatterGeneralCommissioningPluginServerShutdownCallback(); \
    MatterGeneralDiagnosticsPluginServerShutdownCallback(); \
    MatterGroupKeyManagementPluginServerShutdownCallback(); \
    MatterIdentifyPluginServerShutdownCallback(); \
    MatterLocalizationConfigurationPluginServerShutdownCallback(); \
    MatterMeterIdentificationPluginServerShutdownCallback(); \
    MatterNetworkCommissioningPluginServerShutdownCallback(); \
    MatterOperationalCredentialsPluginServerShutdownCallback(); \
    MatterOtaSoftwareUpdateRequestorPluginServerShutdownCallback(); \
    MatterUnitLocalizationPluginServerShutdownCallback();

