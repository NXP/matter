// DO NOT EDIT - Generated file
//
// Application configuration for WindowCovering based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/placeholder/linux/apps/app1/config.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/WindowCovering/AttributeIds.h>
#include <clusters/WindowCovering/CommandIds.h>
#include <clusters/WindowCovering/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace WindowCovering {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint0EnabledAttributes[] = {
    Attributes::ClusterRevision::Id,
    Attributes::ConfigStatus::Id,
    Attributes::CurrentPositionLift::Id,
    Attributes::CurrentPositionLiftPercent100ths::Id,
    Attributes::CurrentPositionLiftPercentage::Id,
    Attributes::CurrentPositionTilt::Id,
    Attributes::CurrentPositionTiltPercent100ths::Id,
    Attributes::CurrentPositionTiltPercentage::Id,
    Attributes::EndProductType::Id,
    Attributes::FeatureMap::Id,
    Attributes::InstalledClosedLimitLift::Id,
    Attributes::InstalledClosedLimitTilt::Id,
    Attributes::InstalledOpenLimitLift::Id,
    Attributes::InstalledOpenLimitTilt::Id,
    Attributes::Mode::Id,
    Attributes::OperationalStatus::Id,
    Attributes::SafetyStatus::Id,
    Attributes::TargetPositionLiftPercent100ths::Id,
    Attributes::TargetPositionTiltPercent100ths::Id,
    Attributes::Type::Id,
};

inline constexpr CommandId kEndpoint0EnabledCommands[] = {
    Commands::DownOrClose::Id,
    Commands::GoToLiftPercentage::Id,
    Commands::GoToLiftValue::Id,
    Commands::GoToTiltPercentage::Id,
    Commands::GoToTiltValue::Id,
    Commands::StopMotion::Id,
    Commands::UpOrOpen::Id,
};

} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 0,
        .featureMap = BitFlags<FeatureBitmapType> {
            FeatureBitmapType::kLift, // feature bit 0x1
            FeatureBitmapType::kTilt, // feature bit 0x2
            FeatureBitmapType::kPositionAwareLift, // feature bit 0x4
            FeatureBitmapType::kPositionAwareTilt// feature bit 0x10
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint0EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint0EnabledCommands),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId) {
  switch (attributeId) {
    case Attributes::ClusterRevision::Id:
    case Attributes::ConfigStatus::Id:
    case Attributes::CurrentPositionLift::Id:
    case Attributes::CurrentPositionLiftPercent100ths::Id:
    case Attributes::CurrentPositionLiftPercentage::Id:
    case Attributes::CurrentPositionTilt::Id:
    case Attributes::CurrentPositionTiltPercent100ths::Id:
    case Attributes::CurrentPositionTiltPercentage::Id:
    case Attributes::EndProductType::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::InstalledClosedLimitLift::Id:
    case Attributes::InstalledClosedLimitTilt::Id:
    case Attributes::InstalledOpenLimitLift::Id:
    case Attributes::InstalledOpenLimitTilt::Id:
    case Attributes::Mode::Id:
    case Attributes::OperationalStatus::Id:
    case Attributes::SafetyStatus::Id:
    case Attributes::TargetPositionLiftPercent100ths::Id:
    case Attributes::TargetPositionTiltPercent100ths::Id:
    case Attributes::Type::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::DownOrClose::Id:
    case Commands::GoToLiftPercentage::Id:
    case Commands::GoToLiftValue::Id:
    case Commands::GoToTiltPercentage::Id:
    case Commands::GoToTiltValue::Id:
    case Commands::StopMotion::Id:
    case Commands::UpOrOpen::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace WindowCovering
} // namespace Clusters
} // namespace app
} // namespace chip

