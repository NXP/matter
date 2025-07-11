// DO NOT EDIT - Generated file
//
// Application configuration for OccupancySensing based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/chef/devices/rootnode_contactsensor_lightsensor_occupancysensor_temperaturesensor_pressuresensor_flowsensor_humiditysensor_airqualitysensor_powersource_367e7cea91.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/OccupancySensing/AttributeIds.h>
#include <clusters/OccupancySensing/CommandIds.h>
#include <clusters/OccupancySensing/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace OccupancySensing {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint3EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::HoldTime::Id,
    Attributes::HoldTimeLimits::Id,
    Attributes::Occupancy::Id,
    Attributes::OccupancySensorType::Id,
    Attributes::OccupancySensorTypeBitmap::Id,
};
} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 3,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint3EnabledAttributes),
        .enabledCommands = Span<const CommandId>(),
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
    case Attributes::HoldTime::Id:
    case Attributes::HoldTimeLimits::Id:
    case Attributes::Occupancy::Id:
    case Attributes::OccupancySensorType::Id:
    case Attributes::OccupancySensorTypeBitmap::Id:
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
} // namespace OccupancySensing
} // namespace Clusters
} // namespace app
} // namespace chip

