// DO NOT EDIT - Generated file
//
// Application configuration for ScenesManagement based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/placeholder/linux/apps/app1/config.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/ScenesManagement/AttributeIds.h>
#include <clusters/ScenesManagement/CommandIds.h>
#include <clusters/ScenesManagement/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace ScenesManagement {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::FabricSceneInfo::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::SceneTableSize::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::AddScene::Id,
    Commands::AddSceneResponse::Id,
    Commands::GetSceneMembership::Id,
    Commands::GetSceneMembershipResponse::Id,
    Commands::RecallScene::Id,
    Commands::RemoveAllScenes::Id,
    Commands::RemoveAllScenesResponse::Id,
    Commands::RemoveScene::Id,
    Commands::RemoveSceneResponse::Id,
    Commands::StoreScene::Id,
    Commands::StoreSceneResponse::Id,
    Commands::ViewScene::Id,
    Commands::ViewSceneResponse::Id,
};

} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 1,
        .featureMap = BitFlags<FeatureBitmapType> {
            FeatureBitmapType::kSceneNames// feature bit 0x1
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
    case Attributes::FabricSceneInfo::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::SceneTableSize::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::AddScene::Id:
    case Commands::AddSceneResponse::Id:
    case Commands::GetSceneMembership::Id:
    case Commands::GetSceneMembershipResponse::Id:
    case Commands::RecallScene::Id:
    case Commands::RemoveAllScenes::Id:
    case Commands::RemoveAllScenesResponse::Id:
    case Commands::RemoveScene::Id:
    case Commands::RemoveSceneResponse::Id:
    case Commands::StoreScene::Id:
    case Commands::StoreSceneResponse::Id:
    case Commands::ViewScene::Id:
    case Commands::ViewSceneResponse::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace ScenesManagement
} // namespace Clusters
} // namespace app
} // namespace chip

