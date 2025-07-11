// DO NOT EDIT - Generated file
//
// Application configuration for MediaPlayback based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/placeholder/linux/apps/app2/config.matter
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
inline constexpr AttributeId kEndpoint0EnabledAttributes[] = {
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

inline constexpr CommandId kEndpoint0EnabledCommands[] = {
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

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 0,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint0EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint0EnabledCommands),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId) {
  switch (attributeId) {
    case Attributes::ClusterRevision::Id:
    case Attributes::CurrentState::Id:
    case Attributes::Duration::Id:
    case Attributes::FeatureMap::Id:
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

