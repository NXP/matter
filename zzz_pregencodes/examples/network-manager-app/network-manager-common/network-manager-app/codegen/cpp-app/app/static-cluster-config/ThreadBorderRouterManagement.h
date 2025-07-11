// DO NOT EDIT - Generated file
//
// Application configuration for ThreadBorderRouterManagement based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/network-manager-app/network-manager-common/network-manager-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/ThreadBorderRouterManagement/AttributeIds.h>
#include <clusters/ThreadBorderRouterManagement/CommandIds.h>
#include <clusters/ThreadBorderRouterManagement/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace ThreadBorderRouterManagement {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::ActiveDatasetTimestamp::Id,
    Attributes::AttributeList::Id,
    Attributes::BorderAgentID::Id,
    Attributes::BorderRouterName::Id,
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::InterfaceEnabled::Id,
    Attributes::PendingDatasetTimestamp::Id,
    Attributes::ThreadVersion::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::DatasetResponse::Id,
    Commands::GetActiveDatasetRequest::Id,
    Commands::GetPendingDatasetRequest::Id,
    Commands::SetActiveDatasetRequest::Id,
    Commands::SetPendingDatasetRequest::Id,
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
    case Attributes::AcceptedCommandList::Id:
    case Attributes::ActiveDatasetTimestamp::Id:
    case Attributes::AttributeList::Id:
    case Attributes::BorderAgentID::Id:
    case Attributes::BorderRouterName::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::InterfaceEnabled::Id:
    case Attributes::PendingDatasetTimestamp::Id:
    case Attributes::ThreadVersion::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::DatasetResponse::Id:
    case Commands::GetActiveDatasetRequest::Id:
    case Commands::GetPendingDatasetRequest::Id:
    case Commands::SetActiveDatasetRequest::Id:
    case Commands::SetPendingDatasetRequest::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace ThreadBorderRouterManagement
} // namespace Clusters
} // namespace app
} // namespace chip

