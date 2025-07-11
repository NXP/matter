// DO NOT EDIT - Generated file
//
// Application configuration for Thermostat based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/bridge-app/nxp/linux-M2ZigbeeRcp-bridge/M2ZigbeeRcp-bridge-zap/M2ZigbeeRcp-bridge-app.matter
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
inline constexpr AttributeId kEndpoint2EnabledAttributes[] = {
    Attributes::AbsMaxCoolSetpointLimit::Id,
    Attributes::AbsMaxHeatSetpointLimit::Id,
    Attributes::AbsMinCoolSetpointLimit::Id,
    Attributes::AbsMinHeatSetpointLimit::Id,
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::ControlSequenceOfOperation::Id,
    Attributes::EventList::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::HVACSystemTypeConfiguration::Id,
    Attributes::LocalTemperature::Id,
    Attributes::Occupancy::Id,
    Attributes::OutdoorTemperature::Id,
    Attributes::PICoolingDemand::Id,
    Attributes::PIHeatingDemand::Id,
    Attributes::SystemMode::Id,
};

inline constexpr CommandId kEndpoint2EnabledCommands[] = {
    Commands::ClearWeeklySchedule::Id,
    Commands::GetWeeklySchedule::Id,
    Commands::GetWeeklyScheduleResponse::Id,
    Commands::SetpointRaiseLower::Id,
    Commands::SetWeeklySchedule::Id,
};

} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 2,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint2EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint2EnabledCommands),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId) {
  switch (attributeId) {
    case Attributes::HVACSystemTypeConfiguration::Id:
    case Attributes::PICoolingDemand::Id:
    case Attributes::PIHeatingDemand::Id:
    case Attributes::AbsMaxCoolSetpointLimit::Id:
    case Attributes::AbsMaxHeatSetpointLimit::Id:
    case Attributes::AbsMinCoolSetpointLimit::Id:
    case Attributes::AbsMinHeatSetpointLimit::Id:
    case Attributes::AcceptedCommandList::Id:
    case Attributes::AttributeList::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::ControlSequenceOfOperation::Id:
    case Attributes::EventList::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::LocalTemperature::Id:
    case Attributes::Occupancy::Id:
    case Attributes::OutdoorTemperature::Id:
    case Attributes::SystemMode::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::ClearWeeklySchedule::Id:
    case Commands::GetWeeklySchedule::Id:
    case Commands::GetWeeklyScheduleResponse::Id:
    case Commands::SetWeeklySchedule::Id:
    case Commands::SetpointRaiseLower::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace Thermostat
} // namespace Clusters
} // namespace app
} // namespace chip

