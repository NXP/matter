// DO NOT EDIT - Generated file
//
// Application configuration for BridgedDeviceBasicInformation based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/bridge-app/nxp/linux-M2ZigbeeRcp-bridge/M2ZigbeeRcp-bridge-zap/M2ZigbeeRcp-bridge-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/BridgedDeviceBasicInformation/AttributeIds.h>
#include <clusters/BridgedDeviceBasicInformation/CommandIds.h>
#include <clusters/BridgedDeviceBasicInformation/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace BridgedDeviceBasicInformation {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint2EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::EventList::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::HardwareVersion::Id,
    Attributes::HardwareVersionString::Id,
    Attributes::ManufacturingDate::Id,
    Attributes::NodeLabel::Id,
    Attributes::PartNumber::Id,
    Attributes::ProductAppearance::Id,
    Attributes::ProductLabel::Id,
    Attributes::ProductName::Id,
    Attributes::ProductURL::Id,
    Attributes::Reachable::Id,
    Attributes::SerialNumber::Id,
    Attributes::SoftwareVersion::Id,
    Attributes::SoftwareVersionString::Id,
    Attributes::UniqueID::Id,
    Attributes::VendorID::Id,
    Attributes::VendorName::Id,
};
} // namespace detail

using FeatureBitmapType = Feature;

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
    case Attributes::HardwareVersion::Id:
    case Attributes::HardwareVersionString::Id:
    case Attributes::ManufacturingDate::Id:
    case Attributes::NodeLabel::Id:
    case Attributes::PartNumber::Id:
    case Attributes::ProductAppearance::Id:
    case Attributes::ProductLabel::Id:
    case Attributes::ProductName::Id:
    case Attributes::ProductURL::Id:
    case Attributes::Reachable::Id:
    case Attributes::SerialNumber::Id:
    case Attributes::SoftwareVersion::Id:
    case Attributes::SoftwareVersionString::Id:
    case Attributes::UniqueID::Id:
    case Attributes::VendorID::Id:
    case Attributes::VendorName::Id:
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
} // namespace BridgedDeviceBasicInformation
} // namespace Clusters
} // namespace app
} // namespace chip

