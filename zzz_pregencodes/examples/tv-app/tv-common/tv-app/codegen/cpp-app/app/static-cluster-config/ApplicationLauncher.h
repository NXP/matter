// DO NOT EDIT - Generated file
//
// Application configuration for ApplicationLauncher based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/tv-app/tv-common/tv-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/ApplicationLauncher/AttributeIds.h>
#include <clusters/ApplicationLauncher/CommandIds.h>
#include <clusters/ApplicationLauncher/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace ApplicationLauncher {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::CatalogList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::CurrentApp::Id,
    Attributes::FeatureMap::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::HideApp::Id,
    Commands::LaunchApp::Id,
    Commands::LauncherResponse::Id,
    Commands::StopApp::Id,
};

inline constexpr AttributeId kEndpoint3EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
};

inline constexpr CommandId kEndpoint3EnabledCommands[] = {
    Commands::HideApp::Id,
    Commands::LaunchApp::Id,
    Commands::LauncherResponse::Id,
    Commands::StopApp::Id,
};

} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 2> kFixedClusterConfig = { {
    {
        .endpointNumber = 1,
        .featureMap = BitFlags<FeatureBitmapType> {
            FeatureBitmapType::kApplicationPlatform// feature bit 0x1
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint1EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint1EnabledCommands),
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
    case Attributes::CatalogList::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::CurrentApp::Id:
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
    case Commands::HideApp::Id:
    case Commands::LaunchApp::Id:
    case Commands::LauncherResponse::Id:
    case Commands::StopApp::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace ApplicationLauncher
} // namespace Clusters
} // namespace app
} // namespace chip

