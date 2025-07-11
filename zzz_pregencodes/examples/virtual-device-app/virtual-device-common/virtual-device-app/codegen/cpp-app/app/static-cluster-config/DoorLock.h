// DO NOT EDIT - Generated file
//
// Application configuration for DoorLock based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/virtual-device-app/virtual-device-common/virtual-device-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/DoorLock/AttributeIds.h>
#include <clusters/DoorLock/CommandIds.h>
#include <clusters/DoorLock/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace DoorLock {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::ActuatorEnabled::Id,
    Attributes::AutoRelockTime::Id,
    Attributes::ClusterRevision::Id,
    Attributes::CredentialRulesSupport::Id,
    Attributes::DoorState::Id,
    Attributes::EnableOneTouchLocking::Id,
    Attributes::EnablePrivacyModeButton::Id,
    Attributes::FeatureMap::Id,
    Attributes::Language::Id,
    Attributes::LockState::Id,
    Attributes::LockType::Id,
    Attributes::MaxPINCodeLength::Id,
    Attributes::MaxRFIDCodeLength::Id,
    Attributes::MinPINCodeLength::Id,
    Attributes::MinRFIDCodeLength::Id,
    Attributes::NumberOfPINUsersSupported::Id,
    Attributes::NumberOfRFIDUsersSupported::Id,
    Attributes::NumberOfTotalUsersSupported::Id,
    Attributes::NumberOfWeekDaySchedulesSupportedPerUser::Id,
    Attributes::NumberOfYearDaySchedulesSupportedPerUser::Id,
    Attributes::OperatingMode::Id,
    Attributes::RequirePINforRemoteOperation::Id,
    Attributes::SoundVolume::Id,
    Attributes::SupportedOperatingModes::Id,
    Attributes::UserCodeTemporaryDisableTime::Id,
    Attributes::WrongCodeEntryLimit::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::ClearCredential::Id,
    Commands::ClearUser::Id,
    Commands::ClearWeekDaySchedule::Id,
    Commands::ClearYearDaySchedule::Id,
    Commands::GetCredentialStatus::Id,
    Commands::GetCredentialStatusResponse::Id,
    Commands::GetUser::Id,
    Commands::GetUserResponse::Id,
    Commands::GetWeekDaySchedule::Id,
    Commands::GetWeekDayScheduleResponse::Id,
    Commands::GetYearDaySchedule::Id,
    Commands::GetYearDayScheduleResponse::Id,
    Commands::LockDoor::Id,
    Commands::SetCredential::Id,
    Commands::SetCredentialResponse::Id,
    Commands::SetUser::Id,
    Commands::SetWeekDaySchedule::Id,
    Commands::SetYearDaySchedule::Id,
    Commands::UnlockDoor::Id,
    Commands::UnlockWithTimeout::Id,
};

} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 1,
        .featureMap = BitFlags<FeatureBitmapType> {
            FeatureBitmapType::kPINCredential, // feature bit 0x1
            FeatureBitmapType::kRFIDCredential, // feature bit 0x2
            FeatureBitmapType::kWeekDayAccessSchedules, // feature bit 0x10
            FeatureBitmapType::kCredentialsOverTheAirAccess, // feature bit 0x80
            FeatureBitmapType::kUser// feature bit 0x100
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint1EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint1EnabledCommands),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId) {
  switch (attributeId) {
    case Attributes::ActuatorEnabled::Id:
    case Attributes::AutoRelockTime::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::CredentialRulesSupport::Id:
    case Attributes::DoorState::Id:
    case Attributes::EnableOneTouchLocking::Id:
    case Attributes::EnablePrivacyModeButton::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::Language::Id:
    case Attributes::LockState::Id:
    case Attributes::LockType::Id:
    case Attributes::MaxPINCodeLength::Id:
    case Attributes::MaxRFIDCodeLength::Id:
    case Attributes::MinPINCodeLength::Id:
    case Attributes::MinRFIDCodeLength::Id:
    case Attributes::NumberOfPINUsersSupported::Id:
    case Attributes::NumberOfRFIDUsersSupported::Id:
    case Attributes::NumberOfTotalUsersSupported::Id:
    case Attributes::NumberOfWeekDaySchedulesSupportedPerUser::Id:
    case Attributes::NumberOfYearDaySchedulesSupportedPerUser::Id:
    case Attributes::OperatingMode::Id:
    case Attributes::RequirePINforRemoteOperation::Id:
    case Attributes::SoundVolume::Id:
    case Attributes::SupportedOperatingModes::Id:
    case Attributes::UserCodeTemporaryDisableTime::Id:
    case Attributes::WrongCodeEntryLimit::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::ClearCredential::Id:
    case Commands::ClearUser::Id:
    case Commands::ClearWeekDaySchedule::Id:
    case Commands::ClearYearDaySchedule::Id:
    case Commands::GetCredentialStatus::Id:
    case Commands::GetCredentialStatusResponse::Id:
    case Commands::GetUser::Id:
    case Commands::GetUserResponse::Id:
    case Commands::GetWeekDaySchedule::Id:
    case Commands::GetWeekDayScheduleResponse::Id:
    case Commands::GetYearDaySchedule::Id:
    case Commands::GetYearDayScheduleResponse::Id:
    case Commands::LockDoor::Id:
    case Commands::SetCredential::Id:
    case Commands::SetCredentialResponse::Id:
    case Commands::SetUser::Id:
    case Commands::SetWeekDaySchedule::Id:
    case Commands::SetYearDaySchedule::Id:
    case Commands::UnlockDoor::Id:
    case Commands::UnlockWithTimeout::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace DoorLock
} // namespace Clusters
} // namespace app
} // namespace chip

