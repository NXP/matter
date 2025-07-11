// DO NOT EDIT - Generated file
//
// Application configuration for ContentLauncher based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/nxp-media-app/nxp-media-common/nxp-media-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/ContentLauncher/AttributeIds.h>
#include <clusters/ContentLauncher/CommandIds.h>
#include <clusters/ContentLauncher/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace ContentLauncher {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AcceptHeader::Id,
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::SupportedStreamingProtocols::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::LaunchContent::Id,
    Commands::LauncherResponse::Id,
    Commands::LaunchURL::Id,
};

inline constexpr AttributeId kEndpoint3EnabledAttributes[] = {
    Attributes::AcceptHeader::Id,
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::SupportedStreamingProtocols::Id,
};

inline constexpr CommandId kEndpoint3EnabledCommands[] = {
    Commands::LaunchContent::Id,
    Commands::LauncherResponse::Id,
    Commands::LaunchURL::Id,
};

} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 2> kFixedClusterConfig = { {
    {
        .endpointNumber = 1,
        .featureMap = BitFlags<FeatureBitmapType> {
            FeatureBitmapType::kContentSearch, // feature bit 0x1
            FeatureBitmapType::kURLPlayback// feature bit 0x2
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint1EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint1EnabledCommands),
    },
    {
        .endpointNumber = 3,
        .featureMap = BitFlags<FeatureBitmapType> {
            FeatureBitmapType::kContentSearch, // feature bit 0x1
            FeatureBitmapType::kURLPlayback// feature bit 0x2
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint3EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint3EnabledCommands),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId) {
  switch (attributeId) {
    case Attributes::AcceptHeader::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::SupportedStreamingProtocols::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::LaunchContent::Id:
    case Commands::LaunchURL::Id:
    case Commands::LauncherResponse::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace ContentLauncher
} // namespace Clusters
} // namespace app
} // namespace chip

