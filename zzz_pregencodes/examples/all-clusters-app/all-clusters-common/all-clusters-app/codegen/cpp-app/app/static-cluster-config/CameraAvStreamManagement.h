// DO NOT EDIT - Generated file
//
// Application configuration for CameraAvStreamManagement based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/all-clusters-app/all-clusters-common/all-clusters-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/CameraAvStreamManagement/AttributeIds.h>
#include <clusters/CameraAvStreamManagement/CommandIds.h>
#include <clusters/CameraAvStreamManagement/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace CameraAvStreamManagement {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AllocatedAudioStreams::Id,
    Attributes::AllocatedSnapshotStreams::Id,
    Attributes::AllocatedVideoStreams::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::CurrentFrameRate::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::HardPrivacyModeOn::Id,
    Attributes::HDRModeEnabled::Id,
    Attributes::ImageFlipHorizontal::Id,
    Attributes::ImageFlipVertical::Id,
    Attributes::ImageRotation::Id,
    Attributes::LocalSnapshotRecordingEnabled::Id,
    Attributes::LocalVideoRecordingEnabled::Id,
    Attributes::MaxConcurrentEncoders::Id,
    Attributes::MaxContentBufferSize::Id,
    Attributes::MaxEncodedPixelRate::Id,
    Attributes::MaxNetworkBandwidth::Id,
    Attributes::MicrophoneAGCEnabled::Id,
    Attributes::MicrophoneCapabilities::Id,
    Attributes::MicrophoneMaxLevel::Id,
    Attributes::MicrophoneMinLevel::Id,
    Attributes::MicrophoneMuted::Id,
    Attributes::MicrophoneVolumeLevel::Id,
    Attributes::MinViewport::Id,
    Attributes::NightVision::Id,
    Attributes::NightVisionIllum::Id,
    Attributes::NightVisionUsesInfrared::Id,
    Attributes::RateDistortionTradeOffPoints::Id,
    Attributes::SnapshotCapabilities::Id,
    Attributes::SoftLivestreamPrivacyModeEnabled::Id,
    Attributes::SoftRecordingPrivacyModeEnabled::Id,
    Attributes::SpeakerCapabilities::Id,
    Attributes::SpeakerMaxLevel::Id,
    Attributes::SpeakerMinLevel::Id,
    Attributes::SpeakerMuted::Id,
    Attributes::SpeakerVolumeLevel::Id,
    Attributes::StatusLightBrightness::Id,
    Attributes::StatusLightEnabled::Id,
    Attributes::StreamUsagePriorities::Id,
    Attributes::SupportedStreamUsages::Id,
    Attributes::TwoWayTalkSupport::Id,
    Attributes::VideoSensorParams::Id,
    Attributes::Viewport::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::CaptureSnapshot::Id,
    Commands::CaptureSnapshotResponse::Id,
    Commands::SetStreamPriorities::Id,
    Commands::SnapshotStreamAllocate::Id,
    Commands::SnapshotStreamAllocateResponse::Id,
    Commands::SnapshotStreamDeallocate::Id,
};

} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 1,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint1EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint1EnabledCommands),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId) {
  switch (attributeId) {
    case Attributes::HDRModeEnabled::Id:
    case Attributes::AcceptedCommandList::Id:
    case Attributes::AllocatedAudioStreams::Id:
    case Attributes::AllocatedSnapshotStreams::Id:
    case Attributes::AllocatedVideoStreams::Id:
    case Attributes::AttributeList::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::CurrentFrameRate::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::HardPrivacyModeOn::Id:
    case Attributes::ImageFlipHorizontal::Id:
    case Attributes::ImageFlipVertical::Id:
    case Attributes::ImageRotation::Id:
    case Attributes::LocalSnapshotRecordingEnabled::Id:
    case Attributes::LocalVideoRecordingEnabled::Id:
    case Attributes::MaxConcurrentEncoders::Id:
    case Attributes::MaxContentBufferSize::Id:
    case Attributes::MaxEncodedPixelRate::Id:
    case Attributes::MaxNetworkBandwidth::Id:
    case Attributes::MicrophoneAGCEnabled::Id:
    case Attributes::MicrophoneCapabilities::Id:
    case Attributes::MicrophoneMaxLevel::Id:
    case Attributes::MicrophoneMinLevel::Id:
    case Attributes::MicrophoneMuted::Id:
    case Attributes::MicrophoneVolumeLevel::Id:
    case Attributes::MinViewport::Id:
    case Attributes::NightVision::Id:
    case Attributes::NightVisionIllum::Id:
    case Attributes::NightVisionUsesInfrared::Id:
    case Attributes::RateDistortionTradeOffPoints::Id:
    case Attributes::SnapshotCapabilities::Id:
    case Attributes::SoftLivestreamPrivacyModeEnabled::Id:
    case Attributes::SoftRecordingPrivacyModeEnabled::Id:
    case Attributes::SpeakerCapabilities::Id:
    case Attributes::SpeakerMaxLevel::Id:
    case Attributes::SpeakerMinLevel::Id:
    case Attributes::SpeakerMuted::Id:
    case Attributes::SpeakerVolumeLevel::Id:
    case Attributes::StatusLightBrightness::Id:
    case Attributes::StatusLightEnabled::Id:
    case Attributes::StreamUsagePriorities::Id:
    case Attributes::SupportedStreamUsages::Id:
    case Attributes::TwoWayTalkSupport::Id:
    case Attributes::VideoSensorParams::Id:
    case Attributes::Viewport::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::CaptureSnapshot::Id:
    case Commands::CaptureSnapshotResponse::Id:
    case Commands::SetStreamPriorities::Id:
    case Commands::SnapshotStreamAllocate::Id:
    case Commands::SnapshotStreamAllocateResponse::Id:
    case Commands::SnapshotStreamDeallocate::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace CameraAvStreamManagement
} // namespace Clusters
} // namespace app
} // namespace chip

