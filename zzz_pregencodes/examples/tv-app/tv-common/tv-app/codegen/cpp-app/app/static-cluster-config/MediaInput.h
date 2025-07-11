// DO NOT EDIT - Generated file
//
// Application configuration for MediaInput based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/tv-app/tv-common/tv-app.matter
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
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::ClusterRevision::Id,
    Attributes::CurrentInput::Id,
    Attributes::FeatureMap::Id,
    Attributes::InputList::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::HideInputStatus::Id,
    Commands::RenameInput::Id,
    Commands::SelectInput::Id,
    Commands::ShowInputStatus::Id,
};

} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 1,
        .featureMap = BitFlags<FeatureBitmapType> {
            FeatureBitmapType::kNameUpdates// feature bit 0x1
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint1EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint1EnabledCommands),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId) {
  switch (attributeId) {
    case Attributes::ClusterRevision::Id:
    case Attributes::CurrentInput::Id:
    case Attributes::FeatureMap::Id:
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

