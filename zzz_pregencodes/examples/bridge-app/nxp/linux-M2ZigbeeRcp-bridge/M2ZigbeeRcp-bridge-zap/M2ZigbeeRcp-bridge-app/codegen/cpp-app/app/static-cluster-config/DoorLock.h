// DO NOT EDIT - Generated file
//
// Application configuration for DoorLock based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/bridge-app/nxp/linux-M2ZigbeeRcp-bridge/M2ZigbeeRcp-bridge-zap/M2ZigbeeRcp-bridge-app.matter
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
inline constexpr AttributeId kEndpoint2EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::ActuatorEnabled::Id,
    Attributes::AttributeList::Id,
    Attributes::AutoRelockTime::Id,
    Attributes::ClusterRevision::Id,
    Attributes::CredentialRulesSupport::Id,
    Attributes::DefaultConfigurationRegister::Id,
    Attributes::DoorClosedEvents::Id,
    Attributes::DoorOpenEvents::Id,
    Attributes::DoorState::Id,
    Attributes::EnableInsideStatusLED::Id,
    Attributes::EnableLocalProgramming::Id,
    Attributes::EnableOneTouchLocking::Id,
    Attributes::EnablePrivacyModeButton::Id,
    Attributes::EventList::Id,
    Attributes::ExpiringUserTimeout::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::Language::Id,
    Attributes::LEDSettings::Id,
    Attributes::LocalProgrammingFeatures::Id,
    Attributes::LockState::Id,
    Attributes::LockType::Id,
    Attributes::MaxPINCodeLength::Id,
    Attributes::MaxRFIDCodeLength::Id,
    Attributes::MinPINCodeLength::Id,
    Attributes::MinRFIDCodeLength::Id,
    Attributes::NumberOfCredentialsSupportedPerUser::Id,
    Attributes::NumberOfHolidaySchedulesSupported::Id,
    Attributes::NumberOfPINUsersSupported::Id,
    Attributes::NumberOfRFIDUsersSupported::Id,
    Attributes::NumberOfTotalUsersSupported::Id,
    Attributes::NumberOfWeekDaySchedulesSupportedPerUser::Id,
    Attributes::NumberOfYearDaySchedulesSupportedPerUser::Id,
    Attributes::OpenPeriod::Id,
    Attributes::OperatingMode::Id,
    Attributes::RequirePINforRemoteOperation::Id,
    Attributes::SendPINOverTheAir::Id,
    Attributes::SoundVolume::Id,
    Attributes::SupportedOperatingModes::Id,
    Attributes::UserCodeTemporaryDisableTime::Id,
    Attributes::WrongCodeEntryLimit::Id,
};

inline constexpr CommandId kEndpoint2EnabledCommands[] = {
    Commands::ClearWeekDaySchedule::Id,
    Commands::ClearYearDaySchedule::Id,
    Commands::GetWeekDaySchedule::Id,
    Commands::GetWeekDayScheduleResponse::Id,
    Commands::GetYearDaySchedule::Id,
    Commands::GetYearDayScheduleResponse::Id,
    Commands::LockDoor::Id,
    Commands::SetHolidaySchedule::Id,
    Commands::SetWeekDaySchedule::Id,
    Commands::SetYearDaySchedule::Id,
    Commands::UnlockDoor::Id,
    Commands::UnlockWithTimeout::Id,
};

} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 2,
        .featureMap = BitFlags<FeatureBitmapType> {
            FeatureBitmapType::kPINCredential// feature bit 0x1
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint2EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint2EnabledCommands),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId) {
  switch (attributeId) {
    case Attributes::LEDSettings::Id:
    case Attributes::AcceptedCommandList::Id:
    case Attributes::ActuatorEnabled::Id:
    case Attributes::AttributeList::Id:
    case Attributes::AutoRelockTime::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::CredentialRulesSupport::Id:
    case Attributes::DefaultConfigurationRegister::Id:
    case Attributes::DoorClosedEvents::Id:
    case Attributes::DoorOpenEvents::Id:
    case Attributes::DoorState::Id:
    case Attributes::EnableInsideStatusLED::Id:
    case Attributes::EnableLocalProgramming::Id:
    case Attributes::EnableOneTouchLocking::Id:
    case Attributes::EnablePrivacyModeButton::Id:
    case Attributes::EventList::Id:
    case Attributes::ExpiringUserTimeout::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::Language::Id:
    case Attributes::LocalProgrammingFeatures::Id:
    case Attributes::LockState::Id:
    case Attributes::LockType::Id:
    case Attributes::MaxPINCodeLength::Id:
    case Attributes::MaxRFIDCodeLength::Id:
    case Attributes::MinPINCodeLength::Id:
    case Attributes::MinRFIDCodeLength::Id:
    case Attributes::NumberOfCredentialsSupportedPerUser::Id:
    case Attributes::NumberOfHolidaySchedulesSupported::Id:
    case Attributes::NumberOfPINUsersSupported::Id:
    case Attributes::NumberOfRFIDUsersSupported::Id:
    case Attributes::NumberOfTotalUsersSupported::Id:
    case Attributes::NumberOfWeekDaySchedulesSupportedPerUser::Id:
    case Attributes::NumberOfYearDaySchedulesSupportedPerUser::Id:
    case Attributes::OpenPeriod::Id:
    case Attributes::OperatingMode::Id:
    case Attributes::RequirePINforRemoteOperation::Id:
    case Attributes::SendPINOverTheAir::Id:
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
    case Commands::ClearWeekDaySchedule::Id:
    case Commands::ClearYearDaySchedule::Id:
    case Commands::GetWeekDaySchedule::Id:
    case Commands::GetWeekDayScheduleResponse::Id:
    case Commands::GetYearDaySchedule::Id:
    case Commands::GetYearDayScheduleResponse::Id:
    case Commands::LockDoor::Id:
    case Commands::SetHolidaySchedule::Id:
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

