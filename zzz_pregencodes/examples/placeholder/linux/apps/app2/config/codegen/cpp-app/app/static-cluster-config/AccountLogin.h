// DO NOT EDIT - Generated file
//
// Application configuration for AccountLogin based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/placeholder/linux/apps/app2/config.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/AccountLogin/AttributeIds.h>
#include <clusters/AccountLogin/CommandIds.h>
#include <clusters/AccountLogin/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace AccountLogin {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint0EnabledAttributes[] = {
    Attributes::ClusterRevision::Id,
};

inline constexpr CommandId kEndpoint0EnabledCommands[] = {
    Commands::GetSetupPIN::Id,
    Commands::GetSetupPINResponse::Id,
    Commands::Login::Id,
    Commands::Logout::Id,
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
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::GetSetupPIN::Id:
    case Commands::GetSetupPINResponse::Id:
    case Commands::Login::Id:
    case Commands::Logout::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace AccountLogin
} // namespace Clusters
} // namespace app
} // namespace chip

