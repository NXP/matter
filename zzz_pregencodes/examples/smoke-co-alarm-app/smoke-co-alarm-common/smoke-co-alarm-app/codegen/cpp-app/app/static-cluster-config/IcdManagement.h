// DO NOT EDIT - Generated file
//
// Application configuration for IcdManagement based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/smoke-co-alarm-app/smoke-co-alarm-common/smoke-co-alarm-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/IcdManagement/AttributeIds.h>
#include <clusters/IcdManagement/CommandIds.h>
#include <clusters/IcdManagement/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace IcdManagement {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint0EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::ActiveModeDuration::Id,
    Attributes::ActiveModeThreshold::Id,
    Attributes::AttributeList::Id,
    Attributes::ClientsSupportedPerFabric::Id,
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::ICDCounter::Id,
    Attributes::IdleModeDuration::Id,
    Attributes::RegisteredClients::Id,
};

inline constexpr CommandId kEndpoint0EnabledCommands[] = {
    Commands::RegisterClient::Id,
    Commands::RegisterClientResponse::Id,
    Commands::StayActiveRequest::Id,
    Commands::UnregisterClient::Id,
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
    case Attributes::ICDCounter::Id:
    case Attributes::AcceptedCommandList::Id:
    case Attributes::ActiveModeDuration::Id:
    case Attributes::ActiveModeThreshold::Id:
    case Attributes::AttributeList::Id:
    case Attributes::ClientsSupportedPerFabric::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::IdleModeDuration::Id:
    case Attributes::RegisteredClients::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::RegisterClient::Id:
    case Commands::RegisterClientResponse::Id:
    case Commands::StayActiveRequest::Id:
    case Commands::UnregisterClient::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace IcdManagement
} // namespace Clusters
} // namespace app
} // namespace chip

