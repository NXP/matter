// DO NOT EDIT - Generated file
//
// Application configuration for ColorControl based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/chef/devices/rootnode_colortemperaturelight_hbUnzYVeyn.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/ColorControl/AttributeIds.h>
#include <clusters/ColorControl/CommandIds.h>
#include <clusters/ColorControl/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace ColorControl {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::ColorCapabilities::Id,
    Attributes::ColorMode::Id,
    Attributes::ColorTemperatureMireds::Id,
    Attributes::ColorTempPhysicalMaxMireds::Id,
    Attributes::ColorTempPhysicalMinMireds::Id,
    Attributes::CoupleColorTempToLevelMinMireds::Id,
    Attributes::EnhancedColorMode::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::NumberOfPrimaries::Id,
    Attributes::Options::Id,
    Attributes::RemainingTime::Id,
    Attributes::StartUpColorTemperatureMireds::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::ColorLoopSet::Id,
    Commands::EnhancedMoveHue::Id,
    Commands::EnhancedMoveToHueAndSaturation::Id,
    Commands::EnhancedStepHue::Id,
    Commands::MoveColorTemperature::Id,
    Commands::MoveToColorTemperature::Id,
    Commands::StepColorTemperature::Id,
    Commands::StopMoveStep::Id,
};

} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 1,
        .featureMap = BitFlags<FeatureBitmapType> {
            FeatureBitmapType::kColorTemperature// feature bit 0x10
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
    case Attributes::ColorCapabilities::Id:
    case Attributes::ColorMode::Id:
    case Attributes::ColorTempPhysicalMaxMireds::Id:
    case Attributes::ColorTempPhysicalMinMireds::Id:
    case Attributes::ColorTemperatureMireds::Id:
    case Attributes::CoupleColorTempToLevelMinMireds::Id:
    case Attributes::EnhancedColorMode::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::NumberOfPrimaries::Id:
    case Attributes::Options::Id:
    case Attributes::RemainingTime::Id:
    case Attributes::StartUpColorTemperatureMireds::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::ColorLoopSet::Id:
    case Commands::EnhancedMoveHue::Id:
    case Commands::EnhancedMoveToHueAndSaturation::Id:
    case Commands::EnhancedStepHue::Id:
    case Commands::MoveColorTemperature::Id:
    case Commands::MoveToColorTemperature::Id:
    case Commands::StepColorTemperature::Id:
    case Commands::StopMoveStep::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace ColorControl
} // namespace Clusters
} // namespace app
} // namespace chip

