#pragma once
void MatterAccessControlPluginServerInitCallback();
void MatterAdministratorCommissioningPluginServerInitCallback();
void MatterBasicInformationPluginServerInitCallback();
void MatterDescriptorPluginServerInitCallback();
void MatterGeneralCommissioningPluginServerInitCallback();
void MatterGeneralDiagnosticsPluginServerInitCallback();
void MatterGroupKeyManagementPluginServerInitCallback();
void MatterJointFabricAdministratorPluginServerInitCallback();
void MatterJointFabricDatastorePluginServerInitCallback();
void MatterLocalizationConfigurationPluginServerInitCallback();
void MatterNetworkCommissioningPluginServerInitCallback();
void MatterOperationalCredentialsPluginServerInitCallback();
void MatterOtaSoftwareUpdateRequestorPluginServerInitCallback();
void MatterUnitLocalizationPluginServerInitCallback();
void MatterAccessControlPluginServerShutdownCallback();
void MatterAdministratorCommissioningPluginServerShutdownCallback();
void MatterBasicInformationPluginServerShutdownCallback();
void MatterDescriptorPluginServerShutdownCallback();
void MatterGeneralCommissioningPluginServerShutdownCallback();
void MatterGeneralDiagnosticsPluginServerShutdownCallback();
void MatterGroupKeyManagementPluginServerShutdownCallback();
void MatterJointFabricAdministratorPluginServerShutdownCallback();
void MatterJointFabricDatastorePluginServerShutdownCallback();
void MatterLocalizationConfigurationPluginServerShutdownCallback();
void MatterNetworkCommissioningPluginServerShutdownCallback();
void MatterOperationalCredentialsPluginServerShutdownCallback();
void MatterOtaSoftwareUpdateRequestorPluginServerShutdownCallback();
void MatterUnitLocalizationPluginServerShutdownCallback();

#define MATTER_PLUGINS_INIT                                                                                                        \
    MatterAccessControlPluginServerInitCallback();                                                                                 \
    MatterAdministratorCommissioningPluginServerInitCallback();                                                                    \
    MatterBasicInformationPluginServerInitCallback();                                                                              \
    MatterDescriptorPluginServerInitCallback();                                                                                    \
    MatterGeneralCommissioningPluginServerInitCallback();                                                                          \
    MatterGeneralDiagnosticsPluginServerInitCallback();                                                                            \
    MatterGroupKeyManagementPluginServerInitCallback();                                                                            \
    MatterJointFabricAdministratorPluginServerInitCallback();                                                                      \
    MatterJointFabricDatastorePluginServerInitCallback();                                                                          \
    MatterLocalizationConfigurationPluginServerInitCallback();                                                                     \
    MatterNetworkCommissioningPluginServerInitCallback();                                                                          \
    MatterOperationalCredentialsPluginServerInitCallback();                                                                        \
    MatterOtaSoftwareUpdateRequestorPluginServerInitCallback();                                                                    \
    MatterUnitLocalizationPluginServerInitCallback();

#define MATTER_PLUGINS_SHUTDOWN                                                                                                    \
    MatterAccessControlPluginServerShutdownCallback();                                                                             \
    MatterAdministratorCommissioningPluginServerShutdownCallback();                                                                \
    MatterBasicInformationPluginServerShutdownCallback();                                                                          \
    MatterDescriptorPluginServerShutdownCallback();                                                                                \
    MatterGeneralCommissioningPluginServerShutdownCallback();                                                                      \
    MatterGeneralDiagnosticsPluginServerShutdownCallback();                                                                        \
    MatterGroupKeyManagementPluginServerShutdownCallback();                                                                        \
    MatterJointFabricAdministratorPluginServerShutdownCallback();                                                                  \
    MatterJointFabricDatastorePluginServerShutdownCallback();                                                                      \
    MatterLocalizationConfigurationPluginServerShutdownCallback();                                                                 \
    MatterNetworkCommissioningPluginServerShutdownCallback();                                                                      \
    MatterOperationalCredentialsPluginServerShutdownCallback();                                                                    \
    MatterOtaSoftwareUpdateRequestorPluginServerShutdownCallback();                                                                \
    MatterUnitLocalizationPluginServerShutdownCallback();
