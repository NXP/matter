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
void MatterModeSelectPluginServerInitCallback();
void MatterNetworkCommissioningPluginServerInitCallback();
void MatterOperationalCredentialsPluginServerInitCallback();
void MatterAccessControlPluginServerShutdownCallback();
void MatterAdministratorCommissioningPluginServerShutdownCallback();
void MatterBasicInformationPluginServerShutdownCallback();
void MatterDescriptorPluginServerShutdownCallback();
void MatterDiagnosticLogsPluginServerShutdownCallback();
void MatterGeneralCommissioningPluginServerShutdownCallback();
void MatterGeneralDiagnosticsPluginServerShutdownCallback();
void MatterGroupKeyManagementPluginServerShutdownCallback();
void MatterIdentifyPluginServerShutdownCallback();
void MatterModeSelectPluginServerShutdownCallback();
void MatterNetworkCommissioningPluginServerShutdownCallback();
void MatterOperationalCredentialsPluginServerShutdownCallback();

#define MATTER_PLUGINS_INIT                                                                                                        \
    MatterAccessControlPluginServerInitCallback();                                                                                 \
    MatterAdministratorCommissioningPluginServerInitCallback();                                                                    \
    MatterBasicInformationPluginServerInitCallback();                                                                              \
    MatterDescriptorPluginServerInitCallback();                                                                                    \
    MatterDiagnosticLogsPluginServerInitCallback();                                                                                \
    MatterGeneralCommissioningPluginServerInitCallback();                                                                          \
    MatterGeneralDiagnosticsPluginServerInitCallback();                                                                            \
    MatterGroupKeyManagementPluginServerInitCallback();                                                                            \
    MatterIdentifyPluginServerInitCallback();                                                                                      \
    MatterModeSelectPluginServerInitCallback();                                                                                    \
    MatterNetworkCommissioningPluginServerInitCallback();                                                                          \
    MatterOperationalCredentialsPluginServerInitCallback();

#define MATTER_PLUGINS_SHUTDOWN                                                                                                    \
    MatterAccessControlPluginServerShutdownCallback();                                                                             \
    MatterAdministratorCommissioningPluginServerShutdownCallback();                                                                \
    MatterBasicInformationPluginServerShutdownCallback();                                                                          \
    MatterDescriptorPluginServerShutdownCallback();                                                                                \
    MatterDiagnosticLogsPluginServerShutdownCallback();                                                                            \
    MatterGeneralCommissioningPluginServerShutdownCallback();                                                                      \
    MatterGeneralDiagnosticsPluginServerShutdownCallback();                                                                        \
    MatterGroupKeyManagementPluginServerShutdownCallback();                                                                        \
    MatterIdentifyPluginServerShutdownCallback();                                                                                  \
    MatterModeSelectPluginServerShutdownCallback();                                                                                \
    MatterNetworkCommissioningPluginServerShutdownCallback();                                                                      \
    MatterOperationalCredentialsPluginServerShutdownCallback();
