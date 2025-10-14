// DO NOT EDIT - Generated file
//
// Application configuration for PushAvStreamTransport based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/all-clusters-app/all-clusters-common/all-clusters-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/PushAvStreamTransport/AttributeIds.h>
#include <clusters/PushAvStreamTransport/CommandIds.h>
#include <clusters/PushAvStreamTransport/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace PushAvStreamTransport {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::CurrentConnections::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::SupportedFormats::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::AllocatePushTransport::Id,
    Commands::AllocatePushTransportResponse::Id,
    Commands::DeallocatePushTransport::Id,
    Commands::FindTransport::Id,
    Commands::FindTransportResponse::Id,
    Commands::ManuallyTriggerTransport::Id,
    Commands::ModifyPushTransport::Id,
    Commands::SetTransportStatus::Id,
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
    case Attributes::AttributeList::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::CurrentConnections::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::SupportedFormats::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::AllocatePushTransport::Id:
    case Commands::AllocatePushTransportResponse::Id:
    case Commands::DeallocatePushTransport::Id:
    case Commands::FindTransport::Id:
    case Commands::FindTransportResponse::Id:
    case Commands::ManuallyTriggerTransport::Id:
    case Commands::ModifyPushTransport::Id:
    case Commands::SetTransportStatus::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace PushAvStreamTransport
} // namespace Clusters
} // namespace app
} // namespace chip

