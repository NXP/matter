// DO NOT EDIT - Generated file
//
// Application configuration for WiFiNetworkDiagnostics based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/nxp-water-heater-app/nxp-water-heater-common/nxp-water-heater-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/WiFiNetworkDiagnostics/AttributeIds.h>
#include <clusters/WiFiNetworkDiagnostics/CommandIds.h>
#include <clusters/WiFiNetworkDiagnostics/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace WiFiNetworkDiagnostics {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint0EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::Bssid::Id,
    Attributes::ChannelNumber::Id,
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::Rssi::Id,
    Attributes::SecurityType::Id,
    Attributes::WiFiVersion::Id,
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
    case Attributes::AcceptedCommandList::Id:
    case Attributes::AttributeList::Id:
    case Attributes::Bssid::Id:
    case Attributes::ChannelNumber::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::Rssi::Id:
    case Attributes::SecurityType::Id:
    case Attributes::WiFiVersion::Id:
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
} // namespace WiFiNetworkDiagnostics
} // namespace Clusters
} // namespace app
} // namespace chip

