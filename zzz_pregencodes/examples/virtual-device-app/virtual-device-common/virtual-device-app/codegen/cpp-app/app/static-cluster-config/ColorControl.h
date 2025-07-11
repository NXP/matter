// DO NOT EDIT - Generated file
//
// Application configuration for ColorControl based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/virtual-device-app/virtual-device-common/virtual-device-app.matter
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
    Attributes::CurrentHue::Id,
    Attributes::CurrentSaturation::Id,
    Attributes::CurrentX::Id,
    Attributes::CurrentY::Id,
    Attributes::EnhancedColorMode::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::NumberOfPrimaries::Id,
    Attributes::Options::Id,
    Attributes::RemainingTime::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::MoveToColor::Id,
    Commands::MoveToColorTemperature::Id,
    Commands::MoveToHue::Id,
    Commands::MoveToHueAndSaturation::Id,
    Commands::MoveToSaturation::Id,
};

} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 1,
        .featureMap = BitFlags<FeatureBitmapType> {
            FeatureBitmapType::kHueAndSaturation// feature bit 0x1
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
    case Attributes::ColorTemperatureMireds::Id:
    case Attributes::CurrentHue::Id:
    case Attributes::CurrentSaturation::Id:
    case Attributes::CurrentX::Id:
    case Attributes::CurrentY::Id:
    case Attributes::EnhancedColorMode::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::NumberOfPrimaries::Id:
    case Attributes::Options::Id:
    case Attributes::RemainingTime::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::MoveToColor::Id:
    case Commands::MoveToColorTemperature::Id:
    case Commands::MoveToHue::Id:
    case Commands::MoveToHueAndSaturation::Id:
    case Commands::MoveToSaturation::Id:
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

