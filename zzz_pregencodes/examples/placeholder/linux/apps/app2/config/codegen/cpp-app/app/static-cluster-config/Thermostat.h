// DO NOT EDIT - Generated file
//
// Application configuration for Thermostat based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/placeholder/linux/apps/app2/config.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/Thermostat/AttributeIds.h>
#include <clusters/Thermostat/CommandIds.h>
#include <clusters/Thermostat/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace Thermostat {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint0EnabledAttributes[] = {
    Attributes::AbsMaxCoolSetpointLimit::Id,
    Attributes::AbsMaxHeatSetpointLimit::Id,
    Attributes::AbsMinCoolSetpointLimit::Id,
    Attributes::AbsMinHeatSetpointLimit::Id,
    Attributes::ACCapacity::Id,
    Attributes::ACCapacityformat::Id,
    Attributes::ACCoilTemperature::Id,
    Attributes::ACCompressorType::Id,
    Attributes::ACLouverPosition::Id,
    Attributes::ACRefrigerantType::Id,
    Attributes::ACType::Id,
    Attributes::ClusterRevision::Id,
    Attributes::ControlSequenceOfOperation::Id,
    Attributes::EmergencyHeatDelta::Id,
    Attributes::FeatureMap::Id,
    Attributes::HVACSystemTypeConfiguration::Id,
    Attributes::LocalTemperature::Id,
    Attributes::LocalTemperatureCalibration::Id,
    Attributes::MaxCoolSetpointLimit::Id,
    Attributes::MaxHeatSetpointLimit::Id,
    Attributes::MinCoolSetpointLimit::Id,
    Attributes::MinHeatSetpointLimit::Id,
    Attributes::MinSetpointDeadBand::Id,
    Attributes::NumberOfDailyTransitions::Id,
    Attributes::NumberOfWeeklyTransitions::Id,
    Attributes::Occupancy::Id,
    Attributes::OccupiedCoolingSetpoint::Id,
    Attributes::OccupiedHeatingSetpoint::Id,
    Attributes::OccupiedSetback::Id,
    Attributes::OccupiedSetbackMax::Id,
    Attributes::OccupiedSetbackMin::Id,
    Attributes::OutdoorTemperature::Id,
    Attributes::PICoolingDemand::Id,
    Attributes::PIHeatingDemand::Id,
    Attributes::RemoteSensing::Id,
    Attributes::SetpointChangeAmount::Id,
    Attributes::SetpointChangeSource::Id,
    Attributes::SetpointChangeSourceTimestamp::Id,
    Attributes::StartOfWeek::Id,
    Attributes::SystemMode::Id,
    Attributes::TemperatureSetpointHold::Id,
    Attributes::TemperatureSetpointHoldDuration::Id,
    Attributes::ThermostatProgrammingOperationMode::Id,
    Attributes::ThermostatRunningMode::Id,
    Attributes::ThermostatRunningState::Id,
    Attributes::UnoccupiedCoolingSetpoint::Id,
    Attributes::UnoccupiedHeatingSetpoint::Id,
    Attributes::UnoccupiedSetback::Id,
    Attributes::UnoccupiedSetbackMax::Id,
    Attributes::UnoccupiedSetbackMin::Id,
};
} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 0,
        .featureMap = BitFlags<FeatureBitmapType> {
            FeatureBitmapType::kHeating, // feature bit 0x1
            FeatureBitmapType::kCooling, // feature bit 0x2
            FeatureBitmapType::kScheduleConfiguration// feature bit 0x8
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint0EnabledAttributes),
        .enabledCommands = Span<const CommandId>(),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId) {
  switch (attributeId) {
    case Attributes::ACCapacity::Id:
    case Attributes::ACCapacityformat::Id:
    case Attributes::ACCoilTemperature::Id:
    case Attributes::ACCompressorType::Id:
    case Attributes::ACLouverPosition::Id:
    case Attributes::ACRefrigerantType::Id:
    case Attributes::ACType::Id:
    case Attributes::HVACSystemTypeConfiguration::Id:
    case Attributes::PICoolingDemand::Id:
    case Attributes::PIHeatingDemand::Id:
    case Attributes::AbsMaxCoolSetpointLimit::Id:
    case Attributes::AbsMaxHeatSetpointLimit::Id:
    case Attributes::AbsMinCoolSetpointLimit::Id:
    case Attributes::AbsMinHeatSetpointLimit::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::ControlSequenceOfOperation::Id:
    case Attributes::EmergencyHeatDelta::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::LocalTemperature::Id:
    case Attributes::LocalTemperatureCalibration::Id:
    case Attributes::MaxCoolSetpointLimit::Id:
    case Attributes::MaxHeatSetpointLimit::Id:
    case Attributes::MinCoolSetpointLimit::Id:
    case Attributes::MinHeatSetpointLimit::Id:
    case Attributes::MinSetpointDeadBand::Id:
    case Attributes::NumberOfDailyTransitions::Id:
    case Attributes::NumberOfWeeklyTransitions::Id:
    case Attributes::Occupancy::Id:
    case Attributes::OccupiedCoolingSetpoint::Id:
    case Attributes::OccupiedHeatingSetpoint::Id:
    case Attributes::OccupiedSetback::Id:
    case Attributes::OccupiedSetbackMax::Id:
    case Attributes::OccupiedSetbackMin::Id:
    case Attributes::OutdoorTemperature::Id:
    case Attributes::RemoteSensing::Id:
    case Attributes::SetpointChangeAmount::Id:
    case Attributes::SetpointChangeSource::Id:
    case Attributes::SetpointChangeSourceTimestamp::Id:
    case Attributes::StartOfWeek::Id:
    case Attributes::SystemMode::Id:
    case Attributes::TemperatureSetpointHold::Id:
    case Attributes::TemperatureSetpointHoldDuration::Id:
    case Attributes::ThermostatProgrammingOperationMode::Id:
    case Attributes::ThermostatRunningMode::Id:
    case Attributes::ThermostatRunningState::Id:
    case Attributes::UnoccupiedCoolingSetpoint::Id:
    case Attributes::UnoccupiedHeatingSetpoint::Id:
    case Attributes::UnoccupiedSetback::Id:
    case Attributes::UnoccupiedSetbackMax::Id:
    case Attributes::UnoccupiedSetbackMin::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace Thermostat
} // namespace Clusters
} // namespace app
} // namespace chip

