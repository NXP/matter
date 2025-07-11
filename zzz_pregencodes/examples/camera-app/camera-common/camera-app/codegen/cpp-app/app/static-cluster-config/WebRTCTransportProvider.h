// DO NOT EDIT - Generated file
//
// Application configuration for WebRTCTransportProvider based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/camera-app/camera-common/camera-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/WebRTCTransportProvider/AttributeIds.h>
#include <clusters/WebRTCTransportProvider/CommandIds.h>
#include <clusters/WebRTCTransportProvider/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace WebRTCTransportProvider {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::CurrentSessions::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::EndSession::Id,
    Commands::ProvideAnswer::Id,
    Commands::ProvideICECandidates::Id,
    Commands::ProvideOffer::Id,
    Commands::ProvideOfferResponse::Id,
    Commands::SolicitOffer::Id,
    Commands::SolicitOfferResponse::Id,
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
    case Attributes::CurrentSessions::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::EndSession::Id:
    case Commands::ProvideAnswer::Id:
    case Commands::ProvideICECandidates::Id:
    case Commands::ProvideOffer::Id:
    case Commands::ProvideOfferResponse::Id:
    case Commands::SolicitOffer::Id:
    case Commands::SolicitOfferResponse::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace WebRTCTransportProvider
} // namespace Clusters
} // namespace app
} // namespace chip

