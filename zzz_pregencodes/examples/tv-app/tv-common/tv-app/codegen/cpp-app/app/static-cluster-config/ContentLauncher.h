// DO NOT EDIT - Generated file
//
// Application configuration for ContentLauncher based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/tv-app/tv-common/tv-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/ContentLauncher/AttributeIds.h>
#include <clusters/ContentLauncher/CommandIds.h>
#include <clusters/ContentLauncher/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace ContentLauncher {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AcceptHeader::Id, Attributes::ClusterRevision::Id, Attributes::FeatureMap::Id,
    Attributes::Movable::Id,      Attributes::Presets::Id,         Attributes::SupportedStreamingProtocols::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::ContentReplicationRequest::Id,
    Commands::LaunchContent::Id,
    Commands::LaunchURL::Id,
    Commands::PlayPreset::Id,
};

inline constexpr AttributeId kEndpoint3EnabledAttributes[] = {
    Attributes::AcceptHeader::Id, Attributes::ClusterRevision::Id, Attributes::FeatureMap::Id,
    Attributes::Movable::Id,      Attributes::Presets::Id,         Attributes::SupportedStreamingProtocols::Id,
};

inline constexpr CommandId kEndpoint3EnabledCommands[] = {
    Commands::ContentReplicationRequest::Id,
    Commands::LaunchContent::Id,
    Commands::LaunchURL::Id,
    Commands::PlayPreset::Id,
};

} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 2> kFixedClusterConfig = { {
    {
        .endpointNumber = 1,
        .featureMap =
            BitFlags<FeatureBitmapType>{
                FeatureBitmapType::kContentSearch,      // feature bit 0x1
                FeatureBitmapType::kURLPlayback,        // feature bit 0x2
                FeatureBitmapType::kAdvancedSeek,       // feature bit 0x4
                FeatureBitmapType::kTextTracks,         // feature bit 0x8
                FeatureBitmapType::kAudioTracks,        // feature bit 0x10
                FeatureBitmapType::kContentReplication, // feature bit 0x20
                FeatureBitmapType::kContentQueueing,    // feature bit 0x40
                FeatureBitmapType::kPresets             // feature bit 0x80
            },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint1EnabledAttributes),
        .enabledCommands   = Span<const CommandId>(detail::kEndpoint1EnabledCommands),
    },
    {
        .endpointNumber = 3,
        .featureMap =
            BitFlags<FeatureBitmapType>{
                FeatureBitmapType::kContentSearch,      // feature bit 0x1
                FeatureBitmapType::kURLPlayback,        // feature bit 0x2
                FeatureBitmapType::kAdvancedSeek,       // feature bit 0x4
                FeatureBitmapType::kTextTracks,         // feature bit 0x8
                FeatureBitmapType::kAudioTracks,        // feature bit 0x10
                FeatureBitmapType::kContentReplication, // feature bit 0x20
                FeatureBitmapType::kContentQueueing,    // feature bit 0x40
                FeatureBitmapType::kPresets             // feature bit 0x80
            },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint3EnabledAttributes),
        .enabledCommands   = Span<const CommandId>(detail::kEndpoint3EnabledCommands),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId)
{
    switch (attributeId)
    {
    case Attributes::AcceptHeader::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::Movable::Id:
    case Attributes::Presets::Id:
    case Attributes::SupportedStreamingProtocols::Id:
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
    case Commands::ContentReplicationRequest::Id:
    case Commands::LaunchContent::Id:
    case Commands::LaunchURL::Id:
    case Commands::PlayPreset::Id:
        return true;
    default:
        return false;
    }
}

} // namespace StaticApplicationConfig
} // namespace ContentLauncher
} // namespace Clusters
} // namespace app
} // namespace chip
