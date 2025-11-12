// DO NOT EDIT - Generated file
//
// Application configuration for TlsCertificateManagement based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/camera-app/camera-common/camera-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/TlsCertificateManagement/AttributeIds.h>
#include <clusters/TlsCertificateManagement/CommandIds.h>
#include <clusters/TlsCertificateManagement/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace TlsCertificateManagement {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::MaxClientCertificates::Id,
    Attributes::MaxRootCertificates::Id,
    Attributes::ProvisionedClientCertificates::Id,
    Attributes::ProvisionedRootCertificates::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::ClientCSR::Id,
    Commands::ClientCSRResponse::Id,
    Commands::FindClientCertificate::Id,
    Commands::FindClientCertificateResponse::Id,
    Commands::FindRootCertificate::Id,
    Commands::FindRootCertificateResponse::Id,
    Commands::LookupClientCertificate::Id,
    Commands::LookupClientCertificateResponse::Id,
    Commands::LookupRootCertificate::Id,
    Commands::LookupRootCertificateResponse::Id,
    Commands::ProvisionClientCertificate::Id,
    Commands::ProvisionRootCertificate::Id,
    Commands::ProvisionRootCertificateResponse::Id,
    Commands::RemoveClientCertificate::Id,
    Commands::RemoveRootCertificate::Id,
};

} // namespace detail

using FeatureBitmapType = Clusters::StaticApplicationConfig::NoFeatureFlagsDefined;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber    = 1,
        .featureMap        = BitFlags<FeatureBitmapType>{},
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint1EnabledAttributes),
        .enabledCommands   = Span<const CommandId>(detail::kEndpoint1EnabledCommands),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId)
{
    switch (attributeId)
    {
    case Attributes::AcceptedCommandList::Id:
    case Attributes::AttributeList::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::MaxClientCertificates::Id:
    case Attributes::MaxRootCertificates::Id:
    case Attributes::ProvisionedClientCertificates::Id:
    case Attributes::ProvisionedRootCertificates::Id:
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
    case Commands::ClientCSR::Id:
    case Commands::ClientCSRResponse::Id:
    case Commands::FindClientCertificate::Id:
    case Commands::FindClientCertificateResponse::Id:
    case Commands::FindRootCertificate::Id:
    case Commands::FindRootCertificateResponse::Id:
    case Commands::LookupClientCertificate::Id:
    case Commands::LookupClientCertificateResponse::Id:
    case Commands::LookupRootCertificate::Id:
    case Commands::LookupRootCertificateResponse::Id:
    case Commands::ProvisionClientCertificate::Id:
    case Commands::ProvisionRootCertificate::Id:
    case Commands::ProvisionRootCertificateResponse::Id:
    case Commands::RemoveClientCertificate::Id:
    case Commands::RemoveRootCertificate::Id:
        return true;
    default:
        return false;
    }
}

} // namespace StaticApplicationConfig
} // namespace TlsCertificateManagement
} // namespace Clusters
} // namespace app
} // namespace chip
