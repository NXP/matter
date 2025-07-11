// DO NOT EDIT - Generated file
//
// Application configuration for AudioOutput based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/all-clusters-minimal-app/all-clusters-common/all-clusters-minimal-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/AudioOutput/AttributeIds.h>
#include <clusters/AudioOutput/CommandIds.h>
#include <clusters/AudioOutput/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace AudioOutput {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::ClusterRevision::Id,
    Attributes::CurrentOutput::Id,
    Attributes::FeatureMap::Id,
    Attributes::OutputList::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::SelectOutput::Id,
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
    case Attributes::ClusterRevision::Id:
    case Attributes::CurrentOutput::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::OutputList::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::SelectOutput::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace AudioOutput
} // namespace Clusters
} // namespace app
} // namespace chip

