// DO NOT EDIT - Generated file
//
// Application configuration for CommodityPrice based on EMBER configuration
// from /opt/matter/matter_dev/connectedhomeip/examples/energy-gateway-app/energy-gateway-common/energy-gateway-app.matter
#pragma once

#include <app/util/cluster-config.h>
#include <clusters/CommodityPrice/AttributeIds.h>
#include <clusters/CommodityPrice/CommandIds.h>
#include <clusters/CommodityPrice/Enums.h>

#include <array>

namespace chip {
namespace app {
namespace Clusters {
namespace CommodityPrice {
namespace StaticApplicationConfig {
namespace detail {
inline constexpr AttributeId kEndpoint1EnabledAttributes[] = {
    Attributes::AcceptedCommandList::Id,
    Attributes::AttributeList::Id,
    Attributes::ClusterRevision::Id,
    Attributes::Currency::Id,
    Attributes::CurrentPrice::Id,
    Attributes::FeatureMap::Id,
    Attributes::GeneratedCommandList::Id,
    Attributes::PriceForecast::Id,
    Attributes::TariffUnit::Id,
};

inline constexpr CommandId kEndpoint1EnabledCommands[] = {
    Commands::GetDetailedForecastRequest::Id,
    Commands::GetDetailedForecastResponse::Id,
    Commands::GetDetailedPriceRequest::Id,
    Commands::GetDetailedPriceResponse::Id,
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
    case Attributes::Currency::Id:
    case Attributes::CurrentPrice::Id:
    case Attributes::FeatureMap::Id:
    case Attributes::GeneratedCommandList::Id:
    case Attributes::PriceForecast::Id:
    case Attributes::TariffUnit::Id:
      return true;
    default:
      return false;
  }
}

// If a specific command is supported at all across all endpoint static instantiations
inline constexpr bool IsCommandEnabledOnSomeEndpoint(CommandId commandId) {
  switch (commandId) {
    case Commands::GetDetailedForecastRequest::Id:
    case Commands::GetDetailedForecastResponse::Id:
    case Commands::GetDetailedPriceRequest::Id:
    case Commands::GetDetailedPriceResponse::Id:
      return true;
    default:
      return false;
  }
}

} // namespace StaticApplicationConfig
} // namespace CommodityPrice
} // namespace Clusters
} // namespace app
} // namespace chip

