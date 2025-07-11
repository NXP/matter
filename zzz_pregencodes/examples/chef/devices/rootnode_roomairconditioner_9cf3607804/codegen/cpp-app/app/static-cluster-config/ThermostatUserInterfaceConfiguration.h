// DO NOT EDIT - Generated file
//
// Application configuration for ThermostatUserInterfaceConfiguration based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/chef/devices/rootnode_roomairconditioner_9cf3607804.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/ThermostatUserInterfaceConfiguration/AttributeIds.h>
#include <clusters/ThermostatUserInterfaceConfiguration/CommandIds.h>
#include <clusters/ThermostatUserInterfaceConfiguration/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace ThermostatUserInterfaceConfiguration {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::KeypadLockout::Id,
    Attributes::TemperatureDisplayMode::Id,
};
} // namespace detail

using FeatureBitmapType = Clusters::StaticApplicationConfig::NoFeatureFlagsDefined;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 1,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint1EnabledAttributes),
        .enabledCommands = Span<const CommandId>(),
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
    case Attributes::KeypadLockout::Id:
    case Attributes::TemperatureDisplayMode::Id:
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
} // namespace ThermostatUserInterfaceConfiguration
} // namespace Clusters
} // namespace app
} // namespace chip

