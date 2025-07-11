// DO NOT EDIT - Generated file
//
// Application configuration for OnOff based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/pump-app/silabs/data_model/pump-thread-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/OnOff/AttributeIds.h>
#include <clusters/OnOff/CommandIds.h>
#include <clusters/OnOff/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace OnOff {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::OnOff::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::Off::Id,
    Commands::On::Id,
    Commands::Toggle::Id,
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
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::OnOff::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::Off::Id:
    case Commands::On::Id:
    case Commands::Toggle::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace OnOff
} // namespace Clusters
} // namespace app
} // namespace chip

