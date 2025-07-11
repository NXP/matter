// DO NOT EDIT - Generated file
//
// Application configuration for JointFabricAdministrator based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/jf-admin-app/jfa-common/jfa-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/JointFabricAdministrator/AttributeIds.h>
#include <clusters/JointFabricAdministrator/CommandIds.h>
#include <clusters/JointFabricAdministrator/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace JointFabricAdministrator {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AdministratorFabricIndex::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::AddICAC::Id,
    Commands::AnnounceJointFabricAdministrator::Id,
    Commands::ICACCSRRequest::Id,
    Commands::ICACCSRResponse::Id,
    Commands::ICACResponse::Id,
    Commands::OpenJointCommissioningWindow::Id,
    Commands::TransferAnchorComplete::Id,
    Commands::TransferAnchorRequest::Id,
    Commands::TransferAnchorResponse::Id,
};

} // namespace detail

using FeatureBitmapType = Clusters::StaticApplicationConfig::NoFeatureFlagsDefined;

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
    case Attributes::AdministratorFabricIndex::Id:
    case Attributes::AttributeList::Id:
    case Attributes::ClusterRevision::Id:
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
    case Commands::AddICAC::Id:
    case Commands::AnnounceJointFabricAdministrator::Id:
    case Commands::ICACCSRRequest::Id:
    case Commands::ICACCSRResponse::Id:
    case Commands::ICACResponse::Id:
    case Commands::OpenJointCommissioningWindow::Id:
    case Commands::TransferAnchorComplete::Id:
    case Commands::TransferAnchorRequest::Id:
    case Commands::TransferAnchorResponse::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace JointFabricAdministrator
} // namespace Clusters
} // namespace app
} // namespace chip

