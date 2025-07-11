// DO NOT EDIT - Generated file
//
// Application configuration for ElectricalGridConditions based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/energy-gateway-app/energy-gateway-common/energy-gateway-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/ElectricalGridConditions/AttributeIds.h>
#include <clusters/ElectricalGridConditions/CommandIds.h>
#include <clusters/ElectricalGridConditions/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace ElectricalGridConditions {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::CurrentConditions::Id,
    Attributes::FeatureMap::Id,
    Attributes::ForecastConditions::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::LocalGenerationAvailable::Id,
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
    case Attributes::ClusterRevision::Id:
    case Attributes::CurrentConditions::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::ForecastConditions::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::LocalGenerationAvailable::Id:
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
} // namespace ElectricalGridConditions
} // namespace Clusters
} // namespace app
} // namespace chip

