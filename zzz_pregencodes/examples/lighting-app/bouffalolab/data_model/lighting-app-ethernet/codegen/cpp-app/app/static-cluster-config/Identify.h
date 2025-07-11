// DO NOT EDIT - Generated file
//
// Application configuration for Identify based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/lighting-app/bouffalolab/data_model/lighting-app-ethernet.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/Identify/AttributeIds.h>
#include <clusters/Identify/CommandIds.h>
#include <clusters/Identify/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace Identify {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::IdentifyTime::Id,
    Attributes::IdentifyType::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::Identify::Id,
    Commands::TriggerEffect::Id,
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
    case Attributes::ClusterRevision::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::IdentifyTime::Id:
    case Attributes::IdentifyType::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::Identify::Id:
    case Commands::TriggerEffect::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace Identify
} // namespace Clusters
} // namespace app
} // namespace chip

