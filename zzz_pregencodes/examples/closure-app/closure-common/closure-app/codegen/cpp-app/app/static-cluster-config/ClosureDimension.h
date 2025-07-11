// DO NOT EDIT - Generated file
//
// Application configuration for ClosureDimension based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/closure-app/closure-common/closure-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/ClosureDimension/AttributeIds.h>
#include <clusters/ClosureDimension/CommandIds.h>
#include <clusters/ClosureDimension/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace ClosureDimension {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint2EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::CurrentState::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::LatchControlModes::Id,
    Attributes::LimitRange::Id,
    Attributes::ModulationType::Id,
    Attributes::Overflow::Id,
    Attributes::Resolution::Id,
    Attributes::RotationAxis::Id,
    Attributes::StepValue::Id,
    Attributes::TargetState::Id,
    Attributes::TranslationDirection::Id,
    Attributes::Unit::Id,
    Attributes::UnitRange::Id,
};

inline constexpr CommandId kEndpoint2EnabledCommands[] = {
    Commands::SetTarget::Id,
    Commands::Step::Id,
};

inline constexpr AttributeId kEndpoint3EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::CurrentState::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::LatchControlModes::Id,
    Attributes::LimitRange::Id,
    Attributes::ModulationType::Id,
    Attributes::Overflow::Id,
    Attributes::Resolution::Id,
    Attributes::RotationAxis::Id,
    Attributes::StepValue::Id,
    Attributes::TargetState::Id,
    Attributes::TranslationDirection::Id,
    Attributes::Unit::Id,
    Attributes::UnitRange::Id,
};

inline constexpr CommandId kEndpoint3EnabledCommands[] = {
    Commands::SetTarget::Id,
    Commands::Step::Id,
};

} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 2> kFixedClusterConfig = { {
    {
        .endpointNumber = 2,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint2EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint2EnabledCommands),
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
    case Attributes::ClusterRevision::Id:
    case Attributes::CurrentState::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::LatchControlModes::Id:
    case Attributes::LimitRange::Id:
    case Attributes::ModulationType::Id:
    case Attributes::Overflow::Id:
    case Attributes::Resolution::Id:
    case Attributes::RotationAxis::Id:
    case Attributes::StepValue::Id:
    case Attributes::TargetState::Id:
    case Attributes::TranslationDirection::Id:
    case Attributes::Unit::Id:
    case Attributes::UnitRange::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::SetTarget::Id:
    case Commands::Step::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace ClosureDimension
} // namespace Clusters
} // namespace app
} // namespace chip

