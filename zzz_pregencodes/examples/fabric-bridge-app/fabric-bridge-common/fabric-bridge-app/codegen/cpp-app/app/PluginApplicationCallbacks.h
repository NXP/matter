#pragma once
void MatterAccessControlPluginServerInitCallback();
void MatterAdministratorCommissioningPluginServerInitCallback();
void MatterBasicInformationPluginServerInitCallback();
void MatterCommissionerControlPluginServerInitCallback();
void MatterDescriptorPluginServerInitCallback();
void MatterDiagnosticLogsPluginServerInitCallback();
void MatterEthernetNetworkDiagnosticsPluginServerInitCallback();
void MatterGeneralCommissioningPluginServerInitCallback();
void MatterGeneralDiagnosticsPluginServerInitCallback();
void MatterGroupKeyManagementPluginServerInitCallback();
void MatterIdentifyPluginServerInitCallback();
void MatterNetworkCommissioningPluginServerInitCallback();
void MatterOperationalCredentialsPluginServerInitCallback();
void MatterSoftwareDiagnosticsPluginServerInitCallback();
void MatterThreadNetworkDiagnosticsPluginServerInitCallback();
void MatterWiFiNetworkDiagnosticsPluginServerInitCallback();
void MatterAccessControlPluginServerShutdownCallback();
void MatterAdministratorCommissioningPluginServerShutdownCallback();
void MatterBasicInformationPluginServerShutdownCallback();
void MatterCommissionerControlPluginServerShutdownCallback();
void MatterDescriptorPluginServerShutdownCallback();
void MatterDiagnosticLogsPluginServerShutdownCallback();
void MatterEthernetNetworkDiagnosticsPluginServerShutdownCallback();
void MatterGeneralCommissioningPluginServerShutdownCallback();
void MatterGeneralDiagnosticsPluginServerShutdownCallback();
void MatterGroupKeyManagementPluginServerShutdownCallback();
void MatterIdentifyPluginServerShutdownCallback();
void MatterNetworkCommissioningPluginServerShutdownCallback();
void MatterOperationalCredentialsPluginServerShutdownCallback();
void MatterSoftwareDiagnosticsPluginServerShutdownCallback();
void MatterThreadNetworkDiagnosticsPluginServerShutdownCallback();
void MatterWiFiNetworkDiagnosticsPluginServerShutdownCallback();

#define MATTER_PLUGINS_INIT \
    MatterAccessControlPluginServerInitCallback(); \
    MatterAdministratorCommissioningPluginServerInitCallback(); \
    MatterBasicInformationPluginServerInitCallback(); \
    MatterCommissionerControlPluginServerInitCallback(); \
    MatterDescriptorPluginServerInitCallback(); \
    MatterDiagnosticLogsPluginServerInitCallback(); \
    MatterEthernetNetworkDiagnosticsPluginServerInitCallback(); \
    MatterGeneralCommissioningPluginServerInitCallback(); \
    MatterGeneralDiagnosticsPluginServerInitCallback(); \
    MatterGroupKeyManagementPluginServerInitCallback(); \
    MatterIdentifyPluginServerInitCallback(); \
    MatterNetworkCommissioningPluginServerInitCallback(); \
    MatterOperationalCredentialsPluginServerInitCallback(); \
    MatterSoftwareDiagnosticsPluginServerInitCallback(); \
    MatterThreadNetworkDiagnosticsPluginServerInitCallback(); \
    MatterWiFiNetworkDiagnosticsPluginServerInitCallback();

#define MATTER_PLUGINS_SHUTDOWN \
    MatterAccessControlPluginServerShutdownCallback(); \
    MatterAdministratorCommissioningPluginServerShutdownCallback(); \
    MatterBasicInformationPluginServerShutdownCallback(); \
    MatterCommissionerControlPluginServerShutdownCallback(); \
    MatterDescriptorPluginServerShutdownCallback(); \
    MatterDiagnosticLogsPluginServerShutdownCallback(); \
    MatterEthernetNetworkDiagnosticsPluginServerShutdownCallback(); \
    MatterGeneralCommissioningPluginServerShutdownCallback(); \
    MatterGeneralDiagnosticsPluginServerShutdownCallback(); \
    MatterGroupKeyManagementPluginServerShutdownCallback(); \
    MatterIdentifyPluginServerShutdownCallback(); \
    MatterNetworkCommissioningPluginServerShutdownCallback(); \
    MatterOperationalCredentialsPluginServerShutdownCallback(); \
    MatterSoftwareDiagnosticsPluginServerShutdownCallback(); \
    MatterThreadNetworkDiagnosticsPluginServerShutdownCallback(); \
    MatterWiFiNetworkDiagnosticsPluginServerShutdownCallback();

