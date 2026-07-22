// DO NOT EDIT - Generated file
//
// Application configuration for MediaFileManagement based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/tv-app/tv-common/tv-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/MediaFileManagement/AttributeIds.h>
#include <clusters/MediaFileManagement/CommandIds.h>
#include <clusters/MediaFileManagement/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace MediaFileManagement {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AvailableFiles::Id, Attributes::AvailableStorage::Id,   Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,     Attributes::SupportedMimeTypes::Id, Attributes::TotalStorage::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::AddFile::Id,   Commands::DeleteFile::Id,         Commands::GetSharedFile::Id,
    Commands::OfferFile::Id, Commands::RequestSharedFiles::Id,
};

} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 1,
        .featureMap =
            BitFlags<FeatureBitmapType>{
                FeatureBitmapType::kMediaSharing // feature bit 0x1
            },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint1EnabledAttributes),
        .enabledCommands   = Span<const CommandId>(detail::kEndpoint1EnabledCommands),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId)
{
    switch (attributeId)
    {
    case Attributes::AvailableFiles::Id:
    case Attributes::AvailableStorage::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::SupportedMimeTypes::Id:
    case Attributes::TotalStorage::Id:
        return true;
    default:
        return false;
    }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId)
{
    switch (commandId)
    {
    case Commands::AddFile::Id:
    case Commands::DeleteFile::Id:
    case Commands::GetSharedFile::Id:
    case Commands::OfferFile::Id:
    case Commands::RequestSharedFiles::Id:
        return true;
    default:
        return false;
    }
}

} // namespace StaticApplicationConfig
} // namespace MediaFileManagement
} // namespace Clusters
} // namespace app
} // namespace chip
