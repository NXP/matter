// DO NOT EDIT - Generated file
//
// Application configuration for SmokeCoAlarm based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/bridge-app/nxp/linux-M2ZigbeeRcp-bridge/M2ZigbeeRcp-bridge-zap/M2ZigbeeRcp-bridge-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/SmokeCoAlarm/AttributeIds.h>
#include <clusters/SmokeCoAlarm/CommandIds.h>
#include <clusters/SmokeCoAlarm/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace SmokeCoAlarm {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint2EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::BatteryAlert::Id,
    Attributes::ClusterRevision::Id,
    Attributes::ContaminationState::Id,
    Attributes::COState::Id,
    Attributes::DeviceMuted::Id,
    Attributes::EndOfServiceAlert::Id,
    Attributes::EventList::Id,
    Attributes::ExpiryDate::Id,
    Attributes::ExpressedState::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::HardwareFaultAlert::Id,
    Attributes::InterconnectCOAlarm::Id,
    Attributes::InterconnectSmokeAlarm::Id,
    Attributes::SmokeSensitivityLevel::Id,
    Attributes::SmokeState::Id,
    Attributes::TestInProgress::Id,
};
} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 2,
        .featureMap = BitFlags<FeatureBitmapType> {
            FeatureBitmapType::kSmokeAlarm// feature bit 0x1
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint2EnabledAttributes),
        .enabledCommands = Span<const CommandId>(),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId) {
  switch (attributeId) {
    case Attributes::COState::Id:
    case Attributes::AcceptedCommandList::Id:
    case Attributes::AttributeList::Id:
    case Attributes::BatteryAlert::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::ContaminationState::Id:
    case Attributes::DeviceMuted::Id:
    case Attributes::EndOfServiceAlert::Id:
    case Attributes::EventList::Id:
    case Attributes::ExpiryDate::Id:
    case Attributes::ExpressedState::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::HardwareFaultAlert::Id:
    case Attributes::InterconnectCOAlarm::Id:
    case Attributes::InterconnectSmokeAlarm::Id:
    case Attributes::SmokeSensitivityLevel::Id:
    case Attributes::SmokeState::Id:
    case Attributes::TestInProgress::Id:
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
} // namespace SmokeCoAlarm
} // namespace Clusters
} // namespace app
} // namespace chip

