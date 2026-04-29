#pragma once
void MatterAccessControlPluginServerInitCallback();
void MatterAdministratorCommissioningPluginServerInitCallback();
void MatterBasicInformationPluginServerInitCallback();
void MatterChimePluginServerInitCallback();
void MatterDescriptorPluginServerInitCallback();
void MatterDiagnosticLogsPluginServerInitCallback();
void MatterGeneralCommissioningPluginServerInitCallback();
void MatterGeneralDiagnosticsPluginServerInitCallback();
void MatterGroupKeyManagementPluginServerInitCallback();
void MatterIdentifyPluginServerInitCallback();
void MatterNetworkCommissioningPluginServerInitCallback();
void MatterOperationalCredentialsPluginServerInitCallback();
void MatterAccessControlPluginServerShutdownCallback();
void MatterAdministratorCommissioningPluginServerShutdownCallback();
void MatterBasicInformationPluginServerShutdownCallback();
void MatterChimePluginServerShutdownCallback();
void MatterDescriptorPluginServerShutdownCallback();
void MatterDiagnosticLogsPluginServerShutdownCallback();
void MatterGeneralCommissioningPluginServerShutdownCallback();
void MatterGeneralDiagnosticsPluginServerShutdownCallback();
void MatterGroupKeyManagementPluginServerShutdownCallback();
void MatterIdentifyPluginServerShutdownCallback();
void MatterNetworkCommissioningPluginServerShutdownCallback();
void MatterOperationalCredentialsPluginServerShutdownCallback();

#define MATTER_PLUGINS_INIT                                                                                                        \
    MatterAccessControlPluginServerInitCallback();                                                                                 \
    MatterAdministratorCommissioningPluginServerInitCallback();                                                                    \
    MatterBasicInformationPluginServerInitCallback();                                                                              \
    MatterChimePluginServerInitCallback();                                                                                         \
    MatterDescriptorPluginServerInitCallback();                                                                                    \
    MatterDiagnosticLogsPluginServerInitCallback();                                                                                \
    MatterGeneralCommissioningPluginServerInitCallback();                                                                          \
    MatterGeneralDiagnosticsPluginServerInitCallback();                                                                            \
    MatterGroupKeyManagementPluginServerInitCallback();                                                                            \
    MatterIdentifyPluginServerInitCallback();                                                                                      \
    MatterNetworkCommissioningPluginServerInitCallback();                                                                          \
    MatterOperationalCredentialsPluginServerInitCallback();

#define MATTER_PLUGINS_SHUTDOWN                                                                                                    \
    MatterAccessControlPluginServerShutdownCallback();                                                                             \
    MatterAdministratorCommissioningPluginServerShutdownCallback();                                                                \
    MatterBasicInformationPluginServerShutdownCallback();                                                                          \
    MatterChimePluginServerShutdownCallback();                                                                                     \
    MatterDescriptorPluginServerShutdownCallback();                                                                                \
    MatterDiagnosticLogsPluginServerShutdownCallback();                                                                            \
    MatterGeneralCommissioningPluginServerShutdownCallback();                                                                      \
    MatterGeneralDiagnosticsPluginServerShutdownCallback();                                                                        \
    MatterGroupKeyManagementPluginServerShutdownCallback();                                                                        \
    MatterIdentifyPluginServerShutdownCallback();                                                                                  \
    MatterNetworkCommissioningPluginServerShutdownCallback();                                                                      \
    MatterOperationalCredentialsPluginServerShutdownCallback();
