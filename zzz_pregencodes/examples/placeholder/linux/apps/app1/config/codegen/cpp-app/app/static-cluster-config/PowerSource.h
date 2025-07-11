// DO NOT EDIT - Generated file
//
// Application configuration for PowerSource based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/placeholder/linux/apps/app1/config.matter
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
inline constexpr AttributeId kEndpoint0EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::ActiveBatChargeFaults::Id,
    Attributes::ActiveBatFaults::Id,
    Attributes::ActiveWiredFaults::Id,
    Attributes::AttributeList::Id,
    Attributes::BatANSIDesignation::Id,
    Attributes::BatApprovedChemistry::Id,
    Attributes::BatCapacity::Id,
    Attributes::BatChargeLevel::Id,
    Attributes::BatChargeState::Id,
    Attributes::BatChargingCurrent::Id,
    Attributes::BatCommonDesignation::Id,
    Attributes::BatFunctionalWhileCharging::Id,
    Attributes::BatIECDesignation::Id,
    Attributes::BatPercentRemaining::Id,
    Attributes::BatPresent::Id,
    Attributes::BatQuantity::Id,
    Attributes::BatReplaceability::Id,
    Attributes::BatReplacementDescription::Id,
    Attributes::BatReplacementNeeded::Id,
    Attributes::BatTimeRemaining::Id,
    Attributes::BatTimeToFullCharge::Id,
    Attributes::BatVoltage::Id,
    Attributes::ClusterRevision::Id,
    Attributes::Description::Id,
    Attributes::EndpointList::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::Order::Id,
    Attributes::Status::Id,
    Attributes::WiredAssessedCurrent::Id,
    Attributes::WiredAssessedInputFrequency::Id,
    Attributes::WiredAssessedInputVoltage::Id,
    Attributes::WiredCurrentType::Id,
    Attributes::WiredMaximumCurrent::Id,
    Attributes::WiredNominalVoltage::Id,
    Attributes::WiredPresent::Id,
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
    case Attributes::ActiveBatChargeFaults::Id:
    case Attributes::ActiveBatFaults::Id:
    case Attributes::ActiveWiredFaults::Id:
    case Attributes::AttributeList::Id:
    case Attributes::BatANSIDesignation::Id:
    case Attributes::BatApprovedChemistry::Id:
    case Attributes::BatCapacity::Id:
    case Attributes::BatChargeLevel::Id:
    case Attributes::BatChargeState::Id:
    case Attributes::BatChargingCurrent::Id:
    case Attributes::BatCommonDesignation::Id:
    case Attributes::BatFunctionalWhileCharging::Id:
    case Attributes::BatIECDesignation::Id:
    case Attributes::BatPercentRemaining::Id:
    case Attributes::BatPresent::Id:
    case Attributes::BatQuantity::Id:
    case Attributes::BatReplaceability::Id:
    case Attributes::BatReplacementDescription::Id:
    case Attributes::BatReplacementNeeded::Id:
    case Attributes::BatTimeRemaining::Id:
    case Attributes::BatTimeToFullCharge::Id:
    case Attributes::BatVoltage::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::Description::Id:
    case Attributes::EndpointList::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::Order::Id:
    case Attributes::Status::Id:
    case Attributes::WiredAssessedCurrent::Id:
    case Attributes::WiredAssessedInputFrequency::Id:
    case Attributes::WiredAssessedInputVoltage::Id:
    case Attributes::WiredCurrentType::Id:
    case Attributes::WiredMaximumCurrent::Id:
    case Attributes::WiredNominalVoltage::Id:
    case Attributes::WiredPresent::Id:
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

