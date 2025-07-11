// DO NOT EDIT - Generated file
//
// Application configuration for LocalizationConfiguration based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/tv-casting-app/tv-casting-common/tv-casting-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/LocalizationConfiguration/AttributeIds.h>
#include <clusters/LocalizationConfiguration/CommandIds.h>
#include <clusters/LocalizationConfiguration/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace LocalizationConfiguration {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint0EnabledAttributes[] = {
    Attributes::ActiveLocale::Id,
    Attributes::ClusterRevision::Id,
    Attributes::FeatureMap::Id,
    Attributes::SupportedLocales::Id,
};
} // namespace detail

using FeatureBitmapType = Clusters::StaticApplicationConfig::NoFeatureFlagsDefined;

inline constexpr std::array<Clusters::StaticApplicationConfig::ClusterConfiguration<FeatureBitmapType>, 1> kFixedClusterConfig = { {
    {
        .endpointNumber = 0,
        .featureMap = BitFlags<FeatureBitmapType> {
        },
        .enabledAttributes = Span<const AttributeId>(detail::kEndpoint0EnabledAttributes),
        .enabledCommands = Span<const CommandId>(),
    },
} };

// If a specific attribute is supported at all across all endpoint static instantiations
inline constexpr bool IsAttributeEnabledOnSomeEndpoint(AttributeId attributeId) {
  switch (attributeId) {
    case Attributes::ActiveLocale::Id:
    case Attributes::ClusterRevision::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::SupportedLocales::Id:
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
} // namespace LocalizationConfiguration
} // namespace Clusters
} // namespace app
} // namespace chip

