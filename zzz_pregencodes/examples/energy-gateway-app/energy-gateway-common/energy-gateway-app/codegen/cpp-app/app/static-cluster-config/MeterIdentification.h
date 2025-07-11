// DO NOT EDIT - Generated file
//
// Application configuration for MeterIdentification based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/energy-gateway-app/energy-gateway-common/energy-gateway-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/MeterIdentification/AttributeIds.h>
#include <clusters/MeterIdentification/CommandIds.h>
#include <clusters/MeterIdentification/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace MeterIdentification {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::MeterSerialNumber::Id,
    Attributes::MeterType::Id,
    Attributes::PointOfDelivery::Id,
    Attributes::PowerThreshold::Id,
    Attributes::ProtocolVersion::Id,
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
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::MeterSerialNumber::Id:
    case Attributes::MeterType::Id:
    case Attributes::PointOfDelivery::Id:
    case Attributes::PowerThreshold::Id:
    case Attributes::ProtocolVersion::Id:
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
} // namespace MeterIdentification
} // namespace Clusters
} // namespace app
} // namespace chip

