#include <h3mtxt/H3MJsonReader/readH3mJson.h>

#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/H3MJsonReader/JsonReader.h>
#include <h3mtxt/H3MJsonReader/readGlobalEvent.h>
#include <h3mtxt/H3MJsonReader/readMapAdditionalInfo.h>
#include <h3mtxt/H3MJsonReader/readMapBasicInfo.h>
#include <h3mtxt/H3MJsonReader/readObjectAttributes.h>
#include <h3mtxt/H3MJsonReader/readObjectDetailsData.h>
#include <h3mtxt/H3MJsonReader/readPlayerSpecs.h>
#include <h3mtxt/H3MJsonReader/readTile.h>

#include <stdexcept>

namespace h3m
{
  namespace
  {
    // Checks if JsonReader is specialized for ObjectDetailsData<T> where T == meta_object_type.
    // TODO: remove.
    constexpr bool isImplementedObjectDetailsDataReader(MetaObjectType meta_object_type)
    {
      // The underlying integer type for MetaObjectType.
      using MetaObjectTypeIdx = std::underlying_type_t<MetaObjectType>;
      // Compile-time table.
      constexpr
        std::array<bool, kNumMetaObjectTypes> kIsDefaultImplementation =
        [] <MetaObjectTypeIdx... meta_object_type_idx>
        (std::integer_sequence<MetaObjectTypeIdx, meta_object_type_idx...> seq)
        consteval
      {
        return std::array<bool, sizeof...(meta_object_type_idx)>
        { std::is_base_of_v<DefaultObjectDetailsDataReaderBase,
                            JsonReader<ObjectDetailsData<static_cast<MetaObjectType>(meta_object_type_idx)>>>... };
      }(std::make_integer_sequence<MetaObjectTypeIdx, kNumMetaObjectTypes>{});
      return !kIsDefaultImplementation.at(static_cast<MetaObjectTypeIdx>(meta_object_type));
    }

    // Utility wrapper around fromJson<ObjectDetailsData<T>>(), which returns the result
    // as ObjectDetailsDataVariant.
    template<MetaObjectType T>
    ObjectDetailsDataVariant readObjectDetailsDataAsVariant(const Json::Value& value)
    {
      if constexpr (isImplementedObjectDetailsDataReader(T))
      {
        return fromJson<ObjectDetailsData<T>>(value);
      }
      else
      {
        throw std::runtime_error("NotImplemented.");
      }
    }

    // Reads ObjectDetailsData for the specified MetaObjectType.
    // \param value - input JSON value.
    // \param meta_object_type - MetaObjectType of the object.
    // \return the deserialized data as ObjectDetailsDataVariant.
    ObjectDetailsDataVariant readObjectDetailsDataVariant(const Json::Value& value, MetaObjectType meta_object_type)
    {
      // The underlying integer type for MetaObjectType.
      using MetaObjectTypeIdx = std::underlying_type_t<MetaObjectType>;
      // Type of a pointer to a function that takes std::istream& and returns ObjectDetails::Data.
      using ReadObjectDetailsDataPtr = ObjectDetailsDataVariant(*)(const Json::Value&);
      // Generate (at compile time) an array of function pointers for each instantiation of
      // readObjectDetailsDataAsVariant() ordered by MetaObjectType.
      constexpr
        std::array<ReadObjectDetailsDataPtr, kNumMetaObjectTypes> kObjectDetailsDataReaders =
        [] <MetaObjectTypeIdx... meta_object_type_idx>
        (std::integer_sequence<MetaObjectTypeIdx, meta_object_type_idx...> seq)
        consteval
      {
        return std::array<ReadObjectDetailsDataPtr, sizeof...(meta_object_type_idx)>
        { &readObjectDetailsDataAsVariant<static_cast<MetaObjectType>(meta_object_type_idx)>... };
      }(std::make_integer_sequence<MetaObjectTypeIdx, kNumMetaObjectTypes>{});
      // Invoke a function from the generated array.
      return kObjectDetailsDataReaders.at(static_cast<MetaObjectTypeIdx>(meta_object_type))(value);
    }

    // TODO: return as ObjectDetails, not as std::optional.
    std::optional<ObjectDetails> tryReadObjectDetails(
      const Json::Value& value,
      const std::vector<ObjectAttributes>& objects_attributes)
    {
      using Fields = FieldNames<ObjectDetails>;
      ObjectDetails object_details;
      readField(object_details.x, value, Fields::kX);
      readField(object_details.y, value, Fields::kY);
      readField(object_details.z, value, Fields::kZ);
      readField(object_details.kind, value, Fields::kKind);
      readField(object_details.unknown, value, Fields::kUnknown);

      const ObjectAttributes& object_attributes = objects_attributes.at(object_details.kind);
      const h3m::MetaObjectType meta_object_type = getMetaObjectType(object_attributes.object_class);

      // TODO: remove.
      if (!isImplementedObjectDetailsDataReader(meta_object_type))
      {
        return std::nullopt;
      }
      if (meta_object_type != h3m::MetaObjectType::GENERIC_NO_PROPERTIES)
      {
        const Json::Value* details_json = value.find(Fields::kDetails.data(),
                                                     Fields::kDetails.data() + Fields::kDetails.size());
        if (!details_json)
        {
          throw MissingJsonFieldError(Fields::kDetails);
        }
        object_details.details = readObjectDetailsDataVariant(*details_json, meta_object_type);
      }
      return object_details;
    }

    void readObjectsDetails(std::vector<ObjectDetails>& objects_details,
                                   const Json::Value& value,
                                   const std::vector<ObjectAttributes>& objects_attributes)
    {
      if (!value.isArray())
      {
        throw std::runtime_error("readH3mJson(): expected array, got " + value.toStyledString());
      }
      const std::size_t num_elements = value.size();
      objects_details.reserve(objects_details.size() + num_elements);
      for (std::size_t i = 0; i < num_elements; ++i)
      {
        const Json::Value& object_details_json = value[static_cast<Json::ArrayIndex>(i)];
        std::optional<ObjectDetails> object_details = tryReadObjectDetails(object_details_json, objects_attributes);
        if (object_details)
        {
          objects_details.push_back(std::move(*object_details));
        }
      }
    }
  }

  template<>
  struct JsonReader<Map>
  {
    Map operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<Map>;

      Map map;
      readField(map.format, value, Fields::kFormat);
      readField(map.basic_info, value, Fields::kBasicInfo);
      readField(map.players, value, Fields::kPlayers);
      readField(map.additional_info, value, Fields::kAdditionalInfo);
      readField(map.tiles, value, Fields::kTiles);
      readField(map.objects_attributes, value, Fields::kObjectsAttributes);
      {
        const Json::Value* objects_details_json =
          value.find(Fields::kObjectsDetails.data(), Fields::kObjectsDetails.data() + Fields::kObjectsDetails.size());
        if (!objects_details_json)
        {
          throw MissingJsonFieldError(Fields::kObjectsDetails);
        }
        readObjectsDetails(map.objects_details, *objects_details_json, map.objects_attributes);
      }
      readField(map.global_events, value, Fields::kGlobalEvents);
      readField(map.padding, value, Fields::kPadding);
      return map;
    }
  };

  Map readH3mJson(std::istream& stream)
  {
    Json::Value root;
    {
      Json::CharReaderBuilder builder;
      builder["collectComments"] = false;
      Json::String errs;
      if (!parseFromStream(builder, stream, &root, &errs))
      {
        throw std::runtime_error("readH3mJson(): " + errs);
      }
    }
    return fromJson<Map>(root);
  }
}
