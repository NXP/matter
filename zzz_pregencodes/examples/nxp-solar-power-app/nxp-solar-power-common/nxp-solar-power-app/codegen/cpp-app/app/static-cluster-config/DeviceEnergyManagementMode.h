// DO NOT EDIT - Generated file
//
// Application configuration for DeviceEnergyManagementMode based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/nxp-solar-power-app/nxp-solar-power-common/nxp-solar-power-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/DeviceEnergyManagementMode/AttributeIds.h>
#include <clusters/DeviceEnergyManagementMode/CommandIds.h>
#include <clusters/DeviceEnergyManagementMode/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace DeviceEnergyManagementMode {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint2EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::CurrentMode::Id,
    Attributes::EventList::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::SupportedModes::Id,
};

inline constexpr CommandId kEndpoint2EnabledCommands[] = {
    Commands::ChangeToMode::Id,
    Commands::ChangeToModeResponse::Id,
};

} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 2,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint2EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint2EnabledCommands),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId) {
  switch (attributeId) {
    case Attributes::AcceptedCommandList::Id:
    case Attributes::AttributeList::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::CurrentMode::Id:
    case Attributes::EventList::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::SupportedModes::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::ChangeToMode::Id:
    case Commands::ChangeToModeResponse::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace DeviceEnergyManagementMode
} // namespace Clusters
} // namespace app
} // namespace chip

