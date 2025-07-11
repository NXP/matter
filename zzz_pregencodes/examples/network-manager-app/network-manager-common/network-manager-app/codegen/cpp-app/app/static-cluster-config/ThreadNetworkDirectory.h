// DO NOT EDIT - Generated file
//
// Application configuration for ThreadNetworkDirectory based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/network-manager-app/network-manager-common/network-manager-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/ThreadNetworkDirectory/AttributeIds.h>
#include <clusters/ThreadNetworkDirectory/CommandIds.h>
#include <clusters/ThreadNetworkDirectory/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace ThreadNetworkDirectory {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::PreferredExtendedPanID::Id,
    Attributes::ThreadNetworks::Id,
    Attributes::ThreadNetworkTableSize::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::AddNetwork::Id,
    Commands::GetOperationalDataset::Id,
    Commands::OperationalDatasetResponse::Id,
    Commands::RemoveNetwork::Id,
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
    case Attributes::PreferredExtendedPanID::Id:
    case Attributes::ThreadNetworkTableSize::Id:
    case Attributes::ThreadNetworks::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::AddNetwork::Id:
    case Commands::GetOperationalDataset::Id:
    case Commands::OperationalDatasetResponse::Id:
    case Commands::RemoveNetwork::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace ThreadNetworkDirectory
} // namespace Clusters
} // namespace app
} // namespace chip

