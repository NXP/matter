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
    case app::Clusters::ActivatedCarbonFilterMonitoring::Id:
        emberAfActivatedCarbonFilterMonitoringClusterInitCallback(endpoint);
        break;
    case app::Clusters::AdministratorCommissioning::Id:
        emberAfAdministratorCommissioningClusterInitCallback(endpoint);
        break;
    case app::Clusters::AirQuality::Id:
        emberAfAirQualityClusterInitCallback(endpoint);
        break;
    case app::Clusters::BasicInformation::Id:
        emberAfBasicInformationClusterInitCallback(endpoint);
        break;
    case app::Clusters::CarbonDioxideConcentrationMeasurement::Id:
        emberAfCarbonDioxideConcentrationMeasurementClusterInitCallback(endpoint);
        break;
    case app::Clusters::CarbonMonoxideConcentrationMeasurement::Id:
        emberAfCarbonMonoxideConcentrationMeasurementClusterInitCallback(endpoint);
        break;
    case app::Clusters::Descriptor::Id:
        emberAfDescriptorClusterInitCallback(endpoint);
        break;
    case app::Clusters::DiagnosticLogs::Id:
        emberAfDiagnosticLogsClusterInitCallback(endpoint);
        break;
    case app::Clusters::FanControl::Id:
        emberAfFanControlClusterInitCallback(endpoint);
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
    case app::Clusters::NetworkCommissioning::Id:
        emberAfNetworkCommissioningClusterInitCallback(endpoint);
        break;
    case app::Clusters::NitrogenDioxideConcentrationMeasurement::Id:
        emberAfNitrogenDioxideConcentrationMeasurementClusterInitCallback(endpoint);
        break;
    case app::Clusters::OperationalCredentials::Id:
        emberAfOperationalCredentialsClusterInitCallback(endpoint);
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
    case app::Clusters::RadonConcentrationMeasurement::Id:
        emberAfRadonConcentrationMeasurementClusterInitCallback(endpoint);
        break;
    case app::Clusters::RelativeHumidityMeasurement::Id:
        emberAfRelativeHumidityMeasurementClusterInitCallback(endpoint);
        break;
    case app::Clusters::TemperatureMeasurement::Id:
        emberAfTemperatureMeasurementClusterInitCallback(endpoint);
        break;
    case app::Clusters::Thermostat::Id:
        emberAfThermostatClusterInitCallback(endpoint);
        break;
    case app::Clusters::TotalVolatileOrganicCompoundsConcentrationMeasurement::Id:
        emberAfTotalVolatileOrganicCompoundsConcentrationMeasurementClusterInitCallback(endpoint);
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
    case app::Clusters::ActivatedCarbonFilterMonitoring::Id:
        emberAfActivatedCarbonFilterMonitoringClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::AdministratorCommissioning::Id:
        emberAfAdministratorCommissioningClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::AirQuality::Id:
        emberAfAirQualityClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::BasicInformation::Id:
        emberAfBasicInformationClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::CarbonDioxideConcentrationMeasurement::Id:
        emberAfCarbonDioxideConcentrationMeasurementClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::CarbonMonoxideConcentrationMeasurement::Id:
        emberAfCarbonMonoxideConcentrationMeasurementClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::Descriptor::Id:
        emberAfDescriptorClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::DiagnosticLogs::Id:
        emberAfDiagnosticLogsClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::FanControl::Id:
        emberAfFanControlClusterShutdownCallback(endpoint);
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
    case app::Clusters::NetworkCommissioning::Id:
        emberAfNetworkCommissioningClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::NitrogenDioxideConcentrationMeasurement::Id:
        emberAfNitrogenDioxideConcentrationMeasurementClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::OperationalCredentials::Id:
        emberAfOperationalCredentialsClusterShutdownCallback(endpoint);
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
    case app::Clusters::RadonConcentrationMeasurement::Id:
        emberAfRadonConcentrationMeasurementClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::RelativeHumidityMeasurement::Id:
        emberAfRelativeHumidityMeasurementClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::TemperatureMeasurement::Id:
        emberAfTemperatureMeasurementClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::Thermostat::Id:
        emberAfThermostatClusterShutdownCallback(endpoint);
        break;
    case app::Clusters::TotalVolatileOrganicCompoundsConcentrationMeasurement::Id:
        emberAfTotalVolatileOrganicCompoundsConcentrationMeasurementClusterShutdownCallback(endpoint);
        break;
    default:
        // Unrecognized cluster ID
        break;
    }
}
