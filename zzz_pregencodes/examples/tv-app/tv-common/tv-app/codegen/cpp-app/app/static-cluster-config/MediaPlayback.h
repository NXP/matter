// DO NOT EDIT - Generated file
//
// Application configuration for MediaPlayback based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/tv-app/tv-common/tv-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/MediaPlayback/AttributeIds.h>
#include <clusters/MediaPlayback/CommandIds.h>
#include <clusters/MediaPlayback/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace MediaPlayback {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::ActiveAudioTrack::Id,
    Attributes::ActiveTextTrack::Id,
    Attributes::AttributeList::Id,
    Attributes::AvailableAudioTracks::Id,
    Attributes::AvailableTextTracks::Id,
    Attributes::ClusterRevision::Id,
    Attributes::CurrentState::Id,
    Attributes::Duration::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::PlaybackSpeed::Id,
    Attributes::SampledPosition::Id,
    Attributes::SeekRangeEnd::Id,
    Attributes::SeekRangeStart::Id,
    Attributes::StartTime::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::ActivateAudioTrack::Id,
    Commands::ActivateTextTrack::Id,
    Commands::DeactivateTextTrack::Id,
    Commands::FastForward::Id,
    Commands::Next::Id,
    Commands::Pause::Id,
    Commands::Play::Id,
    Commands::PlaybackResponse::Id,
    Commands::Previous::Id,
    Commands::Rewind::Id,
    Commands::Seek::Id,
    Commands::SkipBackward::Id,
    Commands::SkipForward::Id,
    Commands::StartOver::Id,
    Commands::Stop::Id,
};

inline constexpr AttributeId kEndpoint3EnabledAttributes[] = {
    Attributes::ActiveAudioTrack::Id,
    Attributes::ActiveTextTrack::Id,
    Attributes::AvailableAudioTracks::Id,
    Attributes::AvailableTextTracks::Id,
    Attributes::ClusterRevision::Id,
    Attributes::CurrentState::Id,
    Attributes::Duration::Id,
    Attributes::FeatureMap::Id,
    Attributes::PlaybackSpeed::Id,
    Attributes::SampledPosition::Id,
    Attributes::SeekRangeEnd::Id,
    Attributes::SeekRangeStart::Id,
    Attributes::StartTime::Id,
};

inline constexpr CommandId kEndpoint3EnabledCommands[] = {
    Commands::ActivateAudioTrack::Id,
    Commands::ActivateTextTrack::Id,
    Commands::DeactivateTextTrack::Id,
    Commands::FastForward::Id,
    Commands::Next::Id,
    Commands::Pause::Id,
    Commands::Play::Id,
    Commands::PlaybackResponse::Id,
    Commands::Previous::Id,
    Commands::Rewind::Id,
    Commands::Seek::Id,
    Commands::SkipBackward::Id,
    Commands::SkipForward::Id,
    Commands::StartOver::Id,
    Commands::Stop::Id,
};

} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 2> kFixedClusterConfig = { {
    {
        .endpointNumber = 1,
        .featureMap = BitFlags<FeatureBitmapType> {
            FeatureBitmapType::kAdvancedSeek, // feature bit 0x1
            FeatureBitmapType::kVariableSpeed// feature bit 0x2
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint1EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint1EnabledCommands),
    },
    {
        .endpointNumber = 3,
        .featureMap = BitFlags<FeatureBitmapType> {
            FeatureBitmapType::kAdvancedSeek, // feature bit 0x1
            FeatureBitmapType::kVariableSpeed// feature bit 0x2
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint3EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint3EnabledCommands),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId) {
  switch (attributeId) {
    case Attributes::AcceptedCommandList::Id:
    case Attributes::ActiveAudioTrack::Id:
    case Attributes::ActiveTextTrack::Id:
    case Attributes::AttributeList::Id:
    case Attributes::AvailableAudioTracks::Id:
    case Attributes::AvailableTextTracks::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::CurrentState::Id:
    case Attributes::Duration::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::PlaybackSpeed::Id:
    case Attributes::SampledPosition::Id:
    case Attributes::SeekRangeEnd::Id:
    case Attributes::SeekRangeStart::Id:
    case Attributes::StartTime::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::ActivateAudioTrack::Id:
    case Commands::ActivateTextTrack::Id:
    case Commands::DeactivateTextTrack::Id:
    case Commands::FastForward::Id:
    case Commands::Next::Id:
    case Commands::Pause::Id:
    case Commands::Play::Id:
    case Commands::PlaybackResponse::Id:
    case Commands::Previous::Id:
    case Commands::Rewind::Id:
    case Commands::Seek::Id:
    case Commands::SkipBackward::Id:
    case Commands::SkipForward::Id:
    case Commands::StartOver::Id:
    case Commands::Stop::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace MediaPlayback
} // namespace Clusters
} // namespace app
} // namespace chip

