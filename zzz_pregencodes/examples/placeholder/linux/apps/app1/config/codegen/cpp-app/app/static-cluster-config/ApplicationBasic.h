// DO NOT EDIT - Generated file
//
// Application configuration for ApplicationBasic based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/placeholder/linux/apps/app1/config.matter
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
inline constexpr AttributeId kEndpoint0EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AllowedVendorList::Id,
    Attributes::Application::Id,
    Attributes::ApplicationName::Id,
    Attributes::ApplicationVersion::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::ProductID::Id,
    Attributes::Status::Id,
    Attributes::VendorID::Id,
    Attributes::VendorName::Id,
};
} // namespace detail

using FeatureBitmapType = Clusters::StaticApplicationConfig::NoFeatureFlagsDefined;

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
    case Attributes::AcceptedCommandList::Id:
    case Attributes::AllowedVendorList::Id:
    case Attributes::Application::Id:
    case Attributes::ApplicationName::Id:
    case Attributes::ApplicationVersion::Id:
    case Attributes::AttributeList::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::ProductID::Id:
    case Attributes::Status::Id:
    case Attributes::VendorID::Id:
    case Attributes::VendorName::Id:
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

