// DO NOT EDIT - Generated file
//
// Application configuration for Channel based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/placeholder/linux/apps/app2/config.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/Channel/AttributeIds.h>
#include <clusters/Channel/CommandIds.h>
#include <clusters/Channel/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace Channel {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint0EnabledAttributes[] = {
    Attributes::ChannelList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::CurrentChannel::Id,
    Attributes::FeatureMap::Id,
    Attributes::Lineup::Id,
};

inline constexpr CommandId kEndpoint0EnabledCommands[] = {
    Commands::ChangeChannel::Id,
    Commands::ChangeChannelByNumber::Id,
    Commands::SkipChannel::Id,
};

} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 0,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint0EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint0EnabledCommands),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId) {
  switch (attributeId) {
    case Attributes::ChannelList::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::CurrentChannel::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::Lineup::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::ChangeChannel::Id:
    case Commands::ChangeChannelByNumber::Id:
    case Commands::SkipChannel::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace Channel
} // namespace Clusters
} // namespace app
} // namespace chip

