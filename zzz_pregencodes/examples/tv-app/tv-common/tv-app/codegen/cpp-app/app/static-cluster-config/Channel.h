// DO NOT EDIT - Generated file
//
// Application configuration for Channel based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/tv-app/tv-common/tv-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/Channel/AttributeIds.h>
#include <clusters/Channel/CommandIds.h>
#include <clusters/Channel/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace Channel {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::ChannelList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::CurrentChannel::Id,
    Attributes::FeatureMap::Id,
    Attributes::Lineup::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::CancelRecordProgram::Id,
    Commands::ChangeChannel::Id,
    Commands::ChangeChannelByNumber::Id,
    Commands::ChangeChannelResponse::Id,
    Commands::GetProgramGuide::Id,
    Commands::ProgramGuideResponse::Id,
    Commands::RecordProgram::Id,
    Commands::SkipChannel::Id,
};

inline constexpr AttributeId kEndpoint3EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ChannelList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::CurrentChannel::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::Lineup::Id,
};

inline constexpr CommandId kEndpoint3EnabledCommands[] = {
    Commands::CancelRecordProgram::Id,
    Commands::ChangeChannel::Id,
    Commands::ChangeChannelByNumber::Id,
    Commands::ChangeChannelResponse::Id,
    Commands::GetProgramGuide::Id,
    Commands::ProgramGuideResponse::Id,
    Commands::RecordProgram::Id,
    Commands::SkipChannel::Id,
};

} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 2> kFixedClusterConfig = { {
    {
        .endpointNumber = 1,
        .featureMap = BitFlags<FeatureBitmapType> {
            FeatureBitmapType::kChannelList, // feature bit 0x1
            FeatureBitmapType::kLineupInfo// feature bit 0x2
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint1EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint1EnabledCommands),
    },
    {
        .endpointNumber = 3,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint3EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint3EnabledCommands),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId) {
  switch (attributeId) {
    case Attributes::AcceptedCommandList::Id:
    case Attributes::AttributeList::Id:
    case Attributes::ChannelList::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::CurrentChannel::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::Lineup::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::CancelRecordProgram::Id:
    case Commands::ChangeChannel::Id:
    case Commands::ChangeChannelByNumber::Id:
    case Commands::ChangeChannelResponse::Id:
    case Commands::GetProgramGuide::Id:
    case Commands::ProgramGuideResponse::Id:
    case Commands::RecordProgram::Id:
    case Commands::SkipChannel::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace Channel
} // namespace Clusters
} // namespace app
} // namespace chip

