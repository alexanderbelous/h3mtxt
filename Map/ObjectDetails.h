#pragma once

#include <h3mtxt/Map/ObjectDetailsData.h>
#include <h3mtxt/Map/Utils/ReservedData.h>

#include <cstdint>
#include <type_traits>
#include <variant>

namespace h3m
{
namespace Details_NS
{
  template<class Types>
  struct ObjectDetailsVariantTraits;

  template<std::underlying_type_t<MetaObjectType>... meta_object_type_idx>
  struct ObjectDetailsVariantTraits<std::integer_sequence<std::underlying_type_t<MetaObjectType>,
                                                          meta_object_type_idx...>>
  {
    using type = std::variant<ObjectDetailsData<static_cast<MetaObjectType>(meta_object_type_idx)>...>;
  };

  using ObjectDetailsVariant =
    typename ObjectDetailsVariantTraits<std::make_integer_sequence<std::underlying_type_t<MetaObjectType>,
                                                                   kNumMetaObjectTypes>>::type;
}

struct ObjectDetails
{
  // std::variant with kNumMetaObjectTypes alternatives, whose N-th alternative is ObjectDetailsData<N>.
  // TODO: consider making ObjectDetailsData a polymorphic class and using the Visitor pattern instead.
  // The size of the variant is already 288 bytes, even though most objects on the map will have little or
  // no details (e.g., decorative objects).
  using Data = Details_NS::ObjectDetailsVariant;

  // Coordinates of the bottom right corner.
  std::uint8_t x {};
  std::uint8_t y {};
  std::uint8_t z {};
  // 0-based index of the corresponding ObjectAttributes in Map.objects_attributes.
  std::uint32_t kind {};
  // Should be all 0s; kept here for compatibility.
  ReservedData<5> unknown {};
  // Object-specific data.
  // TODO: consider renaming to additional_info.
  Data details;
};

}
