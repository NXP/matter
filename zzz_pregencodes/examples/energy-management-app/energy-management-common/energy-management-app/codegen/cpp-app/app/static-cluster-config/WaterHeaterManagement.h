// DO NOT EDIT - Generated file
//
// Application configuration for WaterHeaterManagement based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/energy-management-app/energy-management-common/energy-management-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/WaterHeaterManagement/AttributeIds.h>
#include <clusters/WaterHeaterManagement/CommandIds.h>
#include <clusters/WaterHeaterManagement/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace WaterHeaterManagement {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint2EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::BoostState::Id,
    Attributes::ClusterRevision::Id,
    Attributes::EstimatedHeatRequired::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::HeatDemand::Id,
    Attributes::HeaterTypes::Id,
    Attributes::TankPercentage::Id,
    Attributes::TankVolume::Id,
};

inline constexpr CommandId kEndpoint2EnabledCommands[] = {
    Commands::Boost::Id,
    Commands::CancelBoost::Id,
};

} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 2,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint2EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint2EnabledCommands),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId) {
  switch (attributeId) {
    case Attributes::AcceptedCommandList::Id:
    case Attributes::AttributeList::Id:
    case Attributes::BoostState::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::EstimatedHeatRequired::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::HeatDemand::Id:
    case Attributes::HeaterTypes::Id:
    case Attributes::TankPercentage::Id:
    case Attributes::TankVolume::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::Boost::Id:
    case Commands::CancelBoost::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace WaterHeaterManagement
} // namespace Clusters
} // namespace app
} // namespace chip

