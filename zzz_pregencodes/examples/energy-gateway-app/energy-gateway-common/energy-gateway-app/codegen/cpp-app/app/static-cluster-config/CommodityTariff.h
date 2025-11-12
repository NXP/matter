// DO NOT EDIT - Generated file
//
// Application configuration for CommodityTariff based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/energy-gateway-app/energy-gateway-common/energy-gateway-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/CommodityTariff/AttributeIds.h>
#include <clusters/CommodityTariff/CommandIds.h>
#include <clusters/CommodityTariff/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace CommodityTariff {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::CalendarPeriods::Id,
    Attributes::ClusterRevision::Id,
    Attributes::CurrentDay::Id,
    Attributes::CurrentDayEntry::Id,
    Attributes::CurrentDayEntryDate::Id,
    Attributes::CurrentTariffComponents::Id,
    Attributes::DayEntries::Id,
    Attributes::DayPatterns::Id,
    Attributes::DefaultRandomizationOffset::Id,
    Attributes::DefaultRandomizationType::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::IndividualDays::Id,
    Attributes::NextDay::Id,
    Attributes::NextDayEntry::Id,
    Attributes::NextDayEntryDate::Id,
    Attributes::NextTariffComponents::Id,
    Attributes::StartDate::Id,
    Attributes::TariffComponents::Id,
    Attributes::TariffInfo::Id,
    Attributes::TariffPeriods::Id,
    Attributes::TariffUnit::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::GetDayEntry::Id,
    Commands::GetDayEntryResponse::Id,
    Commands::GetTariffComponent::Id,
    Commands::GetTariffComponentResponse::Id,
};

} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 1,
        .featureMap =
            BitFlags<FeatureBitmapType>{
                FeatureBitmapType::kPricing,        // feature bit 0x1
                FeatureBitmapType::kFriendlyCredit, // feature bit 0x2
                FeatureBitmapType::kAuxiliaryLoad,  // feature bit 0x4
                FeatureBitmapType::kPeakPeriod,     // feature bit 0x8
                FeatureBitmapType::kPowerThreshold, // feature bit 0x10
                FeatureBitmapType::kRandomization   // feature bit 0x20
            },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint1EnabledAttributes),
        .enabledCommands   = Span<const CommandId>(detail::kEndpoint1EnabledCommands),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId)
{
    switch (attributeId)
    {
    case Attributes::AcceptedCommandList::Id:
    case Attributes::AttributeList::Id:
    case Attributes::CalendarPeriods::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::CurrentDay::Id:
    case Attributes::CurrentDayEntry::Id:
    case Attributes::CurrentDayEntryDate::Id:
    case Attributes::CurrentTariffComponents::Id:
    case Attributes::DayEntries::Id:
    case Attributes::DayPatterns::Id:
    case Attributes::DefaultRandomizationOffset::Id:
    case Attributes::DefaultRandomizationType::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::IndividualDays::Id:
    case Attributes::NextDay::Id:
    case Attributes::NextDayEntry::Id:
    case Attributes::NextDayEntryDate::Id:
    case Attributes::NextTariffComponents::Id:
    case Attributes::StartDate::Id:
    case Attributes::TariffComponents::Id:
    case Attributes::TariffInfo::Id:
    case Attributes::TariffPeriods::Id:
    case Attributes::TariffUnit::Id:
        return true;
    default:
        return false;
    }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId)
{
    switch (commandId)
    {
    case Commands::GetDayEntry::Id:
    case Commands::GetDayEntryResponse::Id:
    case Commands::GetTariffComponent::Id:
    case Commands::GetTariffComponentResponse::Id:
        return true;
    default:
        return false;
    }
}

} // namespace StaticApplicationConfig
} // namespace CommodityTariff
} // namespace Clusters
} // namespace app
} // namespace chip
