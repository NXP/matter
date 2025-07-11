#pragma once
void MatterAccessControlPluginServerInitCallback();
void MatterDiagnosticLogsPluginServerInitCallback();
void MatterGeneralCommissioningPluginServerInitCallback();
void MatterNetworkCommissioningPluginServerInitCallback();
void MatterOperationalCredentialsPluginServerInitCallback();
void MatterAccessControlPluginServerShutdownCallback();
void MatterDiagnosticLogsPluginServerShutdownCallback();
void MatterGeneralCommissioningPluginServerShutdownCallback();
void MatterNetworkCommissioningPluginServerShutdownCallback();
void MatterOperationalCredentialsPluginServerShutdownCallback();

#define MATTER_PLUGINS_INIT \
    MatterAccessControlPluginServerInitCallback(); \
    MatterDiagnosticLogsPluginServerInitCallback(); \
    MatterGeneralCommissioningPluginServerInitCallback(); \
    MatterNetworkCommissioningPluginServerInitCallback(); \
    MatterOperationalCredentialsPluginServerInitCallback();

#define MATTER_PLUGINS_SHUTDOWN \
    MatterAccessControlPluginServerShutdownCallback(); \
    MatterDiagnosticLogsPluginServerShutdownCallback(); \
    MatterGeneralCommissioningPluginServerShutdownCallback(); \
    MatterNetworkCommissioningPluginServerShutdownCallback(); \
    MatterOperationalCredentialsPluginServerShutdownCallback();

