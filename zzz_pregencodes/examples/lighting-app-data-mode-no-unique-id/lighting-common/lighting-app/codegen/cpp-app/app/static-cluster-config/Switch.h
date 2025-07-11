// DO NOT EDIT - Generated file
//
// Application configuration for Switch based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/lighting-app-data-mode-no-unique-id/lighting-common/lighting-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/Switch/AttributeIds.h>
#include <clusters/Switch/CommandIds.h>
#include <clusters/Switch/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace Switch {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint0EnabledAttributes[] = {
    Attributes::ClusterRevision::Id,
    Attributes::CurrentPosition::Id,
    Attributes::FeatureMap::Id,
    Attributes::NumberOfPositions::Id,
};
} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 0,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint0EnabledAttributes),
        .enabledCommands = Span<const CommandId>(),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId) {
  switch (attributeId) {
    case Attributes::ClusterRevision::Id:
    case Attributes::CurrentPosition::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::NumberOfPositions::Id:
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
} // namespace Switch
} // namespace Clusters
} // namespace app
} // namespace chip

