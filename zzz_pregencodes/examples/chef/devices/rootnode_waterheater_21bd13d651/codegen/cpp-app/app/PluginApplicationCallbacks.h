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
void MatterThermostatPluginServerInitCallback();
void MatterWaterHeaterManagementPluginServerInitCallback();
void MatterWaterHeaterModePluginServerInitCallback();
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
void MatterThermostatPluginServerShutdownCallback();
void MatterWaterHeaterManagementPluginServerShutdownCallback();
void MatterWaterHeaterModePluginServerShutdownCallback();

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
    MatterNetworkCommissioningPluginServerInitCallback();                                                                          \
    MatterOperationalCredentialsPluginServerInitCallback();                                                                        \
    MatterThermostatPluginServerInitCallback();                                                                                    \
    MatterWaterHeaterManagementPluginServerInitCallback();                                                                         \
    MatterWaterHeaterModePluginServerInitCallback();

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
    MatterNetworkCommissioningPluginServerShutdownCallback();                                                                      \
    MatterOperationalCredentialsPluginServerShutdownCallback();                                                                    \
    MatterThermostatPluginServerShutdownCallback();                                                                                \
    MatterWaterHeaterManagementPluginServerShutdownCallback();                                                                     \
    MatterWaterHeaterModePluginServerShutdownCallback();
