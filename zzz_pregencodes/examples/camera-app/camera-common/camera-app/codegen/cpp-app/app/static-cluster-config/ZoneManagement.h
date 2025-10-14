// DO NOT EDIT - Generated file
//
// Application configuration for ZoneManagement based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/camera-app/camera-common/camera-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/ZoneManagement/AttributeIds.h>
#include <clusters/ZoneManagement/CommandIds.h>
#include <clusters/ZoneManagement/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace ZoneManagement {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::MaxUserDefinedZones::Id,
    Attributes::MaxZones::Id,
    Attributes::Sensitivity::Id,
    Attributes::SensitivityMax::Id,
    Attributes::Triggers::Id,
    Attributes::TwoDCartesianMax::Id,
    Attributes::Zones::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::CreateOrUpdateTrigger::Id,
    Commands::CreateTwoDCartesianZone::Id,
    Commands::CreateTwoDCartesianZoneResponse::Id,
    Commands::RemoveTrigger::Id,
    Commands::RemoveZone::Id,
    Commands::UpdateTwoDCartesianZone::Id,
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
    case Attributes::AcceptedCommandList::Id:
    case Attributes::AttributeList::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::MaxUserDefinedZones::Id:
    case Attributes::MaxZones::Id:
    case Attributes::Sensitivity::Id:
    case Attributes::SensitivityMax::Id:
    case Attributes::Triggers::Id:
    case Attributes::TwoDCartesianMax::Id:
    case Attributes::Zones::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::CreateOrUpdateTrigger::Id:
    case Commands::CreateTwoDCartesianZone::Id:
    case Commands::CreateTwoDCartesianZoneResponse::Id:
    case Commands::RemoveTrigger::Id:
    case Commands::RemoveZone::Id:
    case Commands::UpdateTwoDCartesianZone::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace ZoneManagement
} // namespace Clusters
} // namespace app
} // namespace chip

