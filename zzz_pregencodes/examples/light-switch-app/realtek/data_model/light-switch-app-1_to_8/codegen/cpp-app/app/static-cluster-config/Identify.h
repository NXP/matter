// DO NOT EDIT - Generated file
//
// Application configuration for Identify based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/light-switch-app/realtek/data_model/light-switch-app-1_to_8.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/Identify/AttributeIds.h>
#include <clusters/Identify/CommandIds.h>
#include <clusters/Identify/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace Identify {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::IdentifyTime::Id,
    Attributes::IdentifyType::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::Identify::Id,
    Commands::TriggerEffect::Id,
};

inline constexpr AttributeId kEndpoint2EnabledAttributes[] = {
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::IdentifyTime::Id,
    Attributes::IdentifyType::Id,
};

inline constexpr CommandId kEndpoint2EnabledCommands[] = {
    Commands::Identify::Id,
    Commands::TriggerEffect::Id,
};

inline constexpr AttributeId kEndpoint3EnabledAttributes[] = {
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::IdentifyTime::Id,
    Attributes::IdentifyType::Id,
};

inline constexpr CommandId kEndpoint3EnabledCommands[] = {
    Commands::Identify::Id,
    Commands::TriggerEffect::Id,
};

inline constexpr AttributeId kEndpoint4EnabledAttributes[] = {
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::IdentifyTime::Id,
    Attributes::IdentifyType::Id,
};

inline constexpr CommandId kEndpoint4EnabledCommands[] = {
    Commands::Identify::Id,
    Commands::TriggerEffect::Id,
};

inline constexpr AttributeId kEndpoint5EnabledAttributes[] = {
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::IdentifyTime::Id,
    Attributes::IdentifyType::Id,
};

inline constexpr CommandId kEndpoint5EnabledCommands[] = {
    Commands::Identify::Id,
    Commands::TriggerEffect::Id,
};

inline constexpr AttributeId kEndpoint6EnabledAttributes[] = {
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::IdentifyTime::Id,
    Attributes::IdentifyType::Id,
};

inline constexpr CommandId kEndpoint6EnabledCommands[] = {
    Commands::Identify::Id,
    Commands::TriggerEffect::Id,
};

inline constexpr AttributeId kEndpoint7EnabledAttributes[] = {
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::IdentifyTime::Id,
    Attributes::IdentifyType::Id,
};

inline constexpr CommandId kEndpoint7EnabledCommands[] = {
    Commands::Identify::Id,
    Commands::TriggerEffect::Id,
};

inline constexpr AttributeId kEndpoint8EnabledAttributes[] = {
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::IdentifyTime::Id,
    Attributes::IdentifyType::Id,
};

inline constexpr CommandId kEndpoint8EnabledCommands[] = {
    Commands::Identify::Id,
    Commands::TriggerEffect::Id,
};

inline constexpr AttributeId kEndpoint9EnabledAttributes[] = {
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::IdentifyTime::Id,
    Attributes::IdentifyType::Id,
};

inline constexpr CommandId kEndpoint9EnabledCommands[] = {
    Commands::Identify::Id,
    Commands::TriggerEffect::Id,
};

inline constexpr AttributeId kEndpoint10EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::IdentifyTime::Id,
    Attributes::IdentifyType::Id,
};

inline constexpr CommandId kEndpoint10EnabledCommands[] = {
    Commands::Identify::Id,
    Commands::TriggerEffect::Id,
};

} // namespace detail

using FeatureBitmapType = Clusters::StaticApplicationConfig::NoFeatureFlagsDefined;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 10> kFixedClusterConfig = { {
    {
        .endpointNumber = 1,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint1EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint1EnabledCommands),
    },
    {
        .endpointNumber = 2,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint2EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint2EnabledCommands),
    },
    {
        .endpointNumber = 3,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint3EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint3EnabledCommands),
    },
    {
        .endpointNumber = 4,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint4EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint4EnabledCommands),
    },
    {
        .endpointNumber = 5,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint5EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint5EnabledCommands),
    },
    {
        .endpointNumber = 6,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint6EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint6EnabledCommands),
    },
    {
        .endpointNumber = 7,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint7EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint7EnabledCommands),
    },
    {
        .endpointNumber = 8,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint8EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint8EnabledCommands),
    },
    {
        .endpointNumber = 9,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint9EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint9EnabledCommands),
    },
    {
        .endpointNumber = 10,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint10EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint10EnabledCommands),
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
    case Attributes::IdentifyTime::Id:
    case Attributes::IdentifyType::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::Identify::Id:
    case Commands::TriggerEffect::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace Identify
} // namespace Clusters
} // namespace app
} // namespace chip

