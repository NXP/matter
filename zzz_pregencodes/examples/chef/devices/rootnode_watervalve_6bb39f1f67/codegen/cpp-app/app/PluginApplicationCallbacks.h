#pragma once
void MatterAccessControlPluginServerInitCallback();
void MatterAdministratorCommissioningPluginServerInitCallback();
void MatterBasicInformationPluginServerInitCallback();
void MatterDescriptorPluginServerInitCallback();
void MatterDiagnosticLogsPluginServerInitCallback();
void MatterGeneralCommissioningPluginServerInitCallback();
void MatterGeneralDiagnosticsPluginServerInitCallback();
void MatterGroupKeyManagementPluginServerInitCallback();
void MatterIdentifyPluginServerInitCallback();
void MatterNetworkCommissioningPluginServerInitCallback();
void MatterOperationalCredentialsPluginServerInitCallback();
void MatterPowerSourcePluginServerInitCallback();
void MatterValveConfigurationAndControlPluginServerInitCallback();
void MatterAccessControlPluginServerShutdownCallback();
void MatterAdministratorCommissioningPluginServerShutdownCallback();
void MatterBasicInformationPluginServerShutdownCallback();
void MatterDescriptorPluginServerShutdownCallback();
void MatterDiagnosticLogsPluginServerShutdownCallback();
void MatterGeneralCommissioningPluginServerShutdownCallback();
void MatterGeneralDiagnosticsPluginServerShutdownCallback();
void MatterGroupKeyManagementPluginServerShutdownCallback();
void MatterIdentifyPluginServerShutdownCallback();
void MatterNetworkCommissioningPluginServerShutdownCallback();
void MatterOperationalCredentialsPluginServerShutdownCallback();
void MatterPowerSourcePluginServerShutdownCallback();
void MatterValveConfigurationAndControlPluginServerShutdownCallback();

#define MATTER_PLUGINS_INIT \
    MatterAccessControlPluginServerInitCallback(); \
    MatterAdministratorCommissioningPluginServerInitCallback(); \
    MatterBasicInformationPluginServerInitCallback(); \
    MatterDescriptorPluginServerInitCallback(); \
    MatterDiagnosticLogsPluginServerInitCallback(); \
    MatterGeneralCommissioningPluginServerInitCallback(); \
    MatterGeneralDiagnosticsPluginServerInitCallback(); \
    MatterGroupKeyManagementPluginServerInitCallback(); \
    MatterIdentifyPluginServerInitCallback(); \
    MatterNetworkCommissioningPluginServerInitCallback(); \
    MatterOperationalCredentialsPluginServerInitCallback(); \
    MatterPowerSourcePluginServerInitCallback(); \
    MatterValveConfigurationAndControlPluginServerInitCallback();

#define MATTER_PLUGINS_SHUTDOWN \
    MatterAccessControlPluginServerShutdownCallback(); \
    MatterAdministratorCommissioningPluginServerShutdownCallback(); \
    MatterBasicInformationPluginServerShutdownCallback(); \
    MatterDescriptorPluginServerShutdownCallback(); \
    MatterDiagnosticLogsPluginServerShutdownCallback(); \
    MatterGeneralCommissioningPluginServerShutdownCallback(); \
    MatterGeneralDiagnosticsPluginServerShutdownCallback(); \
    MatterGroupKeyManagementPluginServerShutdownCallback(); \
    MatterIdentifyPluginServerShutdownCallback(); \
    MatterNetworkCommissioningPluginServerShutdownCallback(); \
    MatterOperationalCredentialsPluginServerShutdownCallback(); \
    MatterPowerSourcePluginServerShutdownCallback(); \
    MatterValveConfigurationAndControlPluginServerShutdownCallback();

