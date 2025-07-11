// DO NOT EDIT - Generated file
//
// Application configuration for TemperatureControl based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/chef/devices/rootnode_dishwasher_cc105034fe.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/TemperatureControl/AttributeIds.h>
#include <clusters/TemperatureControl/CommandIds.h>
#include <clusters/TemperatureControl/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace TemperatureControl {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::MaxTemperature::Id,
    Attributes::MinTemperature::Id,
    Attributes::Step::Id,
    Attributes::TemperatureSetpoint::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::SetTemperature::Id,
};

} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 1,
        .featureMap = BitFlags<FeatureBitmapType> {
            FeatureBitmapType::kTemperatureNumber, // feature bit 0x1
            FeatureBitmapType::kTemperatureStep// feature bit 0x4
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint1EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint1EnabledCommands),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId) {
  switch (attributeId) {
    case Attributes::AcceptedCommandList::Id:
    case Attributes::AttributeList::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::MaxTemperature::Id:
    case Attributes::MinTemperature::Id:
    case Attributes::Step::Id:
    case Attributes::TemperatureSetpoint::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::SetTemperature::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace TemperatureControl
} // namespace Clusters
} // namespace app
} // namespace chip

