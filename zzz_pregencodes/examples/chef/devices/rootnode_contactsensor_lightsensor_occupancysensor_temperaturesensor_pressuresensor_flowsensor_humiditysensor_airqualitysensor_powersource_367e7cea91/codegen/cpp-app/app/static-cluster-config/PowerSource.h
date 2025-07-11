// DO NOT EDIT - Generated file
//
// Application configuration for PowerSource based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/chef/devices/rootnode_contactsensor_lightsensor_occupancysensor_temperaturesensor_pressuresensor_flowsensor_humiditysensor_airqualitysensor_powersource_367e7cea91.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/PowerSource/AttributeIds.h>
#include <clusters/PowerSource/CommandIds.h>
#include <clusters/PowerSource/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace PowerSource {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint9EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::BatApprovedChemistry::Id,
    Attributes::BatChargeLevel::Id,
    Attributes::BatCommonDesignation::Id,
    Attributes::BatPercentRemaining::Id,
    Attributes::BatPresent::Id,
    Attributes::BatQuantity::Id,
    Attributes::BatReplaceability::Id,
    Attributes::BatReplacementDescription::Id,
    Attributes::BatReplacementNeeded::Id,
    Attributes::BatTimeRemaining::Id,
    Attributes::BatVoltage::Id,
    Attributes::ClusterRevision::Id,
    Attributes::Description::Id,
    Attributes::EndpointList::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::Order::Id,
    Attributes::Status::Id,
};
} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 9,
        .featureMap = BitFlags<FeatureBitmapType> {
            FeatureBitmapType::kBattery, // feature bit 0x2
            FeatureBitmapType::kReplaceable// feature bit 0x8
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint9EnabledAttributes),
        .enabledCommands = Span<const CommandId>(),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId) {
  switch (attributeId) {
    case Attributes::AcceptedCommandList::Id:
    case Attributes::AttributeList::Id:
    case Attributes::BatApprovedChemistry::Id:
    case Attributes::BatChargeLevel::Id:
    case Attributes::BatCommonDesignation::Id:
    case Attributes::BatPercentRemaining::Id:
    case Attributes::BatPresent::Id:
    case Attributes::BatQuantity::Id:
    case Attributes::BatReplaceability::Id:
    case Attributes::BatReplacementDescription::Id:
    case Attributes::BatReplacementNeeded::Id:
    case Attributes::BatTimeRemaining::Id:
    case Attributes::BatVoltage::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::Description::Id:
    case Attributes::EndpointList::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::Order::Id:
    case Attributes::Status::Id:
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
} // namespace PowerSource
} // namespace Clusters
} // namespace app
} // namespace chip

