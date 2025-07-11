// DO NOT EDIT - Generated file
//
// Application configuration for ApplicationBasic based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/all-clusters-minimal-app/all-clusters-common/all-clusters-minimal-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/ApplicationBasic/AttributeIds.h>
#include <clusters/ApplicationBasic/CommandIds.h>
#include <clusters/ApplicationBasic/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace ApplicationBasic {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AllowedVendorList::Id,
    Attributes::Application::Id,
    Attributes::ApplicationName::Id,
    Attributes::ApplicationVersion::Id,
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::Status::Id,
};
} // namespace detail

using FeatureBitmapType = Clusters::StaticApplicationConfig::NoFeatureFlagsDefined;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 1,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint1EnabledAttributes),
        .enabledCommands = Span<const CommandId>(),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId) {
  switch (attributeId) {
    case Attributes::AllowedVendorList::Id:
    case Attributes::Application::Id:
    case Attributes::ApplicationName::Id:
    case Attributes::ApplicationVersion::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::Status::Id:
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
} // namespace ApplicationBasic
} // namespace Clusters
} // namespace app
} // namespace chip

