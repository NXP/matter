// DO NOT EDIT - Generated file
//
// Application configuration for TargetNavigator based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/tv-app/tv-common/tv-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/TargetNavigator/AttributeIds.h>
#include <clusters/TargetNavigator/CommandIds.h>
#include <clusters/TargetNavigator/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace TargetNavigator {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::ClusterRevision::Id,
    Attributes::CurrentTarget::Id,
    Attributes::FeatureMap::Id,
    Attributes::TargetList::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::NavigateTarget::Id,
    Commands::NavigateTargetResponse::Id,
};

inline constexpr AttributeId kEndpoint3EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::TargetList::Id,
};

inline constexpr CommandId kEndpoint3EnabledCommands[] = {
    Commands::NavigateTarget::Id,
    Commands::NavigateTargetResponse::Id,
};

} // namespace detail

using FeatureBitmapType = Clusters::StaticApplicationConfig::NoFeatureFlagsDefined;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 2> kFixedClusterConfig = { {
    {
        .endpointNumber = 1,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint1EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint1EnabledCommands),
    },
    {
        .endpointNumber = 3,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint3EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint3EnabledCommands),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId) {
  switch (attributeId) {
    case Attributes::AcceptedCommandList::Id:
    case Attributes::AttributeList::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::CurrentTarget::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::TargetList::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::NavigateTarget::Id:
    case Commands::NavigateTargetResponse::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace TargetNavigator
} // namespace Clusters
} // namespace app
} // namespace chip

