// DO NOT EDIT - Generated file
//
// Application configuration for KeypadInput based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/chef/devices/rootnode_basicvideoplayer_0ff86e943b.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/KeypadInput/AttributeIds.h>
#include <clusters/KeypadInput/CommandIds.h>
#include <clusters/KeypadInput/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace KeypadInput {
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
    Commands::SendKey::Id,
    Commands::SendKeyResponse::Id,
};

} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 1,
        .featureMap = BitFlags<FeatureBitmapType> {
            FeatureBitmapType::kNavigationKeyCodes, // feature bit 0x1
            FeatureBitmapType::kLocationKeys, // feature bit 0x2
            FeatureBitmapType::kNumberKeys// feature bit 0x4
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
    case Commands::SendKey::Id:
    case Commands::SendKeyResponse::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace KeypadInput
} // namespace Clusters
} // namespace app
} // namespace chip

