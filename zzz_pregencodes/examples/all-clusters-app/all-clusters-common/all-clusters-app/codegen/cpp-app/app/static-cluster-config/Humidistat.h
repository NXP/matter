// DO NOT EDIT - Generated file
//
// Application configuration for Humidistat based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/all-clusters-app/all-clusters-common/all-clusters-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/Humidistat/AttributeIds.h>
#include <clusters/Humidistat/CommandIds.h>
#include <clusters/Humidistat/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace Humidistat {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::Continuous::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::MaxSetpoint::Id,
    Attributes::MinSetpoint::Id,
    Attributes::MistType::Id,
    Attributes::Mode::Id,
    Attributes::Optimal::Id,
    Attributes::Sleep::Id,
    Attributes::Step::Id,
    Attributes::SystemState::Id,
    Attributes::TargetSetpoint::Id,
    Attributes::UserSetpoint::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::SetSettings::Id,
};

} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 1,
        .featureMap =
            BitFlags<FeatureBitmapType>{
                FeatureBitmapType::kHumidifier,   // feature bit 0x1
                FeatureBitmapType::kDehumidifier, // feature bit 0x2
                FeatureBitmapType::kContinuous,   // feature bit 0x4
                FeatureBitmapType::kSensor,       // feature bit 0x8
                FeatureBitmapType::kAuto,         // feature bit 0x10
                FeatureBitmapType::kFanOnly,      // feature bit 0x20
                FeatureBitmapType::kOptimal,      // feature bit 0x40
                FeatureBitmapType::kWarmMist,     // feature bit 0x80
                FeatureBitmapType::kColdMist      // feature bit 0x100
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
    case Attributes::ClusterRevision::Id:
    case Attributes::Continuous::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::MaxSetpoint::Id:
    case Attributes::MinSetpoint::Id:
    case Attributes::MistType::Id:
    case Attributes::Mode::Id:
    case Attributes::Optimal::Id:
    case Attributes::Sleep::Id:
    case Attributes::Step::Id:
    case Attributes::SystemState::Id:
    case Attributes::TargetSetpoint::Id:
    case Attributes::UserSetpoint::Id:
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
    case Commands::SetSettings::Id:
        return true;
    default:
        return false;
    }
}

} // namespace StaticApplicationConfig
} // namespace Humidistat
} // namespace Clusters
} // namespace app
} // namespace chip
