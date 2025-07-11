// DO NOT EDIT - Generated file
//
// Application configuration for ContentAppObserver based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/tv-casting-app/tv-casting-common/tv-casting-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/ContentAppObserver/AttributeIds.h>
#include <clusters/ContentAppObserver/CommandIds.h>
#include <clusters/ContentAppObserver/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace ContentAppObserver {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::ContentAppMessage::Id,
    Commands::ContentAppMessageResponse::Id,
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
    case Attributes::GeneratedCommandList::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::ContentAppMessage::Id:
    case Commands::ContentAppMessageResponse::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace ContentAppObserver
} // namespace Clusters
} // namespace app
} // namespace chip

