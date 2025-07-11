// DO NOT EDIT - Generated file
//
// Application configuration for SampleMei based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/chef/devices/rootnode_onofflight_samplemei.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/SampleMei/AttributeIds.h>
#include <clusters/SampleMei/CommandIds.h>
#include <clusters/SampleMei/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace SampleMei {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::FlipFlop::Id,
    Attributes::GeneratedCommandList::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::AddArguments::Id,
    Commands::AddArgumentsResponse::Id,
    Commands::Ping::Id,
};

} // namespace detail

using FeatureBitmapType = Clusters::StaticApplicationConfig::NoFeatureFlagsDefined;

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
    case Attributes::FeatureMap::Id:
    case Attributes::FlipFlop::Id:
    case Attributes::GeneratedCommandList::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::AddArguments::Id:
    case Commands::AddArgumentsResponse::Id:
    case Commands::Ping::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace SampleMei
} // namespace Clusters
} // namespace app
} // namespace chip

