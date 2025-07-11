#pragma once
void MatterAccessControlPluginServerInitCallback();
void MatterAdministratorCommissioningPluginServerInitCallback();
void MatterBasicInformationPluginServerInitCallback();
void MatterDescriptorPluginServerInitCallback();
void MatterDeviceEnergyManagementPluginServerInitCallback();
void MatterDeviceEnergyManagementModePluginServerInitCallback();
void MatterDiagnosticLogsPluginServerInitCallback();
void MatterElectricalEnergyMeasurementPluginServerInitCallback();
void MatterElectricalPowerMeasurementPluginServerInitCallback();
void MatterGeneralCommissioningPluginServerInitCallback();
void MatterGeneralDiagnosticsPluginServerInitCallback();
void MatterGroupKeyManagementPluginServerInitCallback();
void MatterIdentifyPluginServerInitCallback();
void MatterNetworkCommissioningPluginServerInitCallback();
void MatterOperationalCredentialsPluginServerInitCallback();
void MatterPowerSourcePluginServerInitCallback();
void MatterPowerTopologyPluginServerInitCallback();
void MatterTemperatureMeasurementPluginServerInitCallback();
void MatterAccessControlPluginServerShutdownCallback();
void MatterAdministratorCommissioningPluginServerShutdownCallback();
void MatterBasicInformationPluginServerShutdownCallback();
void MatterDescriptorPluginServerShutdownCallback();
void MatterDeviceEnergyManagementPluginServerShutdownCallback();
void MatterDeviceEnergyManagementModePluginServerShutdownCallback();
void MatterDiagnosticLogsPluginServerShutdownCallback();
void MatterElectricalEnergyMeasurementPluginServerShutdownCallback();
void MatterElectricalPowerMeasurementPluginServerShutdownCallback();
void MatterGeneralCommissioningPluginServerShutdownCallback();
void MatterGeneralDiagnosticsPluginServerShutdownCallback();
void MatterGroupKeyManagementPluginServerShutdownCallback();
void MatterIdentifyPluginServerShutdownCallback();
void MatterNetworkCommissioningPluginServerShutdownCallback();
void MatterOperationalCredentialsPluginServerShutdownCallback();
void MatterPowerSourcePluginServerShutdownCallback();
void MatterPowerTopologyPluginServerShutdownCallback();
void MatterTemperatureMeasurementPluginServerShutdownCallback();

#define MATTER_PLUGINS_INIT \
    MatterAccessControlPluginServerInitCallback(); \
    MatterAdministratorCommissioningPluginServerInitCallback(); \
    MatterBasicInformationPluginServerInitCallback(); \
    MatterDescriptorPluginServerInitCallback(); \
    MatterDeviceEnergyManagementPluginServerInitCallback(); \
    MatterDeviceEnergyManagementModePluginServerInitCallback(); \
    MatterDiagnosticLogsPluginServerInitCallback(); \
    MatterElectricalEnergyMeasurementPluginServerInitCallback(); \
    MatterElectricalPowerMeasurementPluginServerInitCallback(); \
    MatterGeneralCommissioningPluginServerInitCallback(); \
    MatterGeneralDiagnosticsPluginServerInitCallback(); \
    MatterGroupKeyManagementPluginServerInitCallback(); \
    MatterIdentifyPluginServerInitCallback(); \
    MatterNetworkCommissioningPluginServerInitCallback(); \
    MatterOperationalCredentialsPluginServerInitCallback(); \
    MatterPowerSourcePluginServerInitCallback(); \
    MatterPowerTopologyPluginServerInitCallback(); \
    MatterTemperatureMeasurementPluginServerInitCallback();

#define MATTER_PLUGINS_SHUTDOWN \
    MatterAccessControlPluginServerShutdownCallback(); \
    MatterAdministratorCommissioningPluginServerShutdownCallback(); \
    MatterBasicInformationPluginServerShutdownCallback(); \
    MatterDescriptorPluginServerShutdownCallback(); \
    MatterDeviceEnergyManagementPluginServerShutdownCallback(); \
    MatterDeviceEnergyManagementModePluginServerShutdownCallback(); \
    MatterDiagnosticLogsPluginServerShutdownCallback(); \
    MatterElectricalEnergyMeasurementPluginServerShutdownCallback(); \
    MatterElectricalPowerMeasurementPluginServerShutdownCallback(); \
    MatterGeneralCommissioningPluginServerShutdownCallback(); \
    MatterGeneralDiagnosticsPluginServerShutdownCallback(); \
    MatterGroupKeyManagementPluginServerShutdownCallback(); \
    MatterIdentifyPluginServerShutdownCallback(); \
    MatterNetworkCommissioningPluginServerShutdownCallback(); \
    MatterOperationalCredentialsPluginServerShutdownCallback(); \
    MatterPowerSourcePluginServerShutdownCallback(); \
    MatterPowerTopologyPluginServerShutdownCallback(); \
    MatterTemperatureMeasurementPluginServerShutdownCallback();

