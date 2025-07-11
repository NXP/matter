// DO NOT EDIT - Generated file
//
// Application configuration for PumpConfigurationAndControl based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/chef/devices/rootnode_pump_5f904818cc.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/PumpConfigurationAndControl/AttributeIds.h>
#include <clusters/PumpConfigurationAndControl/CommandIds.h>
#include <clusters/PumpConfigurationAndControl/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace PumpConfigurationAndControl {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::Capacity::Id,
    Attributes::ClusterRevision::Id,
    Attributes::EffectiveControlMode::Id,
    Attributes::EffectiveOperationMode::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::MaxFlow::Id,
    Attributes::MaxPressure::Id,
    Attributes::MaxSpeed::Id,
    Attributes::OperationMode::Id,
    Attributes::PumpStatus::Id,
};
} // namespace detail

using FeatureBitmapType = Feature;

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
    case Attributes::AcceptedCommandList::Id:
    case Attributes::AttributeList::Id:
    case Attributes::Capacity::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::EffectiveControlMode::Id:
    case Attributes::EffectiveOperationMode::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::MaxFlow::Id:
    case Attributes::MaxPressure::Id:
    case Attributes::MaxSpeed::Id:
    case Attributes::OperationMode::Id:
    case Attributes::PumpStatus::Id:
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
} // namespace PumpConfigurationAndControl
} // namespace Clusters
} // namespace app
} // namespace chip

