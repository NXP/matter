// DO NOT EDIT - Generated file
//
// Application configuration for ApplicationLauncher based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/placeholder/linux/apps/app2/config.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/ApplicationLauncher/AttributeIds.h>
#include <clusters/ApplicationLauncher/CommandIds.h>
#include <clusters/ApplicationLauncher/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace ApplicationLauncher {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint0EnabledAttributes[] = {
    Attributes::CatalogList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::CurrentApp::Id,
    Attributes::FeatureMap::Id,
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
    case Attributes::CatalogList::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::CurrentApp::Id:
    case Attributes::FeatureMap::Id:
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
} // namespace ApplicationLauncher
} // namespace Clusters
} // namespace app
} // namespace chip

