// DO NOT EDIT - Generated file
//
// Application configuration for TlsClientManagement based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/all-clusters-app/all-clusters-common/all-clusters-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/TlsClientManagement/AttributeIds.h>
#include <clusters/TlsClientManagement/CommandIds.h>
#include <clusters/TlsClientManagement/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace TlsClientManagement {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::MaxProvisioned::Id,
    Attributes::ProvisionedEndpoints::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::FindEndpoint::Id,
    Commands::FindEndpointResponse::Id,
    Commands::ProvisionEndpoint::Id,
    Commands::ProvisionEndpointResponse::Id,
    Commands::RemoveEndpoint::Id,
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
    case Attributes::MaxProvisioned::Id:
    case Attributes::ProvisionedEndpoints::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::FindEndpoint::Id:
    case Commands::FindEndpointResponse::Id:
    case Commands::ProvisionEndpoint::Id:
    case Commands::ProvisionEndpointResponse::Id:
    case Commands::RemoveEndpoint::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace TlsClientManagement
} // namespace Clusters
} // namespace app
} // namespace chip

