// DO NOT EDIT - Generated file
//
// Application configuration for IlluminanceMeasurement based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/bridge-app/nxp/linux-M2ZigbeeRcp-bridge/M2ZigbeeRcp-bridge-zap/M2ZigbeeRcp-bridge-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/IlluminanceMeasurement/AttributeIds.h>
#include <clusters/IlluminanceMeasurement/CommandIds.h>
#include <clusters/IlluminanceMeasurement/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace IlluminanceMeasurement {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint2EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::EventList::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::LightSensorType::Id,
    Attributes::MaxMeasuredValue::Id,
    Attributes::MeasuredValue::Id,
    Attributes::MinMeasuredValue::Id,
    Attributes::Tolerance::Id,
};
} // namespace detail

using FeatureBitmapType = Clusters::StaticApplicationConfig::NoFeatureFlagsDefined;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 2,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint2EnabledAttributes),
        .enabledCommands = Span<const CommandId>(),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId) {
  switch (attributeId) {
    case Attributes::AcceptedCommandList::Id:
    case Attributes::AttributeList::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::EventList::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::LightSensorType::Id:
    case Attributes::MaxMeasuredValue::Id:
    case Attributes::MeasuredValue::Id:
    case Attributes::MinMeasuredValue::Id:
    case Attributes::Tolerance::Id:
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
} // namespace IlluminanceMeasurement
} // namespace Clusters
} // namespace app
} // namespace chip

