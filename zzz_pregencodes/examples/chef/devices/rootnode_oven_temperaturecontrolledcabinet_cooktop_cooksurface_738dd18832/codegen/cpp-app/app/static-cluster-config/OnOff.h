// DO NOT EDIT - Generated file
//
// Application configuration for OnOff based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/chef/devices/rootnode_oven_temperaturecontrolledcabinet_cooktop_cooksurface_738dd18832.matter
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
inline constexpr AttributeId kEndpoint3EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::OnOff::Id,
};

inline constexpr CommandId kEndpoint3EnabledCommands[] = {
    Commands::Off::Id,
};

inline constexpr AttributeId kEndpoint4EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::OnOff::Id,
};

inline constexpr CommandId kEndpoint4EnabledCommands[] = {
    Commands::Off::Id,
};

} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 2> kFixedClusterConfig = { {
    {
        .endpointNumber = 3,
        .featureMap = BitFlags<FeatureBitmapType> {
            FeatureBitmapType::kOffOnly// feature bit 0x4
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint3EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint3EnabledCommands),
    },
    {
        .endpointNumber = 4,
        .featureMap = BitFlags<FeatureBitmapType> {
            FeatureBitmapType::kOffOnly// feature bit 0x4
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint4EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint4EnabledCommands),
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

