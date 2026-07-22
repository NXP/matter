#pragma once
void MatterAccessControlPluginServerInitCallback();
void MatterAdministratorCommissioningPluginServerInitCallback();
void MatterBasicInformationPluginServerInitCallback();
void MatterDescriptorPluginServerInitCallback();
void MatterGeneralCommissioningPluginServerInitCallback();
void MatterGeneralDiagnosticsPluginServerInitCallback();
void MatterGroupKeyManagementPluginServerInitCallback();
void MatterNetworkCommissioningPluginServerInitCallback();
void MatterNetworkIdentityManagementPluginServerInitCallback();
void MatterOperationalCredentialsPluginServerInitCallback();
void MatterThreadBorderRouterManagementPluginServerInitCallback();
void MatterThreadNetworkDiagnosticsPluginServerInitCallback();
void MatterThreadNetworkDirectoryPluginServerInitCallback();
void MatterWiFiNetworkManagementPluginServerInitCallback();
void MatterAccessControlPluginServerShutdownCallback();
void MatterAdministratorCommissioningPluginServerShutdownCallback();
void MatterBasicInformationPluginServerShutdownCallback();
void MatterDescriptorPluginServerShutdownCallback();
void MatterGeneralCommissioningPluginServerShutdownCallback();
void MatterGeneralDiagnosticsPluginServerShutdownCallback();
void MatterGroupKeyManagementPluginServerShutdownCallback();
void MatterNetworkCommissioningPluginServerShutdownCallback();
void MatterNetworkIdentityManagementPluginServerShutdownCallback();
void MatterOperationalCredentialsPluginServerShutdownCallback();
void MatterThreadBorderRouterManagementPluginServerShutdownCallback();
void MatterThreadNetworkDiagnosticsPluginServerShutdownCallback();
void MatterThreadNetworkDirectoryPluginServerShutdownCallback();
void MatterWiFiNetworkManagementPluginServerShutdownCallback();

#define MATTER_PLUGINS_INIT                                                                                                        \
    MatterAccessControlPluginServerInitCallback();                                                                                 \
    MatterAdministratorCommissioningPluginServerInitCallback();                                                                    \
    MatterBasicInformationPluginServerInitCallback();                                                                              \
    MatterDescriptorPluginServerInitCallback();                                                                                    \
    MatterGeneralCommissioningPluginServerInitCallback();                                                                          \
    MatterGeneralDiagnosticsPluginServerInitCallback();                                                                            \
    MatterGroupKeyManagementPluginServerInitCallback();                                                                            \
    MatterNetworkCommissioningPluginServerInitCallback();                                                                          \
    MatterNetworkIdentityManagementPluginServerInitCallback();                                                                     \
    MatterOperationalCredentialsPluginServerInitCallback();                                                                        \
    MatterThreadBorderRouterManagementPluginServerInitCallback();                                                                  \
    MatterThreadNetworkDiagnosticsPluginServerInitCallback();                                                                      \
    MatterThreadNetworkDirectoryPluginServerInitCallback();                                                                        \
    MatterWiFiNetworkManagementPluginServerInitCallback();

#define MATTER_PLUGINS_SHUTDOWN                                                                                                    \
    MatterAccessControlPluginServerShutdownCallback();                                                                             \
    MatterAdministratorCommissioningPluginServerShutdownCallback();                                                                \
    MatterBasicInformationPluginServerShutdownCallback();                                                                          \
    MatterDescriptorPluginServerShutdownCallback();                                                                                \
    MatterGeneralCommissioningPluginServerShutdownCallback();                                                                      \
    MatterGeneralDiagnosticsPluginServerShutdownCallback();                                                                        \
    MatterGroupKeyManagementPluginServerShutdownCallback();                                                                        \
    MatterNetworkCommissioningPluginServerShutdownCallback();                                                                      \
    MatterNetworkIdentityManagementPluginServerShutdownCallback();                                                                 \
    MatterOperationalCredentialsPluginServerShutdownCallback();                                                                    \
    MatterThreadBorderRouterManagementPluginServerShutdownCallback();                                                              \
    MatterThreadNetworkDiagnosticsPluginServerShutdownCallback();                                                                  \
    MatterThreadNetworkDirectoryPluginServerShutdownCallback();                                                                    \
    MatterWiFiNetworkManagementPluginServerShutdownCallback();
