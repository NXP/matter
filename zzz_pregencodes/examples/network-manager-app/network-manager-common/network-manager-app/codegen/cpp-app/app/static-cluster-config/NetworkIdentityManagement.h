// DO NOT EDIT - Generated file
//
// Application configuration for NetworkIdentityManagement based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/network-manager-app/network-manager-common/network-manager-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/NetworkIdentityManagement/AttributeIds.h>
#include <clusters/NetworkIdentityManagement/CommandIds.h>
#include <clusters/NetworkIdentityManagement/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace NetworkIdentityManagement {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id, Attributes::ActiveNetworkIdentities::Id,
    Attributes::AttributeList::Id,       Attributes::Clients::Id,
    Attributes::ClientTableSize::Id,     Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,          Attributes::GeneratedCommandList::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::AddClient::Id,     Commands::ExportAdminSecret::Id, Commands::ImportAdminSecret::Id,
    Commands::QueryIdentity::Id, Commands::RemoveClient::Id,
};

} // namespace detail

using FeatureBitmapType = Clusters::StaticApplicationConfig::NoFeatureFlagsDefined;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber    = 1,
        .featureMap        = BitFlags<FeatureBitmapType>{},
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint1EnabledAttributes),
        .enabledCommands   = Span<const CommandId>(detail::kEndpoint1EnabledCommands),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId)
{
    switch (attributeId)
    {
    case Attributes::AcceptedCommandList::Id:
    case Attributes::ActiveNetworkIdentities::Id:
    case Attributes::AttributeList::Id:
    case Attributes::ClientTableSize::Id:
    case Attributes::Clients::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
        return true;
    default:
        return false;
    }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId)
{
    switch (commandId)
    {
    case Commands::AddClient::Id:
    case Commands::ExportAdminSecret::Id:
    case Commands::ImportAdminSecret::Id:
    case Commands::QueryIdentity::Id:
    case Commands::RemoveClient::Id:
        return true;
    default:
        return false;
    }
}

} // namespace StaticApplicationConfig
} // namespace NetworkIdentityManagement
} // namespace Clusters
} // namespace app
} // namespace chip
