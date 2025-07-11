// DO NOT EDIT - Generated file
//
// Application configuration for GeneralCommissioning based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/terms-and-conditions-app/terms-and-conditions-common/terms-and-conditions-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/GeneralCommissioning/AttributeIds.h>
#include <clusters/GeneralCommissioning/CommandIds.h>
#include <clusters/GeneralCommissioning/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace GeneralCommissioning {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint0EnabledAttributes[] = {
    Attributes::BasicCommissioningInfo::Id,
    Attributes::Breadcrumb::Id,
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::LocationCapability::Id,
    Attributes::RegulatoryConfig::Id,
    Attributes::SupportsConcurrentConnection::Id,
    Attributes::TCAcceptedVersion::Id,
    Attributes::TCAcknowledgements::Id,
    Attributes::TCAcknowledgementsRequired::Id,
    Attributes::TCMinRequiredVersion::Id,
    Attributes::TCUpdateDeadline::Id,
};

inline constexpr CommandId kEndpoint0EnabledCommands[] = {
    Commands::ArmFailSafe::Id,
    Commands::ArmFailSafeResponse::Id,
    Commands::CommissioningComplete::Id,
    Commands::CommissioningCompleteResponse::Id,
    Commands::SetRegulatoryConfig::Id,
    Commands::SetRegulatoryConfigResponse::Id,
    Commands::SetTCAcknowledgements::Id,
    Commands::SetTCAcknowledgementsResponse::Id,
};

} // namespace detail

using FeatureBitmapType = Feature;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 0,
        .featureMap = BitFlags<FeatureBitmapType> {
            FeatureBitmapType::kTermsAndConditions// feature bit 0x1
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint0EnabledAttributes),
        .enabledCommands = Span<const CommandId>(detail::kEndpoint0EnabledCommands),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId) {
  switch (attributeId) {
    case Attributes::TCAcceptedVersion::Id:
    case Attributes::TCAcknowledgements::Id:
    case Attributes::TCAcknowledgementsRequired::Id:
    case Attributes::TCMinRequiredVersion::Id:
    case Attributes::TCUpdateDeadline::Id:
    case Attributes::BasicCommissioningInfo::Id:
    case Attributes::Breadcrumb::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::LocationCapability::Id:
    case Attributes::RegulatoryConfig::Id:
    case Attributes::SupportsConcurrentConnection::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::ArmFailSafe::Id:
    case Commands::ArmFailSafeResponse::Id:
    case Commands::CommissioningComplete::Id:
    case Commands::CommissioningCompleteResponse::Id:
    case Commands::SetRegulatoryConfig::Id:
    case Commands::SetRegulatoryConfigResponse::Id:
    case Commands::SetTCAcknowledgements::Id:
    case Commands::SetTCAcknowledgementsResponse::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace GeneralCommissioning
} // namespace Clusters
} // namespace app
} // namespace chip

