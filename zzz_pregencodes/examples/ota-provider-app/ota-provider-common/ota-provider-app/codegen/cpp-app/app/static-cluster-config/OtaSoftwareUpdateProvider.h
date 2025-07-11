// DO NOT EDIT - Generated file
//
// Application configuration for OtaSoftwareUpdateProvider based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/ota-provider-app/ota-provider-common/ota-provider-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/OtaSoftwareUpdateProvider/AttributeIds.h>
#include <clusters/OtaSoftwareUpdateProvider/CommandIds.h>
#include <clusters/OtaSoftwareUpdateProvider/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace OtaSoftwareUpdateProvider {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint0EnabledAttributes[] = {
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
};

inline constexpr CommandId kEndpoint0EnabledCommands[] = {
    Commands::ApplyUpdateRequest::Id,
    Commands::ApplyUpdateResponse::Id,
    Commands::NotifyUpdateApplied::Id,
    Commands::QueryImage::Id,
    Commands::QueryImageResponse::Id,
};

} // namespace detail

using FeatureBitmapType = Clusters::StaticApplicationConfig::NoFeatureFlagsDefined;

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
    case Attributes::ClusterRevision::Id:
    case Attributes::FeatureMap::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::ApplyUpdateRequest::Id:
    case Commands::ApplyUpdateResponse::Id:
    case Commands::NotifyUpdateApplied::Id:
    case Commands::QueryImage::Id:
    case Commands::QueryImageResponse::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace OtaSoftwareUpdateProvider
} // namespace Clusters
} // namespace app
} // namespace chip

