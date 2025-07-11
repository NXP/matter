// DO NOT EDIT - Generated file
//
// Application configuration for FanControl based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/all-clusters-minimal-app/all-clusters-common/all-clusters-minimal-app.matter
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
    Attributes::ClusterRevision::Id,
    Attributes::FanMode::Id,
    Attributes::FanModeSequence::Id,
    Attributes::FeatureMap::Id,
    Attributes::PercentCurrent::Id,
    Attributes::PercentSetting::Id,
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
    case Attributes::ClusterRevision::Id:
    case Attributes::FanMode::Id:
    case Attributes::FanModeSequence::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::PercentCurrent::Id:
    case Attributes::PercentSetting::Id:
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

