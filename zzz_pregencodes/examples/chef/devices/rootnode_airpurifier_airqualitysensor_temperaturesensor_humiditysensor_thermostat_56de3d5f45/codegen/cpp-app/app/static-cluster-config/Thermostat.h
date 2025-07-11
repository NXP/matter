// DO NOT EDIT - Generated file
//
// Application configuration for Thermostat based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/chef/devices/rootnode_airpurifier_airqualitysensor_temperaturesensor_humiditysensor_thermostat_56de3d5f45.matter
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
inline constexpr AttributeId kEndpoint5EnabledAttributes[] = {
    Attributes::AbsMaxHeatSetpointLimit::Id,
    Attributes::AbsMinHeatSetpointLimit::Id,
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::ControlSequenceOfOperation::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::LocalTemperature::Id,
    Attributes::MaxHeatSetpointLimit::Id,
    Attributes::MinHeatSetpointLimit::Id,
    Attributes::OccupiedHeatingSetpoint::Id,
    Attributes::PIHeatingDemand::Id,
    Attributes::SystemMode::Id,
};

inline constexpr CommandId kEndpoint5EnabledCommands[] = {
    Commands::SetpointRaiseLower::Id,
};

} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 5,
        .featureMap = BitFlags<FeatureBitmapType> {
            FeatureBitmapType::kHeating// feature bit 0x1
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint5EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint5EnabledCommands),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId) {
  switch (attributeId) {
    case Attributes::PIHeatingDemand::Id:
    case Attributes::AbsMaxHeatSetpointLimit::Id:
    case Attributes::AbsMinHeatSetpointLimit::Id:
    case Attributes::AcceptedCommandList::Id:
    case Attributes::AttributeList::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::ControlSequenceOfOperation::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::LocalTemperature::Id:
    case Attributes::MaxHeatSetpointLimit::Id:
    case Attributes::MinHeatSetpointLimit::Id:
    case Attributes::OccupiedHeatingSetpoint::Id:
    case Attributes::SystemMode::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
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

