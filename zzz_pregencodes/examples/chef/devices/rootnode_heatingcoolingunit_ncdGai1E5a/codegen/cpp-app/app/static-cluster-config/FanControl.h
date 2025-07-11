// DO NOT EDIT - Generated file
//
// Application configuration for FanControl based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/chef/devices/rootnode_heatingcoolingunit_ncdGai1E5a.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/FanControl/AttributeIds.h>
#include <clusters/FanControl/CommandIds.h>
#include <clusters/FanControl/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace FanControl {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::FanMode::Id,
    Attributes::FanModeSequence::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::PercentCurrent::Id,
    Attributes::PercentSetting::Id,
    Attributes::SpeedCurrent::Id,
    Attributes::SpeedMax::Id,
    Attributes::SpeedSetting::Id,
};
} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 1,
        .featureMap = BitFlags<FeatureBitmapType> {
            FeatureBitmapType::kMultiSpeed, // feature bit 0x1
            FeatureBitmapType::kAuto// feature bit 0x2
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
    case Attributes::ClusterRevision::Id:
    case Attributes::FanMode::Id:
    case Attributes::FanModeSequence::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::PercentCurrent::Id:
    case Attributes::PercentSetting::Id:
    case Attributes::SpeedCurrent::Id:
    case Attributes::SpeedMax::Id:
    case Attributes::SpeedSetting::Id:
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
} // namespace FanControl
} // namespace Clusters
} // namespace app
} // namespace chip

