// DO NOT EDIT - Generated file
//
// Application configuration for ContentControl based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/nxp-media-app/nxp-media-common/nxp-media-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/ContentControl/AttributeIds.h>
#include <clusters/ContentControl/CommandIds.h>
#include <clusters/ContentControl/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace ContentControl {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::BlockUnrated::Id,
    Attributes::ClusterRevision::Id,
    Attributes::Enabled::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::OnDemandRatings::Id,
    Attributes::OnDemandRatingThreshold::Id,
    Attributes::RemainingScreenTime::Id,
    Attributes::ScheduledContentRatings::Id,
    Attributes::ScheduledContentRatingThreshold::Id,
    Attributes::ScreenDailyTime::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::AddBonusTime::Id,
    Commands::BlockUnratedContent::Id,
    Commands::Disable::Id,
    Commands::Enable::Id,
    Commands::ResetPIN::Id,
    Commands::ResetPINResponse::Id,
    Commands::SetOnDemandRatingThreshold::Id,
    Commands::SetScheduledContentRatingThreshold::Id,
    Commands::SetScreenDailyTime::Id,
    Commands::UnblockUnratedContent::Id,
    Commands::UpdatePIN::Id,
};

inline constexpr AttributeId kEndpoint3EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::BlockUnrated::Id,
    Attributes::ClusterRevision::Id,
    Attributes::Enabled::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::OnDemandRatings::Id,
    Attributes::OnDemandRatingThreshold::Id,
    Attributes::RemainingScreenTime::Id,
    Attributes::ScheduledContentRatings::Id,
    Attributes::ScheduledContentRatingThreshold::Id,
    Attributes::ScreenDailyTime::Id,
};

inline constexpr CommandId kEndpoint3EnabledCommands[] = {
    Commands::AddBonusTime::Id,
    Commands::BlockUnratedContent::Id,
    Commands::Disable::Id,
    Commands::Enable::Id,
    Commands::ResetPIN::Id,
    Commands::ResetPINResponse::Id,
    Commands::SetOnDemandRatingThreshold::Id,
    Commands::SetScheduledContentRatingThreshold::Id,
    Commands::SetScreenDailyTime::Id,
    Commands::UnblockUnratedContent::Id,
    Commands::UpdatePIN::Id,
};

} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 2> kFixedClusterConfig = { {
    {
        .endpointNumber = 1,
        .featureMap = BitFlags<FeatureBitmapType> {
            FeatureBitmapType::kBlockUnrated, // feature bit 0x4
            FeatureBitmapType::kOnDemandContentRating, // feature bit 0x8
            FeatureBitmapType::kScheduledContentRating// feature bit 0x10
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint1EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint1EnabledCommands),
    },
    {
        .endpointNumber = 3,
        .featureMap = BitFlags<FeatureBitmapType> {
            FeatureBitmapType::kBlockUnrated, // feature bit 0x4
            FeatureBitmapType::kOnDemandContentRating, // feature bit 0x8
            FeatureBitmapType::kScheduledContentRating// feature bit 0x10
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
    case Attributes::BlockUnrated::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::Enabled::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::OnDemandRatingThreshold::Id:
    case Attributes::OnDemandRatings::Id:
    case Attributes::RemainingScreenTime::Id:
    case Attributes::ScheduledContentRatingThreshold::Id:
    case Attributes::ScheduledContentRatings::Id:
    case Attributes::ScreenDailyTime::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::AddBonusTime::Id:
    case Commands::BlockUnratedContent::Id:
    case Commands::Disable::Id:
    case Commands::Enable::Id:
    case Commands::ResetPIN::Id:
    case Commands::ResetPINResponse::Id:
    case Commands::SetOnDemandRatingThreshold::Id:
    case Commands::SetScheduledContentRatingThreshold::Id:
    case Commands::SetScreenDailyTime::Id:
    case Commands::UnblockUnratedContent::Id:
    case Commands::UpdatePIN::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace ContentControl
} // namespace Clusters
} // namespace app
} // namespace chip

