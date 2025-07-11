// DO NOT EDIT - Generated file
//
// Application configuration for ServiceArea based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/rvc-app/rvc-common/rvc-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/ServiceArea/AttributeIds.h>
#include <clusters/ServiceArea/CommandIds.h>
#include <clusters/ServiceArea/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace ServiceArea {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::CurrentArea::Id,
    Attributes::EstimatedEndTime::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::Progress::Id,
    Attributes::SelectedAreas::Id,
    Attributes::SupportedAreas::Id,
    Attributes::SupportedMaps::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::SelectAreas::Id,
    Commands::SelectAreasResponse::Id,
    Commands::SkipArea::Id,
    Commands::SkipAreaResponse::Id,
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
    case Attributes::CurrentArea::Id:
    case Attributes::EstimatedEndTime::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::Progress::Id:
    case Attributes::SelectedAreas::Id:
    case Attributes::SupportedAreas::Id:
    case Attributes::SupportedMaps::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::SelectAreas::Id:
    case Commands::SelectAreasResponse::Id:
    case Commands::SkipArea::Id:
    case Commands::SkipAreaResponse::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace ServiceArea
} // namespace Clusters
} // namespace app
} // namespace chip

