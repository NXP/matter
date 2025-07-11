// DO NOT EDIT - Generated file
//
// Application configuration for IcdManagement based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/chef/devices/rootnode_extractorhood_0359bf807d.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/IcdManagement/AttributeIds.h>
#include <clusters/IcdManagement/CommandIds.h>
#include <clusters/IcdManagement/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace IcdManagement {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint0EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::ActiveModeDuration::Id,
    Attributes::ActiveModeThreshold::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::IdleModeDuration::Id,
    Attributes::UserActiveModeTriggerInstruction::Id,
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
    case Attributes::ActiveModeDuration::Id:
    case Attributes::ActiveModeThreshold::Id:
    case Attributes::AttributeList::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::IdleModeDuration::Id:
    case Attributes::UserActiveModeTriggerInstruction::Id:
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
} // namespace IcdManagement
} // namespace Clusters
} // namespace app
} // namespace chip

