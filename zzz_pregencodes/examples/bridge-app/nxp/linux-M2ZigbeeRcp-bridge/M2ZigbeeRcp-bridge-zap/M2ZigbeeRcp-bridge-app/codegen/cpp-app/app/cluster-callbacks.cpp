#include <app-common/zap-generated/callback.h>
#include <app-common/zap-generated/ids/Clusters.h>
#include <lib/support/Span.h>
#include <protocols/interaction_model/Constants.h>

using namespace chip;

// Cluster Init Functions
void emberAfClusterInitCallback(EndpointId endpoint, ClusterId clusterId)
{
    switch (clusterId)
    {
    case app::Clusters::AccessControl::Id:
        emberAfAccessControlClusterInitCallback(endpoint);
        break;
    case app::Clusters::Actions::Id:
        emberAfActionsClusterInitCallback(endpoint);
        break;
    case app::Clusters::ActivatedCarbonFilterMonitoring::Id:
        emberAfActivatedCarbonFilterMonitoringClusterInitCallback(endpoint);
        break;
    case app::Clusters::AdministratorCommissioning::Id:
        emberAfAdministratorCommissioningClusterInitCallback(endpoint);
        break;
    case app::Clusters::AirQuality::Id:
        emberAfAirQualityClusterInitCallback(endpoint);
        break;
    case app::Clusters::BallastConfiguration::Id:
        emberAfBallastConfigurationClusterInitCallback(endpoint);
        break;
    case app::Clusters::BasicInformation::Id:
        emberAfBasicInformationClusterInitCallback(endpoint);
        break;
    case app::Clusters::Binding::Id:
        emberAfBindingClusterInitCallback(endpoint);
        break;
    case app::Clusters::BridgedDeviceBasicInformation::Id:
        emberAfBridgedDeviceBasicInformationClusterInitCallback(endpoint);
        break;
    case app::Clusters::CarbonDioxideConcentrationMeasurement::Id:
        emberAfCarbonDioxideConcentrationMeasurementClusterInitCallback(endpoint);
        break;
    case app::Clusters::CarbonMonoxideConcentrationMeasurement::Id:
        emberAfCarbonMonoxideConcentrationMeasurementClusterInitCallback(endpoint);
        break;
    case app::Clusters::ColorControl::Id:
        emberAfColorControlClusterInitCallback(endpoint);
        break;
    case app::Clusters::Descriptor::Id:
        emberAfDescriptorClusterInitCallback(endpoint);
        break;
    case app::Clusters::DiagnosticLogs::Id:
        emberAfDiagnosticLogsClusterInitCallback(endpoint);
        break;
    case app::Clusters::DishwasherAlarm::Id:
        emberAfDishwasherAlarmClusterInitCallback(endpoint);
        break;
    case app::Clusters::DoorLock::Id:
        emberAfDoorLockClusterInitCallback(endpoint);
        break;
    case app::Clusters::EthernetNetworkDiagnostics::Id:
        emberAfEthernetNetworkDiagnosticsClusterInitCallback(endpoint);
        break;
    case app::Clusters::FanControl::Id:
        emberAfFanControlClusterInitCallback(endpoint);
        break;
    case app::Clusters::FlowMeasurement::Id:
        emberAfFlowMeasurementClusterInitCallback(endpoint);
        break;
    case app::Clusters::FormaldehydeConcentrationMeasurement::Id:
        emberAfFormaldehydeConcentrationMeasurementClusterInitCallback(endpoint);
        break;
    case app::Clusters::GeneralCommissioning::Id:
        emberAfGeneralCommissioningClusterInitCallback(endpoint);
        break;
    case app::Clusters::GeneralDiagnostics::Id:
        emberAfGeneralDiagnosticsClusterInitCallback(endpoint);
        break;
    case app::Clusters::GroupKeyManagement::Id:
        emberAfGroupKeyManagementClusterInitCallback(endpoint);
        break;
    case app::Clusters::Groups::Id:
        emberAfGroupsClusterInitCallback(endpoint);
        break;
    case app::Clusters::HepaFilterMonitoring::Id:
        emberAfHepaFilterMonitoringClusterInitCallback(endpoint);
        break;
    case app::Clusters::Identify::Id:
        emberAfIdentifyClusterInitCallback(endpoint);
        break;
    case app::Clusters::IlluminanceMeasurement::Id:
        emberAfIlluminanceMeasurementClusterInitCallback(endpoint);
        break;
    case app::Clusters::LaundryWasherControls::Id:
        emberAfLaundryWasherControlsClusterInitCallback(endpoint);
        break;
    case app::Clusters::LevelControl::Id:
        emberAfLevelControlClusterInitCallback(endpoint);
        break;
    case app::Clusters::LocalizationConfiguration::Id:
        emberAfLocalizationConfigurationClusterInitCallback(endpoint);
        break;
    case app::Clusters::NetworkCommissioning::Id:
        emberAfNetworkCommissioningClusterInitCallback(endpoint);
        break;
    case app::Clusters::NitrogenDioxideConcentrationMeasurement::Id:
        emberAfNitrogenDioxideConcentrationMeasurementClusterInitCallback(endpoint);
        break;
    case app::Clusters::OccupancySensing::Id:
        emberAfOccupancySensingClusterInitCallback(endpoint);
        break;
    case app::Clusters::OnOff::Id:
        emberAfOnOffClusterInitCallback(endpoint);
        break;
    case app::Clusters::OperationalCredentials::Id:
        emberAfOperationalCredentialsClusterInitCallback(endpoint);
        break;
    case app::Clusters::OtaSoftwareUpdateRequestor::Id:
        emberAfOtaSoftwareUpdateRequestorClusterInitCallback(endpoint);
        break;
    case app::Clusters::OzoneConcentrationMeasurement::Id:
        emberAfOzoneConcentrationMeasurementClusterInitCallback(endpoint);
        break;
    case app::Clusters::Pm10ConcentrationMeasurement::Id:
        emberAfPm10ConcentrationMeasurementClusterInitCallback(endpoint);
        break;
    case app::Clusters::Pm1ConcentrationMeasurement::Id:
        emberAfPm1ConcentrationMeasurementClusterInitCallback(endpoint);
        break;
    case app::Clusters::Pm25ConcentrationMeasurement::Id:
        emberAfPm25ConcentrationMeasurementClusterInitCallback(endpoint);
        break;
    case app::Clusters::PowerSourceConfiguration::Id:
        emberAfPowerSourceConfigurationClusterInitCallback(endpoint);
        break;
    case app::Clusters::PressureMeasurement::Id:
        emberAfPressureMeasurementClusterInitCallback(endpoint);
        break;
    case app::Clusters::PumpConfigurationAndControl::Id:
        emberAfPumpConfigurationAndControlClusterInitCallback(endpoint);
        break;
    case app::Clusters::RadonConcentrationMeasurement::Id:
        emberAfRadonConcentrationMeasurementClusterInitCallback(endpoint);
        break;
    case app::Clusters::RefrigeratorAlarm::Id:
        emberAfRefrigeratorAlarmClusterInitCallback(endpoint);
        break;
    case app::Clusters::RelativeHumidityMeasurement::Id:
        emberAfRelativeHumidityMeasurementClusterInitCallback(endpoint);
        break;
    case app::Clusters::ScenesManagement::Id:
        emberAfScenesManagementClusterInitCallback(endpoint);
        break;
    case app::Clusters::SmokeCoAlarm::Id:
        emberAfSmokeCoAlarmClusterInitCallback(endpoint);
        break;
    case app::Clusters::SoftwareDiagnostics::Id:
        emberAfSoftwareDiagnosticsClusterInitCallback(endpoint);
        break;
    case app::Clusters::TemperatureControl::Id:
        emberAfTemperatureControlClusterInitCallback(endpoint);
        break;
    case app::Clusters::TemperatureMeasurement::Id:
        emberAfTemperatureMeasurementClusterInitCallback(endpoint);
        break;
    case app::Clusters::Thermostat::Id:
        emberAfThermostatClusterInitCallback(endpoint);
        break;
    case app::Clusters::ThermostatUserInterfaceConfiguration::Id:
        emberAfThermostatUserInterfaceConfigurationClusterInitCallback(endpoint);
        break;
    case app::Clusters::ThreadNetworkDiagnostics::Id:
        emberAfThreadNetworkDiagnosticsClusterInitCallback(endpoint);
        break;
    case app::Clusters::TimeFormatLocalization::Id:
        emberAfTimeFormatLocalizationClusterInitCallback(endpoint);
        break;
    case app::Clusters::TotalVolatileOrganicCompoundsConcentrationMeasurement::Id:
        emberAfTotalVolatileOrganicCompoundsConcentrationMeasurementClusterInitCallback(endpoint);
        break;
    case app::Clusters::UnitLocalization::Id:
        emberAfUnitLocalizationClusterInitCallback(endpoint);
        break;
    case app::Clusters::UserLabel::Id:
        emberAfUserLabelClusterInitCallback(endpoint);
        break;
    case app::Clusters::WiFiNetworkDiagnostics::Id:
        emberAfWiFiNetworkDiagnosticsClusterInitCallback(endpoint);
        break;
    case app::Clusters::WindowCovering::Id:
        emberAfWindowCoveringClusterInitCallback(endpoint);
        break;
    default:
        // Unrecognized cluster ID
        break;
    }
}

// Cluster Shutdown Functions
void emberAfClusterShutdownCallback(EndpointId endpoint, ClusterId clusterId)
{
    switch (clusterId)
    {
    case app::Clusters::AccessControl::Id:
        emberAfAccessControlClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::Actions::Id:
        emberAfActionsClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::ActivatedCarbonFilterMonitoring::Id:
        emberAfActivatedCarbonFilterMonitoringClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::AdministratorCommissioning::Id:
        emberAfAdministratorCommissioningClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::AirQuality::Id:
        emberAfAirQualityClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::BallastConfiguration::Id:
        emberAfBallastConfigurationClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::BasicInformation::Id:
        emberAfBasicInformationClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::Binding::Id:
        emberAfBindingClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::BridgedDeviceBasicInformation::Id:
        emberAfBridgedDeviceBasicInformationClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::CarbonDioxideConcentrationMeasurement::Id:
        emberAfCarbonDioxideConcentrationMeasurementClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::CarbonMonoxideConcentrationMeasurement::Id:
        emberAfCarbonMonoxideConcentrationMeasurementClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::ColorControl::Id:
        emberAfColorControlClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::Descriptor::Id:
        emberAfDescriptorClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::DiagnosticLogs::Id:
        emberAfDiagnosticLogsClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::DishwasherAlarm::Id:
        emberAfDishwasherAlarmClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::DoorLock::Id:
        emberAfDoorLockClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::EthernetNetworkDiagnostics::Id:
        emberAfEthernetNetworkDiagnosticsClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::FanControl::Id:
        emberAfFanControlClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::FlowMeasurement::Id:
        emberAfFlowMeasurementClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::FormaldehydeConcentrationMeasurement::Id:
        emberAfFormaldehydeConcentrationMeasurementClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::GeneralCommissioning::Id:
        emberAfGeneralCommissioningClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::GeneralDiagnostics::Id:
        emberAfGeneralDiagnosticsClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::GroupKeyManagement::Id:
        emberAfGroupKeyManagementClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::Groups::Id:
        emberAfGroupsClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::HepaFilterMonitoring::Id:
        emberAfHepaFilterMonitoringClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::Identify::Id:
        emberAfIdentifyClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::IlluminanceMeasurement::Id:
        emberAfIlluminanceMeasurementClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::LaundryWasherControls::Id:
        emberAfLaundryWasherControlsClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::LevelControl::Id:
        emberAfLevelControlClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::LocalizationConfiguration::Id:
        emberAfLocalizationConfigurationClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::NetworkCommissioning::Id:
        emberAfNetworkCommissioningClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::NitrogenDioxideConcentrationMeasurement::Id:
        emberAfNitrogenDioxideConcentrationMeasurementClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::OccupancySensing::Id:
        emberAfOccupancySensingClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::OnOff::Id:
        emberAfOnOffClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::OperationalCredentials::Id:
        emberAfOperationalCredentialsClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::OtaSoftwareUpdateRequestor::Id:
        emberAfOtaSoftwareUpdateRequestorClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::OzoneConcentrationMeasurement::Id:
        emberAfOzoneConcentrationMeasurementClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::Pm10ConcentrationMeasurement::Id:
        emberAfPm10ConcentrationMeasurementClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::Pm1ConcentrationMeasurement::Id:
        emberAfPm1ConcentrationMeasurementClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::Pm25ConcentrationMeasurement::Id:
        emberAfPm25ConcentrationMeasurementClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::PowerSourceConfiguration::Id:
        emberAfPowerSourceConfigurationClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::PressureMeasurement::Id:
        emberAfPressureMeasurementClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::PumpConfigurationAndControl::Id:
        emberAfPumpConfigurationAndControlClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::RadonConcentrationMeasurement::Id:
        emberAfRadonConcentrationMeasurementClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::RefrigeratorAlarm::Id:
        emberAfRefrigeratorAlarmClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::RelativeHumidityMeasurement::Id:
        emberAfRelativeHumidityMeasurementClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::ScenesManagement::Id:
        emberAfScenesManagementClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::SmokeCoAlarm::Id:
        emberAfSmokeCoAlarmClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::SoftwareDiagnostics::Id:
        emberAfSoftwareDiagnosticsClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::TemperatureControl::Id:
        emberAfTemperatureControlClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::TemperatureMeasurement::Id:
        emberAfTemperatureMeasurementClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::Thermostat::Id:
        emberAfThermostatClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::ThermostatUserInterfaceConfiguration::Id:
        emberAfThermostatUserInterfaceConfigurationClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::ThreadNetworkDiagnostics::Id:
        emberAfThreadNetworkDiagnosticsClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::TimeFormatLocalization::Id:
        emberAfTimeFormatLocalizationClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::TotalVolatileOrganicCompoundsConcentrationMeasurement::Id:
        emberAfTotalVolatileOrganicCompoundsConcentrationMeasurementClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::UnitLocalization::Id:
        emberAfUnitLocalizationClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::UserLabel::Id:
        emberAfUserLabelClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::WiFiNetworkDiagnostics::Id:
        emberAfWiFiNetworkDiagnosticsClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::WindowCovering::Id:
        emberAfWindowCoveringClusterShutdownCallback(endpoint);
        break;
    default:
        // Unrecognized cluster ID
        break;
    }
}
