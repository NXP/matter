// DO NOT EDIT - Generated file
//
// Application configuration for TimeSynchronization based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/thermostat/thermostat-common/thermostat.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/TimeSynchronization/AttributeIds.h>
#include <clusters/TimeSynchronization/CommandIds.h>
#include <clusters/TimeSynchronization/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace TimeSynchronization {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint0EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::Granularity::Id,
    Attributes::UTCTime::Id,
};

inline constexpr CommandId kEndpoint0EnabledCommands[] = {
    Commands::SetUTCTime::Id,
};

} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber    = 0,
        .featureMap        = BitFlags<FeatureBitmapType>{},
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint0EnabledAttributes),
        .enabledCommands   = Span<const CommandId>(detail::kEndpoint0EnabledCommands),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId)
{
    switch (attributeId)
    {
    case Attributes::UTCTime::Id:
    case Attributes::AcceptedCommandList::Id:
    case Attributes::AttributeList::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::Granularity::Id:
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
    case Commands::SetUTCTime::Id:
        return true;
    default:
        return false;
    }
}

} // namespace StaticApplicationConfig
} // namespace TimeSynchronization
} // namespace Clusters
} // namespace app
} // namespace chip
