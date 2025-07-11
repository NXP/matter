// DO NOT EDIT - Generated file
//
// Application configuration for MediaInput based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/placeholder/linux/apps/app2/config.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/MediaInput/AttributeIds.h>
#include <clusters/MediaInput/CommandIds.h>
#include <clusters/MediaInput/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace MediaInput {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint0EnabledAttributes[] = {
    Attributes::ClusterRevision::Id,
    Attributes::CurrentInput::Id,
    Attributes::InputList::Id,
};

inline constexpr CommandId kEndpoint0EnabledCommands[] = {
    Commands::HideInputStatus::Id,
    Commands::RenameInput::Id,
    Commands::SelectInput::Id,
    Commands::ShowInputStatus::Id,
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
    case Attributes::ClusterRevision::Id:
    case Attributes::CurrentInput::Id:
    case Attributes::InputList::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::HideInputStatus::Id:
    case Commands::RenameInput::Id:
    case Commands::SelectInput::Id:
    case Commands::ShowInputStatus::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace MediaInput
} // namespace Clusters
} // namespace app
} // namespace chip

