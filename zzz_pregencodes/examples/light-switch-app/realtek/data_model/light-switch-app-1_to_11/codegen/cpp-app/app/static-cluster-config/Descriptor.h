// DO NOT EDIT - Generated file
//
// Application configuration for Descriptor based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/light-switch-app/realtek/data_model/light-switch-app-1_to_11.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/Descriptor/AttributeIds.h>
#include <clusters/Descriptor/CommandIds.h>
#include <clusters/Descriptor/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace Descriptor {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint0EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClientList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::DeviceTypeList::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::PartsList::Id,
    Attributes::ServerList::Id,
};
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AttributeList::Id,
    Attributes::ClientList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::DeviceTypeList::Id,
    Attributes::FeatureMap::Id,
    Attributes::PartsList::Id,
    Attributes::ServerList::Id,
    Attributes::TagList::Id,
};
inline constexpr AttributeId kEndpoint2EnabledAttributes[] = {
    Attributes::ClientList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::DeviceTypeList::Id,
    Attributes::FeatureMap::Id,
    Attributes::PartsList::Id,
    Attributes::ServerList::Id,
    Attributes::TagList::Id,
};
inline constexpr AttributeId kEndpoint3EnabledAttributes[] = {
    Attributes::ClientList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::DeviceTypeList::Id,
    Attributes::FeatureMap::Id,
    Attributes::PartsList::Id,
    Attributes::ServerList::Id,
    Attributes::TagList::Id,
};
inline constexpr AttributeId kEndpoint4EnabledAttributes[] = {
    Attributes::ClientList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::DeviceTypeList::Id,
    Attributes::FeatureMap::Id,
    Attributes::PartsList::Id,
    Attributes::ServerList::Id,
    Attributes::TagList::Id,
};
inline constexpr AttributeId kEndpoint5EnabledAttributes[] = {
    Attributes::ClientList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::DeviceTypeList::Id,
    Attributes::FeatureMap::Id,
    Attributes::PartsList::Id,
    Attributes::ServerList::Id,
    Attributes::TagList::Id,
};
inline constexpr AttributeId kEndpoint6EnabledAttributes[] = {
    Attributes::ClientList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::DeviceTypeList::Id,
    Attributes::FeatureMap::Id,
    Attributes::PartsList::Id,
    Attributes::ServerList::Id,
    Attributes::TagList::Id,
};
inline constexpr AttributeId kEndpoint7EnabledAttributes[] = {
    Attributes::ClientList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::DeviceTypeList::Id,
    Attributes::FeatureMap::Id,
    Attributes::PartsList::Id,
    Attributes::ServerList::Id,
    Attributes::TagList::Id,
};
inline constexpr AttributeId kEndpoint8EnabledAttributes[] = {
    Attributes::ClientList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::DeviceTypeList::Id,
    Attributes::FeatureMap::Id,
    Attributes::PartsList::Id,
    Attributes::ServerList::Id,
    Attributes::TagList::Id,
};
inline constexpr AttributeId kEndpoint9EnabledAttributes[] = {
    Attributes::ClientList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::DeviceTypeList::Id,
    Attributes::FeatureMap::Id,
    Attributes::PartsList::Id,
    Attributes::ServerList::Id,
    Attributes::TagList::Id,
};
inline constexpr AttributeId kEndpoint10EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClientList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::DeviceTypeList::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::PartsList::Id,
    Attributes::ServerList::Id,
};
inline constexpr AttributeId kEndpoint11EnabledAttributes[] = {
    Attributes::ClientList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::DeviceTypeList::Id,
    Attributes::FeatureMap::Id,
    Attributes::PartsList::Id,
    Attributes::ServerList::Id,
    Attributes::TagList::Id,
};
inline constexpr AttributeId kEndpoint12EnabledAttributes[] = {
    Attributes::ClientList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::DeviceTypeList::Id,
    Attributes::FeatureMap::Id,
    Attributes::PartsList::Id,
    Attributes::ServerList::Id,
    Attributes::TagList::Id,
};
inline constexpr AttributeId kEndpoint13EnabledAttributes[] = {
    Attributes::ClientList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::DeviceTypeList::Id,
    Attributes::FeatureMap::Id,
    Attributes::PartsList::Id,
    Attributes::ServerList::Id,
    Attributes::TagList::Id,
};
} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 14> kFixedClusterConfig = { {
    {
        .endpointNumber = 0,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint0EnabledAttributes),
        .enabledCommands = Span<const CommandId>(),
    },
    {
        .endpointNumber = 1,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint1EnabledAttributes),
        .enabledCommands = Span<const CommandId>(),
    },
    {
        .endpointNumber = 2,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint2EnabledAttributes),
        .enabledCommands = Span<const CommandId>(),
    },
    {
        .endpointNumber = 3,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint3EnabledAttributes),
        .enabledCommands = Span<const CommandId>(),
    },
    {
        .endpointNumber = 4,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint4EnabledAttributes),
        .enabledCommands = Span<const CommandId>(),
    },
    {
        .endpointNumber = 5,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint5EnabledAttributes),
        .enabledCommands = Span<const CommandId>(),
    },
    {
        .endpointNumber = 6,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint6EnabledAttributes),
        .enabledCommands = Span<const CommandId>(),
    },
    {
        .endpointNumber = 7,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint7EnabledAttributes),
        .enabledCommands = Span<const CommandId>(),
    },
    {
        .endpointNumber = 8,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint8EnabledAttributes),
        .enabledCommands = Span<const CommandId>(),
    },
    {
        .endpointNumber = 9,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint9EnabledAttributes),
        .enabledCommands = Span<const CommandId>(),
    },
    {
        .endpointNumber = 10,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint10EnabledAttributes),
        .enabledCommands = Span<const CommandId>(),
    },
    {
        .endpointNumber = 11,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint11EnabledAttributes),
        .enabledCommands = Span<const CommandId>(),
    },
    {
        .endpointNumber = 12,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint12EnabledAttributes),
        .enabledCommands = Span<const CommandId>(),
    },
    {
        .endpointNumber = 13,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint13EnabledAttributes),
        .enabledCommands = Span<const CommandId>(),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId) {
  switch (attributeId) {
    case Attributes::AcceptedCommandList::Id:
    case Attributes::AttributeList::Id:
    case Attributes::ClientList::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::DeviceTypeList::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::PartsList::Id:
    case Attributes::ServerList::Id:
    case Attributes::TagList::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace Descriptor
} // namespace Clusters
} // namespace app
} // namespace chip

