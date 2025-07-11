// DO NOT EDIT - Generated file
//
// Application configuration for TimeFormatLocalization based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/nxp-media-app/nxp-media-common/nxp-media-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/TimeFormatLocalization/AttributeIds.h>
#include <clusters/TimeFormatLocalization/CommandIds.h>
#include <clusters/TimeFormatLocalization/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace TimeFormatLocalization {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint0EnabledAttributes[] = {
    Attributes::ActiveCalendarType::Id,
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::HourFormat::Id,
    Attributes::SupportedCalendarTypes::Id,
};
} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 0,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint0EnabledAttributes),
        .enabledCommands = Span<const CommandId>(),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId) {
  switch (attributeId) {
    case Attributes::ActiveCalendarType::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::HourFormat::Id:
    case Attributes::SupportedCalendarTypes::Id:
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
} // namespace TimeFormatLocalization
} // namespace Clusters
} // namespace app
} // namespace chip

