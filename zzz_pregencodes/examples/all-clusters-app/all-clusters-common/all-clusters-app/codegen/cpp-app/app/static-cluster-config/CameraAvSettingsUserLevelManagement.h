// DO NOT EDIT - Generated file
//
// Application configuration for CameraAvSettingsUserLevelManagement based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/all-clusters-app/all-clusters-common/all-clusters-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/CameraAvSettingsUserLevelManagement/AttributeIds.h>
#include <clusters/CameraAvSettingsUserLevelManagement/CommandIds.h>
#include <clusters/CameraAvSettingsUserLevelManagement/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace CameraAvSettingsUserLevelManagement {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::DPTZStreams::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::MaxPresets::Id,
    Attributes::MPTZPosition::Id,
    Attributes::MPTZPresets::Id,
    Attributes::PanMax::Id,
    Attributes::PanMin::Id,
    Attributes::TiltMax::Id,
    Attributes::TiltMin::Id,
    Attributes::ZoomMax::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::DPTZRelativeMove::Id,
    Commands::DPTZSetViewport::Id,
    Commands::MPTZMoveToPreset::Id,
    Commands::MPTZRelativeMove::Id,
    Commands::MPTZRemovePreset::Id,
    Commands::MPTZSavePreset::Id,
    Commands::MPTZSetPosition::Id,
};

} // namespace detail

using FeatureBitmapType = Feature;

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
    case Attributes::DPTZStreams::Id:
    case Attributes::MPTZPosition::Id:
    case Attributes::MPTZPresets::Id:
    case Attributes::AcceptedCommandList::Id:
    case Attributes::AttributeList::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::MaxPresets::Id:
    case Attributes::PanMax::Id:
    case Attributes::PanMin::Id:
    case Attributes::TiltMax::Id:
    case Attributes::TiltMin::Id:
    case Attributes::ZoomMax::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::DPTZRelativeMove::Id:
    case Commands::DPTZSetViewport::Id:
    case Commands::MPTZMoveToPreset::Id:
    case Commands::MPTZRelativeMove::Id:
    case Commands::MPTZRemovePreset::Id:
    case Commands::MPTZSavePreset::Id:
    case Commands::MPTZSetPosition::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace CameraAvSettingsUserLevelManagement
} // namespace Clusters
} // namespace app
} // namespace chip

