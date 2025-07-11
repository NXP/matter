#pragma once
void MatterAccessControlPluginServerInitCallback();
void MatterAdministratorCommissioningPluginServerInitCallback();
void MatterBasicInformationPluginServerInitCallback();
void MatterDescriptorPluginServerInitCallback();
void MatterFlowMeasurementPluginServerInitCallback();
void MatterGeneralCommissioningPluginServerInitCallback();
void MatterGeneralDiagnosticsPluginServerInitCallback();
void MatterGroupKeyManagementPluginServerInitCallback();
void MatterIdentifyPluginServerInitCallback();
void MatterLevelControlPluginServerInitCallback();
void MatterNetworkCommissioningPluginServerInitCallback();
void MatterOnOffPluginServerInitCallback();
void MatterOperationalCredentialsPluginServerInitCallback();
void MatterPressureMeasurementPluginServerInitCallback();
void MatterPumpConfigurationAndControlPluginServerInitCallback();
void MatterTemperatureMeasurementPluginServerInitCallback();
void MatterUnitLocalizationPluginServerInitCallback();
void MatterAccessControlPluginServerShutdownCallback();
void MatterAdministratorCommissioningPluginServerShutdownCallback();
void MatterBasicInformationPluginServerShutdownCallback();
void MatterDescriptorPluginServerShutdownCallback();
void MatterFlowMeasurementPluginServerShutdownCallback();
void MatterGeneralCommissioningPluginServerShutdownCallback();
void MatterGeneralDiagnosticsPluginServerShutdownCallback();
void MatterGroupKeyManagementPluginServerShutdownCallback();
void MatterIdentifyPluginServerShutdownCallback();
void MatterLevelControlPluginServerShutdownCallback();
void MatterNetworkCommissioningPluginServerShutdownCallback();
void MatterOnOffPluginServerShutdownCallback();
void MatterOperationalCredentialsPluginServerShutdownCallback();
void MatterPressureMeasurementPluginServerShutdownCallback();
void MatterPumpConfigurationAndControlPluginServerShutdownCallback();
void MatterTemperatureMeasurementPluginServerShutdownCallback();
void MatterUnitLocalizationPluginServerShutdownCallback();

#define MATTER_PLUGINS_INIT \
    MatterAccessControlPluginServerInitCallback(); \
    MatterAdministratorCommissioningPluginServerInitCallback(); \
    MatterBasicInformationPluginServerInitCallback(); \
    MatterDescriptorPluginServerInitCallback(); \
    MatterFlowMeasurementPluginServerInitCallback(); \
    MatterGeneralCommissioningPluginServerInitCallback(); \
    MatterGeneralDiagnosticsPluginServerInitCallback(); \
    MatterGroupKeyManagementPluginServerInitCallback(); \
    MatterIdentifyPluginServerInitCallback(); \
    MatterLevelControlPluginServerInitCallback(); \
    MatterNetworkCommissioningPluginServerInitCallback(); \
    MatterOnOffPluginServerInitCallback(); \
    MatterOperationalCredentialsPluginServerInitCallback(); \
    MatterPressureMeasurementPluginServerInitCallback(); \
    MatterPumpConfigurationAndControlPluginServerInitCallback(); \
    MatterTemperatureMeasurementPluginServerInitCallback(); \
    MatterUnitLocalizationPluginServerInitCallback();

#define MATTER_PLUGINS_SHUTDOWN \
    MatterAccessControlPluginServerShutdownCallback(); \
    MatterAdministratorCommissioningPluginServerShutdownCallback(); \
    MatterBasicInformationPluginServerShutdownCallback(); \
    MatterDescriptorPluginServerShutdownCallback(); \
    MatterFlowMeasurementPluginServerShutdownCallback(); \
    MatterGeneralCommissioningPluginServerShutdownCallback(); \
    MatterGeneralDiagnosticsPluginServerShutdownCallback(); \
    MatterGroupKeyManagementPluginServerShutdownCallback(); \
    MatterIdentifyPluginServerShutdownCallback(); \
    MatterLevelControlPluginServerShutdownCallback(); \
    MatterNetworkCommissioningPluginServerShutdownCallback(); \
    MatterOnOffPluginServerShutdownCallback(); \
    MatterOperationalCredentialsPluginServerShutdownCallback(); \
    MatterPressureMeasurementPluginServerShutdownCallback(); \
    MatterPumpConfigurationAndControlPluginServerShutdownCallback(); \
    MatterTemperatureMeasurementPluginServerShutdownCallback(); \
    MatterUnitLocalizationPluginServerShutdownCallback();

