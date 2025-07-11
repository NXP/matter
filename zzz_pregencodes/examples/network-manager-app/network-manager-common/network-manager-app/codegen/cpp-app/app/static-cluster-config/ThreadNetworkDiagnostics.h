// DO NOT EDIT - Generated file
//
// Application configuration for ThreadNetworkDiagnostics based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/network-manager-app/network-manager-common/network-manager-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/ThreadNetworkDiagnostics/AttributeIds.h>
#include <clusters/ThreadNetworkDiagnostics/CommandIds.h>
#include <clusters/ThreadNetworkDiagnostics/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace ThreadNetworkDiagnostics {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint0EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::ActiveNetworkFaultsList::Id,
    Attributes::AttributeList::Id,
    Attributes::Channel::Id,
    Attributes::ChannelPage0Mask::Id,
    Attributes::ClusterRevision::Id,
    Attributes::DataVersion::Id,
    Attributes::ExtendedPanId::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::LeaderRouterId::Id,
    Attributes::MeshLocalPrefix::Id,
    Attributes::NeighborTable::Id,
    Attributes::NetworkName::Id,
    Attributes::OperationalDatasetComponents::Id,
    Attributes::PanId::Id,
    Attributes::PartitionId::Id,
    Attributes::RouteTable::Id,
    Attributes::RoutingRole::Id,
    Attributes::SecurityPolicy::Id,
    Attributes::StableDataVersion::Id,
    Attributes::Weighting::Id,
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
    case Attributes::AcceptedCommandList::Id:
    case Attributes::ActiveNetworkFaultsList::Id:
    case Attributes::AttributeList::Id:
    case Attributes::Channel::Id:
    case Attributes::ChannelPage0Mask::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::DataVersion::Id:
    case Attributes::ExtendedPanId::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::LeaderRouterId::Id:
    case Attributes::MeshLocalPrefix::Id:
    case Attributes::NeighborTable::Id:
    case Attributes::NetworkName::Id:
    case Attributes::OperationalDatasetComponents::Id:
    case Attributes::PanId::Id:
    case Attributes::PartitionId::Id:
    case Attributes::RouteTable::Id:
    case Attributes::RoutingRole::Id:
    case Attributes::SecurityPolicy::Id:
    case Attributes::StableDataVersion::Id:
    case Attributes::Weighting::Id:
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
} // namespace ThreadNetworkDiagnostics
} // namespace Clusters
} // namespace app
} // namespace chip

