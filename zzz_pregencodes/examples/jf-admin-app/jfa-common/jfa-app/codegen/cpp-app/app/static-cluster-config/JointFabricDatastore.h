// DO NOT EDIT - Generated file
//
// Application configuration for JointFabricDatastore based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/jf-admin-app/jfa-common/jfa-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/JointFabricDatastore/AttributeIds.h>
#include <clusters/JointFabricDatastore/CommandIds.h>
#include <clusters/JointFabricDatastore/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace JointFabricDatastore {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AdminList::Id,
    Attributes::AnchorNodeID::Id,
    Attributes::AnchorRootCA::Id,
    Attributes::AnchorVendorID::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::EndpointBindingList::Id,
    Attributes::EndpointGroupIDList::Id,
    Attributes::FeatureMap::Id,
    Attributes::FriendlyName::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::GroupKeySetList::Id,
    Attributes::GroupList::Id,
    Attributes::NodeACLList::Id,
    Attributes::NodeEndpointList::Id,
    Attributes::NodeKeySetList::Id,
    Attributes::NodeList::Id,
    Attributes::Status::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::AddACLToNode::Id,
    Commands::AddAdmin::Id,
    Commands::AddBindingToEndpointForNode::Id,
    Commands::AddGroup::Id,
    Commands::AddGroupIDToEndpointForNode::Id,
    Commands::AddKeySet::Id,
    Commands::AddPendingNode::Id,
    Commands::RefreshNode::Id,
    Commands::RemoveACLFromNode::Id,
    Commands::RemoveAdmin::Id,
    Commands::RemoveBindingFromEndpointForNode::Id,
    Commands::RemoveGroup::Id,
    Commands::RemoveGroupIDFromEndpointForNode::Id,
    Commands::RemoveKeySet::Id,
    Commands::RemoveNode::Id,
    Commands::UpdateAdmin::Id,
    Commands::UpdateEndpointForNode::Id,
    Commands::UpdateGroup::Id,
    Commands::UpdateKeySet::Id,
    Commands::UpdateNode::Id,
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
    case Attributes::AdminList::Id:
    case Attributes::AnchorNodeID::Id:
    case Attributes::AnchorRootCA::Id:
    case Attributes::AnchorVendorID::Id:
    case Attributes::AttributeList::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::EndpointBindingList::Id:
    case Attributes::EndpointGroupIDList::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::FriendlyName::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::GroupKeySetList::Id:
    case Attributes::GroupList::Id:
    case Attributes::NodeACLList::Id:
    case Attributes::NodeEndpointList::Id:
    case Attributes::NodeKeySetList::Id:
    case Attributes::NodeList::Id:
    case Attributes::Status::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::AddACLToNode::Id:
    case Commands::AddAdmin::Id:
    case Commands::AddBindingToEndpointForNode::Id:
    case Commands::AddGroup::Id:
    case Commands::AddGroupIDToEndpointForNode::Id:
    case Commands::AddKeySet::Id:
    case Commands::AddPendingNode::Id:
    case Commands::RefreshNode::Id:
    case Commands::RemoveACLFromNode::Id:
    case Commands::RemoveAdmin::Id:
    case Commands::RemoveBindingFromEndpointForNode::Id:
    case Commands::RemoveGroup::Id:
    case Commands::RemoveGroupIDFromEndpointForNode::Id:
    case Commands::RemoveKeySet::Id:
    case Commands::RemoveNode::Id:
    case Commands::UpdateAdmin::Id:
    case Commands::UpdateEndpointForNode::Id:
    case Commands::UpdateGroup::Id:
    case Commands::UpdateKeySet::Id:
    case Commands::UpdateNode::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace JointFabricDatastore
} // namespace Clusters
} // namespace app
} // namespace chip

