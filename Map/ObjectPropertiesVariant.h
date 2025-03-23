#pragma once

#include <h3mtxt/Map/ObjectProperties.h>
#include <h3mtxt/Map/Utils/EnumSequence.h>

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <variant>

namespace h3m
{
  namespace Detail_NS
  {
    // The size of the inline storage (in bytes) for ObjectPropertiesVariant.
    inline constexpr std::size_t kInlineStorageSize = sizeof(void*);

    // \return true if ObjectProperties<T> should be inline, false otherwise.
    template<MetaObjectType T>
    consteval bool isInline()
    {
      return (sizeof(ObjectProperties<T>) <= kInlineStorageSize) &&
             (alignof(ObjectProperties<T>) <= alignof(void*));
    }

    template<class T, class... Args>
    struct AreCopyOrMoveConstructorArgs : std::false_type {};

    template<class T, class Arg>
    struct AreCopyOrMoveConstructorArgs<T, Arg> : std::bool_constant<std::is_same_v<T, std::remove_cvref_t<Arg>>> {};

    template<class T>
    class NonInlineAlternative
    {
    public:
      template<class... Args,
               class Enable = std::enable_if_t<!AreCopyOrMoveConstructorArgs<NonInlineAlternative<T>, Args&&...>::value &&
                                               std::is_constructible_v<T, Args&&...>>>
      NonInlineAlternative(Args&&... args):
        impl_(std::make_unique<T>(std::forward<Args>(args)...))
      {}

      NonInlineAlternative(const NonInlineAlternative& other):
        impl_(std::make_unique<T>(other.value()))
      {}

      NonInlineAlternative(NonInlineAlternative&& other) noexcept = default;

      NonInlineAlternative& operator=(const NonInlineAlternative& other)
      {
        value() = other.value();
        return *this;
      }

      NonInlineAlternative& operator=(NonInlineAlternative&& other) noexcept = default;

      ~NonInlineAlternative() = default;

      T& value() &
      {
        return valueImpl();
      }

      T&& value() &&
      {
        return std::move(valueImpl());
      }

      const T& value() const&
      {
        return valueImpl();
      }
      
    private:
      T& valueImpl() const
      {
        if (!impl_)
        {
          throw std::logic_error("NonInlineAlternative: attempting to access a moved-from object.");
        }
        return *impl_;
      }

      std::unique_ptr<T> impl_;
    };

    // Alias template storing ObjectProperties<T> for types that should be inline,
    // NonInlineAlternative<ObjectProperties> otherwise.
    template<MetaObjectType T>
    using ObjectPropertiesVariantAlternative =
      std::conditional_t<isInline<T>(), ObjectProperties<T>, NonInlineAlternative<ObjectProperties<T>>>;

    template<class Types>
    struct ObjectPropertiesVariantImplTraits;

    template<MetaObjectType... meta_object_types>
    struct ObjectPropertiesVariantImplTraits<EnumSequence<MetaObjectType, meta_object_types...>>
    {
      using type = std::variant<ObjectPropertiesVariantAlternative<meta_object_types>...>;
    };

    using ObjectPropertiesVariantImpl =
      typename ObjectPropertiesVariantImplTraits<MakeEnumSequence<MetaObjectType, kNumMetaObjectTypes>>::type;
  }

  // This is so that we can guarantee that ObjectPropertiesVariant never stores a null pointer
  // for some non-inline alternative.
  static_assert(Detail_NS::isInline<MetaObjectType::GENERIC_NO_PROPERTIES>(),
                "ObjectProperties<MetaObjectType::GENERIC_NO_PROPERTIES> "
                "must be stored in the inline storage.");
  static_assert(std::is_nothrow_default_constructible_v<ObjectProperties<MetaObjectType::GENERIC_NO_PROPERTIES>>,
                "ObjectProperties<MetaObjectType::GENERIC_NO_PROPERTIES> "
                "must have a non-throwing default constructor");

  // Eldritch abomination capable of storing any ObjectProperties<T>.
  //
  // This is similar to std::variant, but unlike std::variant, it stores the data on heap
  // for large ObjectProperties<T>. The reason for this is that ObjectProperties can be quite
  // large for some MetaObjectTypes, but most objects on the map it will be small. std::variant
  // is memory-inefficient in this scenario.
  //
  // In order to reduce the number of dynamic memory allocations, this class stores sufficiently small
  // ObjectProperties<T> in the inline storage (similar to Small String Optimization).
  class ObjectPropertiesVariant
  {
  public:
    // Constructs ObjectPropertiesVariant holding ObjectProperties<MetaObjectType::GENERIC_NO_PROPERTIES>.
    constexpr ObjectPropertiesVariant() noexcept;

    // Constructs ObjectPropertiesVariant holding the specified ObjectProperties.
    template<MetaObjectType T>
    ObjectPropertiesVariant(const ObjectProperties<T>& data);

    // Constructs ObjectPropertiesVariant holding the specified ObjectProperties.
    template<MetaObjectType T>
    ObjectPropertiesVariant(ObjectProperties<T>&& data);

    // Copy constructor.
    ObjectPropertiesVariant(const ObjectPropertiesVariant& other) = default;

    // Move constructor.
    // \param other - ObjectPropertiesVariant to move from.
    // After this call @other will be in a valid state holding GENERIC_NO_PROPERTIES.
    inline ObjectPropertiesVariant(ObjectPropertiesVariant&& other)
      noexcept(std::is_nothrow_move_constructible_v<Detail_NS::ObjectPropertiesVariantImpl>);

    // Copy assignment operator.
    ObjectPropertiesVariant& operator=(const ObjectPropertiesVariant& other) = default;

    // Move assignment operator.
    inline ObjectPropertiesVariant& operator=(ObjectPropertiesVariant&& other)
      noexcept(std::is_nothrow_move_assignable_v<Detail_NS::ObjectPropertiesVariantImpl>);

    ~ObjectPropertiesVariant() = default;

    // \return MetaObjectType of the stored ObjectProperties.
    constexpr MetaObjectType getMetaObjectType() const noexcept;

    // \return a reference to the stored ObjectProperties<T>.
    // \throw std::bad_variant_access if getMetaObjectType() != T.
    template<MetaObjectType T>
    ObjectProperties<T>& get();

    // \return a const reference to the stored ObjectProperties<T>.
    // \throw std::bad_variant_access if getMetaObjectType() != T.
    template<MetaObjectType T>
    const ObjectProperties<T>& get() const;

    // \return a pointer to the stored ObjectProperties<T>,
    //         or nullptr if getMetaObjectType() != T.
    template<MetaObjectType T>
    ObjectProperties<T>* get_if() noexcept;

    // \return a pointer to the stored ObjectProperties<T>,
    //         or nullptr if getMetaObjectType() != T.
    template<MetaObjectType T>
    const ObjectProperties<T>* get_if() const noexcept;

    template<class Visitor>
    void visit(Visitor&& visitor);

    template<class Visitor>
    void visit(Visitor&& visitor) const;

  private:
    template<class Visitor, class Self>
    static void visitImpl(Visitor&& visitor, Self&& self);

    Detail_NS::ObjectPropertiesVariantImpl impl_;
  };

  constexpr ObjectPropertiesVariant::ObjectPropertiesVariant() noexcept:
    impl_(std::in_place_type<ObjectProperties<MetaObjectType::GENERIC_NO_PROPERTIES>>)
  {
  }

  template<MetaObjectType T>
  ObjectPropertiesVariant::ObjectPropertiesVariant(const ObjectProperties<T>& data):
    impl_(std::in_place_type<Detail_NS::ObjectPropertiesVariantAlternative<T>>, data)
  {
  }

  template<MetaObjectType T>
  ObjectPropertiesVariant::ObjectPropertiesVariant(ObjectProperties<T>&& data) :
    impl_(std::in_place_type<Detail_NS::ObjectPropertiesVariantAlternative<T>>, std::move(data))
  {
  }

  ObjectPropertiesVariant::ObjectPropertiesVariant(ObjectPropertiesVariant&& other)
    noexcept(std::is_nothrow_move_constructible_v<Detail_NS::ObjectPropertiesVariantImpl>) :
    impl_(std::move(other.impl_))
  {
    // Assign GENERIC_NO_PROPERTIES to @other to ensure that it doesn't store a null unique_ptr.
    other.impl_.emplace<ObjectProperties<MetaObjectType::GENERIC_NO_PROPERTIES>>();
  }

  ObjectPropertiesVariant& ObjectPropertiesVariant::operator=(ObjectPropertiesVariant&& other)
    noexcept(std::is_nothrow_move_assignable_v<Detail_NS::ObjectPropertiesVariantImpl>)
  {
    if (this != &other)
    {
      impl_ = std::move(other.impl_);
      // Assign GENERIC_NO_PROPERTIES to @other to ensure that it doesn't store a null unique_ptr.
      other.impl_.emplace<ObjectProperties<MetaObjectType::GENERIC_NO_PROPERTIES>>();
    }
    return *this;
  }

  constexpr MetaObjectType ObjectPropertiesVariant::getMetaObjectType() const noexcept
  {
    return static_cast<MetaObjectType>(impl_.index());
  }

  template<MetaObjectType T>
  ObjectProperties<T>& ObjectPropertiesVariant::get()
  {
    return const_cast<ObjectProperties<T>&>(std::as_const(*this).get<T>());
  }

  template<MetaObjectType T>
  const ObjectProperties<T>& ObjectPropertiesVariant::get() const
  {
    if (const ObjectProperties<T>* data_ptr = get_if<T>())
    {
      return *data_ptr;
    }
    throw std::bad_variant_access();
  }

  template<MetaObjectType T>
  ObjectProperties<T>* ObjectPropertiesVariant::get_if() noexcept
  {
    return const_cast<ObjectProperties<T>*>(std::as_const(*this).get_if<T>());
  }

  template<MetaObjectType T>
  const ObjectProperties<T>* ObjectPropertiesVariant::get_if() const noexcept
  {
    const Detail_NS::ObjectPropertiesVariantAlternative<T>* alt = std::get_if<static_cast<std::size_t>(T)>(&impl_);
    if constexpr (Detail_NS::isInline<T>())
    {
      return alt;
    }
    else
    {
      if (!alt)
      {
        return nullptr;
      }
      return std::addressof(alt->value());
    }
  }

  template<class Visitor>
  void ObjectPropertiesVariant::visit(Visitor&& visitor)
  {
    visitImpl(std::forward<Visitor>(visitor), *this);
  }

  template<class Visitor>
  void ObjectPropertiesVariant::visit(Visitor&& visitor) const
  {
    visitImpl(std::forward<Visitor>(visitor), *this);
  }

  namespace Detail_NS
  {
    // Stores true if T is a specialization of NonInlineAlternative, false otherwise.
    template<class T>
    struct IsNonInlineAlternative : std::false_type {};

    template<class T>
    struct IsNonInlineAlternative<NonInlineAlternative<T>> : std::true_type {};

    template<class Visitor>
    class VisitorHelper
    {
    public:
      explicit constexpr VisitorHelper(Visitor&& visitor) noexcept:
        visitor_(std::forward<Visitor>(visitor))
      {}

      template<class T>
      decltype(auto) operator()(T&& value)
      {
        if constexpr (IsNonInlineAlternative<std::remove_cvref_t<T>>::value)
        {
          return std::forward<Visitor>(visitor_)(std::forward<T>(value).value());
        }
        else
        {
          return std::forward<Visitor>(visitor_)(std::forward<T>(value));
        }
      }

    private:
      Visitor&& visitor_;
    };

    template<class Visitor>
    constexpr VisitorHelper<Visitor> makeVisitorHelper(Visitor&& visitor) noexcept
    {
      return VisitorHelper<Visitor>(std::forward<Visitor>(visitor));
    }
  }

  template<class Visitor, class Self>
  void ObjectPropertiesVariant::visitImpl(Visitor&& visitor, Self&& self)
  {
    std::visit(Detail_NS::makeVisitorHelper(std::forward<Visitor>(visitor)), std::forward<Self>(self).impl_);
  }
}