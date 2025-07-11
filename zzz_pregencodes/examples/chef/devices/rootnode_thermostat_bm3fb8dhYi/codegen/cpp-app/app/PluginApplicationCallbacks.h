#pragma once
void MatterAccessControlPluginServerInitCallback();
void MatterAdministratorCommissioningPluginServerInitCallback();
void MatterBasicInformationPluginServerInitCallback();
void MatterDescriptorPluginServerInitCallback();
void MatterDiagnosticLogsPluginServerInitCallback();
void MatterGeneralCommissioningPluginServerInitCallback();
void MatterGeneralDiagnosticsPluginServerInitCallback();
void MatterGroupKeyManagementPluginServerInitCallback();
void MatterGroupsPluginServerInitCallback();
void MatterIdentifyPluginServerInitCallback();
void MatterLocalizationConfigurationPluginServerInitCallback();
void MatterNetworkCommissioningPluginServerInitCallback();
void MatterOperationalCredentialsPluginServerInitCallback();
void MatterOtaSoftwareUpdateRequestorPluginServerInitCallback();
void MatterSoftwareDiagnosticsPluginServerInitCallback();
void MatterThermostatPluginServerInitCallback();
void MatterThermostatUserInterfaceConfigurationPluginServerInitCallback();
void MatterAccessControlPluginServerShutdownCallback();
void MatterAdministratorCommissioningPluginServerShutdownCallback();
void MatterBasicInformationPluginServerShutdownCallback();
void MatterDescriptorPluginServerShutdownCallback();
void MatterDiagnosticLogsPluginServerShutdownCallback();
void MatterGeneralCommissioningPluginServerShutdownCallback();
void MatterGeneralDiagnosticsPluginServerShutdownCallback();
void MatterGroupKeyManagementPluginServerShutdownCallback();
void MatterGroupsPluginServerShutdownCallback();
void MatterIdentifyPluginServerShutdownCallback();
void MatterLocalizationConfigurationPluginServerShutdownCallback();
void MatterNetworkCommissioningPluginServerShutdownCallback();
void MatterOperationalCredentialsPluginServerShutdownCallback();
void MatterOtaSoftwareUpdateRequestorPluginServerShutdownCallback();
void MatterSoftwareDiagnosticsPluginServerShutdownCallback();
void MatterThermostatPluginServerShutdownCallback();
void MatterThermostatUserInterfaceConfigurationPluginServerShutdownCallback();

#define MATTER_PLUGINS_INIT \
    MatterAccessControlPluginServerInitCallback(); \
    MatterAdministratorCommissioningPluginServerInitCallback(); \
    MatterBasicInformationPluginServerInitCallback(); \
    MatterDescriptorPluginServerInitCallback(); \
    MatterDiagnosticLogsPluginServerInitCallback(); \
    MatterGeneralCommissioningPluginServerInitCallback(); \
    MatterGeneralDiagnosticsPluginServerInitCallback(); \
    MatterGroupKeyManagementPluginServerInitCallback(); \
    MatterGroupsPluginServerInitCallback(); \
    MatterIdentifyPluginServerInitCallback(); \
    MatterLocalizationConfigurationPluginServerInitCallback(); \
    MatterNetworkCommissioningPluginServerInitCallback(); \
    MatterOperationalCredentialsPluginServerInitCallback(); \
    MatterOtaSoftwareUpdateRequestorPluginServerInitCallback(); \
    MatterSoftwareDiagnosticsPluginServerInitCallback(); \
    MatterThermostatPluginServerInitCallback(); \
    MatterThermostatUserInterfaceConfigurationPluginServerInitCallback();

#define MATTER_PLUGINS_SHUTDOWN \
    MatterAccessControlPluginServerShutdownCallback(); \
    MatterAdministratorCommissioningPluginServerShutdownCallback(); \
    MatterBasicInformationPluginServerShutdownCallback(); \
    MatterDescriptorPluginServerShutdownCallback(); \
    MatterDiagnosticLogsPluginServerShutdownCallback(); \
    MatterGeneralCommissioningPluginServerShutdownCallback(); \
    MatterGeneralDiagnosticsPluginServerShutdownCallback(); \
    MatterGroupKeyManagementPluginServerShutdownCallback(); \
    MatterGroupsPluginServerShutdownCallback(); \
    MatterIdentifyPluginServerShutdownCallback(); \
    MatterLocalizationConfigurationPluginServerShutdownCallback(); \
    MatterNetworkCommissioningPluginServerShutdownCallback(); \
    MatterOperationalCredentialsPluginServerShutdownCallback(); \
    MatterOtaSoftwareUpdateRequestorPluginServerShutdownCallback(); \
    MatterSoftwareDiagnosticsPluginServerShutdownCallback(); \
    MatterThermostatPluginServerShutdownCallback(); \
    MatterThermostatUserInterfaceConfigurationPluginServerShutdownCallback();

