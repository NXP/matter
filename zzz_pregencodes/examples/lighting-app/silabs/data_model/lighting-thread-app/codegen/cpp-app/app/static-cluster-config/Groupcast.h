// DO NOT EDIT - Generated file
//
// Application configuration for Groupcast based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/lighting-app/silabs/data_model/lighting-thread-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/Groupcast/AttributeIds.h>
#include <clusters/Groupcast/CommandIds.h>
#include <clusters/Groupcast/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace Groupcast {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint0EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id, Attributes::AttributeList::Id,      Attributes::ClusterRevision::Id,
    Attributes::FabricUnderTest::Id,     Attributes::FeatureMap::Id,         Attributes::GeneratedCommandList::Id,
    Attributes::MaxMcastAddrCount::Id,   Attributes::MaxMembershipCount::Id, Attributes::Membership::Id,
    Attributes::UsedMcastAddrCount::Id,
};

inline constexpr CommandId kEndpoint0EnabledCommands[] = {
    Commands::ConfigureAuxiliaryACL::Id, Commands::GroupcastTesting::Id, Commands::JoinGroup::Id, Commands::LeaveGroup::Id,
    Commands::UpdateGroupKey::Id,
};

} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 0,
        .featureMap =
            BitFlags<FeatureBitmapType>{
                FeatureBitmapType::kListener // feature bit 0x1
            },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint0EnabledAttributes),
        .enabledCommands   = Span<const CommandId>(detail::kEndpoint0EnabledCommands),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId)
{
    switch (attributeId)
    {
    case Attributes::AcceptedCommandList::Id:
    case Attributes::AttributeList::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::FabricUnderTest::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::MaxMcastAddrCount::Id:
    case Attributes::MaxMembershipCount::Id:
    case Attributes::Membership::Id:
    case Attributes::UsedMcastAddrCount::Id:
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
    case Commands::ConfigureAuxiliaryACL::Id:
    case Commands::GroupcastTesting::Id:
    case Commands::JoinGroup::Id:
    case Commands::LeaveGroup::Id:
    case Commands::UpdateGroupKey::Id:
        return true;
    default:
        return false;
    }
}

} // namespace StaticApplicationConfig
} // namespace Groupcast
} // namespace Clusters
} // namespace app
} // namespace chip
