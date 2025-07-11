// DO NOT EDIT - Generated file
//
// Application configuration for ValveConfigurationAndControl based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/chef/devices/rootnode_watervalve_6bb39f1f67.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/ValveConfigurationAndControl/AttributeIds.h>
#include <clusters/ValveConfigurationAndControl/CommandIds.h>
#include <clusters/ValveConfigurationAndControl/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace ValveConfigurationAndControl {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::CurrentState::Id,
    Attributes::DefaultOpenDuration::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::OpenDuration::Id,
    Attributes::RemainingDuration::Id,
    Attributes::TargetState::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::Close::Id,
    Commands::Open::Id,
};

} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 1,
        .featureMap = BitFlags<FeatureBitmapType> {
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
    case Attributes::CurrentState::Id:
    case Attributes::DefaultOpenDuration::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::OpenDuration::Id:
    case Attributes::RemainingDuration::Id:
    case Attributes::TargetState::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::Close::Id:
    case Commands::Open::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace ValveConfigurationAndControl
} // namespace Clusters
} // namespace app
} // namespace chip

