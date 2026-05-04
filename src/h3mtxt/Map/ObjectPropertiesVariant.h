#pragma once

#include <h3mtxt/Map/ObjectProperties.h>
#include <h3mtxt/Map/Utils/EnumSequence.h>

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <variant>

namespace h3m
{
  namespace Detail_NS
  {
    // Wrapper for std::unique_ptr<T> with deep copy support.
    template<class T>
    class NonInlineAlternative
    {
      template<class... Types>
      struct TypeList;

    public:
      // Constructs an object of type T from the given arguments.
      //
      // This function does not participate in the overload resolution if Args... is a parameter pack
      // containing a single type that is the same as NonInlineAlternative<T> or a cvref-qualified version thereof.
      //
      // \param args - arguments to construct the object of type T from.
      template<class... Args,
               class Enable = std::enable_if_t<!std::is_same_v<TypeList<std::remove_cvref_t<Args>...>,
                                                               TypeList<NonInlineAlternative<T>>>>>
      NonInlineAlternative(Args&&... args);

      NonInlineAlternative(const NonInlineAlternative& other);

      NonInlineAlternative(NonInlineAlternative&& other) noexcept = default;

      NonInlineAlternative& operator=(const NonInlineAlternative& other);

      NonInlineAlternative& operator=(NonInlineAlternative&& other) noexcept = default;

      ~NonInlineAlternative() = default;

      bool operator==(const NonInlineAlternative& other) const;

      T& value() &;

      T&& value() &&;

      const T& value() const&;
      
    private:
      T& valueImpl() const;

      std::unique_ptr<T> impl_;
    };
  }

  // Eldritch abomination capable of storing any ObjectProperties<T>.
  //
  // This is similar to std::variant, but, unlike std::variant, it stores the data on heap
  // for large ObjectProperties<T>. The reason for this is that ObjectProperties<T> can be quite
  // large for some T, but for most objects on the Adeventure Map it will be small. std::variant
  // is memory-inefficient in this scenario.
  //
  // In order to reduce the number of dynamic memory allocations, this class stores sufficiently small
  // ObjectProperties<T> in the inline storage (similar to Small String Optimization).
  class ObjectPropertiesVariant
  {
    // The size of the inline storage (in bytes).
    static constexpr std::size_t kInlineStorageSize = sizeof(void*);

    // \return true if ObjectProperties<T> should be inline, false otherwise.
    template<ObjectPropertiesType T>
    static consteval bool isInline()
    {
      return (sizeof(ObjectProperties<T>) <= kInlineStorageSize) &&
             (alignof(ObjectProperties<T>) <= alignof(void*));
    }

    // Alias template storing ObjectProperties<T> for types that should be inline,
    // NonInlineAlternative<ObjectProperties<T>> otherwise.
    template<ObjectPropertiesType T>
    using AlternativeImpl = std::conditional_t<isInline<T>(), ObjectProperties<T>,
                                                              Detail_NS::NonInlineAlternative<ObjectProperties<T>>>;

    template<class T>
    struct Traits;

    template<ObjectPropertiesType... object_properties_types>
    struct Traits<EnumSequence<ObjectPropertiesType, object_properties_types...>>
    {
      using type = std::variant<AlternativeImpl<object_properties_types>...>;
    };

    // Type of the underlying std::variant.
    using Impl = typename Traits<MakeEnumSequence<ObjectPropertiesType, kNumObjectPropertiesTypes>>::type;

  public:
    // This is so that we can guarantee that ObjectPropertiesVariant never stores a null pointer
    // for some non-inline alternative.
    static_assert(isInline<ObjectPropertiesType::NONE>(),
                  "ObjectProperties<ObjectPropertiesType::NONE> must be stored in the inline storage.");
    static_assert(std::is_nothrow_default_constructible_v<ObjectProperties<ObjectPropertiesType::NONE>>,
                  "ObjectProperties<ObjectPropertiesType::NONE> must have a non-throwing default constructor");

    // Constructs ObjectPropertiesVariant holding ObjectProperties<ObjectPropertiesType::NONE>.
    constexpr ObjectPropertiesVariant() noexcept;

    // Constructs ObjectPropertiesVariant holding the specified ObjectProperties.
    template<ObjectPropertiesType T>
    ObjectPropertiesVariant(const ObjectProperties<T>& data);

    // Constructs ObjectPropertiesVariant holding the specified ObjectProperties.
    template<ObjectPropertiesType T>
    ObjectPropertiesVariant(ObjectProperties<T>&& data);

    // Copy constructor.
    ObjectPropertiesVariant(const ObjectPropertiesVariant& other) = default;

    // Move constructor.
    // \param other - ObjectPropertiesVariant to move from.
    // After this call @other will be in a valid state holding NONE.
    inline ObjectPropertiesVariant(ObjectPropertiesVariant&& other)
      noexcept(std::is_nothrow_move_constructible_v<Impl>);

    // Copy assignment operator.
    ObjectPropertiesVariant& operator=(const ObjectPropertiesVariant& other) = default;

    // Move assignment operator.
    inline ObjectPropertiesVariant& operator=(ObjectPropertiesVariant&& other)
      noexcept(std::is_nothrow_move_assignable_v<Impl>);

    ~ObjectPropertiesVariant() = default;

    bool operator==(const ObjectPropertiesVariant&) const noexcept = default;

    // \return ObjectPropertiesType of the stored ObjectProperties.
    constexpr ObjectPropertiesType type() const noexcept;

    // \return a reference to the stored ObjectProperties<T>.
    // \throw std::bad_variant_access if type() != T.
    template<ObjectPropertiesType T>
    ObjectProperties<T>& get();

    // \return a const reference to the stored ObjectProperties<T>.
    // \throw std::bad_variant_access if type() != T.
    template<ObjectPropertiesType T>
    const ObjectProperties<T>& get() const;

    // \return a pointer to the stored ObjectProperties<T>,
    //         or nullptr if type() != T.
    template<ObjectPropertiesType T>
    ObjectProperties<T>* get_if() noexcept;

    // \return a pointer to the stored ObjectProperties<T>,
    //         or nullptr if type() != T.
    template<ObjectPropertiesType T>
    const ObjectProperties<T>* get_if() const noexcept;

    // Invokes the given visitor with the current alternative (mutable).
    // \param visitor - visitor to invoke. Visitor must be a Callable
    //        that can be called with any ObjectProperties<T>&.
    template<class Visitor>
    void visit(Visitor&& visitor);

    // Invokes the given visitor with the current alternative (non-mutable).
    // \param visitor - visitor to invoke. Visitor must be a Callable
    //        that can be called with any const ObjectProperties<T>&.
    template<class Visitor>
    void visit(Visitor&& visitor) const;

  private:
    // Function object that invokes Visitor with the input argument,
    // "dereferencing" it if it's an instantiation of NonInlineAlternative.
    template<class Visitor>
    class VisitorHelper;

    Impl impl_;
  };

  namespace Detail_NS
  {
    // Stores true if T is a specialization of NonInlineAlternative, false otherwise.
    template<class T>
    struct IsNonInlineAlternative : std::false_type {};

    template<class T>
    struct IsNonInlineAlternative<NonInlineAlternative<T>> : std::true_type {};

    template<class T>
    template<class... Args, class Enable>
    NonInlineAlternative<T>::NonInlineAlternative(Args&&... args) :
      impl_(std::make_unique<T>(std::forward<Args>(args)...))
    {}

    template<class T>
    NonInlineAlternative<T>::NonInlineAlternative(const NonInlineAlternative& other):
      NonInlineAlternative(other.value())
    {}

    template<class T>
    NonInlineAlternative<T>& NonInlineAlternative<T>::operator=(const NonInlineAlternative& other)
    {
      value() = other.value();
      return *this;
    }

    template<class T>
    bool NonInlineAlternative<T>::operator==(const NonInlineAlternative& other) const
    {
      // If comparing with self or if both are in a moved-from state -> return true.
      if (impl_.get() == other.impl_.get())
      {
        return true;
      }
      // Otherwise, if neither is in a moved-from state -> compare the stored values.
      if (impl_ != nullptr && other.impl_ != nullptr)
      {
        return *impl_ == *other.impl_;
      }
      // Otherwise (if either *this or @other is in a moved-from state) -> return false.
      return false;
    }

    template<class T>
    T& NonInlineAlternative<T>::value() &
    {
      return valueImpl();
    }

    template<class T>
    T&& NonInlineAlternative<T>::value() &&
    {
      return std::move(valueImpl());
    }

    template<class T>
    const T& NonInlineAlternative<T>::value() const&
    {
      return valueImpl();
    }

    template<class T>
    T& NonInlineAlternative<T>::valueImpl() const
    {
      if (!impl_)
      {
        throw std::logic_error("NonInlineAlternative: attempting to access a moved-from object.");
      }
      return *impl_;
    }
  }

  constexpr ObjectPropertiesVariant::ObjectPropertiesVariant() noexcept :
    impl_(std::in_place_type<ObjectProperties<ObjectPropertiesType::NONE>>)
  {
    // FYI: this doesn't need to be explictly defined if
    // ObjectProperties<ObjectPropertiesType::NONE> is the 0th alternative. However, the explicit
    // definition makes ObjectPropertiesVariant agnostic to the order of constants in ObjectPropertiesType,
    // which is safer.
  }

  template<ObjectPropertiesType T>
  ObjectPropertiesVariant::ObjectPropertiesVariant(const ObjectProperties<T>& data):
    impl_(std::in_place_type<AlternativeImpl<T>>, data)
  {
  }

  template<ObjectPropertiesType T>
  ObjectPropertiesVariant::ObjectPropertiesVariant(ObjectProperties<T>&& data) :
    impl_(std::in_place_type<AlternativeImpl<T>>, std::move(data))
  {
  }

  ObjectPropertiesVariant::ObjectPropertiesVariant(ObjectPropertiesVariant&& other)
    noexcept(std::is_nothrow_move_constructible_v<Impl>) :
    impl_(std::move(other.impl_))
  {
    // Assign NONE to @other to ensure that it doesn't store a null unique_ptr.
    other.impl_.emplace<ObjectProperties<ObjectPropertiesType::NONE>>();
  }

  ObjectPropertiesVariant& ObjectPropertiesVariant::operator=(ObjectPropertiesVariant&& other)
    noexcept(std::is_nothrow_move_assignable_v<Impl>)
  {
    if (this != &other)
    {
      impl_ = std::move(other.impl_);
      // Assign NONE to @other to ensure that it doesn't store a null unique_ptr.
      other.impl_.emplace<ObjectProperties<ObjectPropertiesType::NONE>>();
    }
    return *this;
  }

  constexpr ObjectPropertiesType ObjectPropertiesVariant::type() const noexcept
  {
    return static_cast<ObjectPropertiesType>(impl_.index());
  }

  template<ObjectPropertiesType T>
  ObjectProperties<T>& ObjectPropertiesVariant::get()
  {
    return const_cast<ObjectProperties<T>&>(std::as_const(*this).get<T>());
  }

  template<ObjectPropertiesType T>
  const ObjectProperties<T>& ObjectPropertiesVariant::get() const
  {
    if (const ObjectProperties<T>* data_ptr = get_if<T>())
    {
      return *data_ptr;
    }
    throw std::bad_variant_access();
  }

  template<ObjectPropertiesType T>
  ObjectProperties<T>* ObjectPropertiesVariant::get_if() noexcept
  {
    return const_cast<ObjectProperties<T>*>(std::as_const(*this).get_if<T>());
  }

  template<ObjectPropertiesType T>
  const ObjectProperties<T>* ObjectPropertiesVariant::get_if() const noexcept
  {
    const AlternativeImpl<T>* alt = std::get_if<static_cast<std::size_t>(T)>(&impl_);
    if constexpr (std::is_same_v<AlternativeImpl<T>, ObjectProperties<T>>)
    {
      return alt;
    }
    else
    {
      static_assert(std::is_same_v<AlternativeImpl<T>, Detail_NS::NonInlineAlternative<ObjectProperties<T>>>);
      if (!alt)
      {
        return nullptr;
      }
      return std::addressof(alt->value());
    }
  }

  template<class Visitor>
  class ObjectPropertiesVariant::VisitorHelper
  {
  public:
    explicit constexpr VisitorHelper(Visitor&& visitor) noexcept :
      visitor_(std::forward<Visitor>(visitor))
    {}

    template<class T>
    decltype(auto) operator()(T&& value) const
    {
      if constexpr (Detail_NS::IsNonInlineAlternative<std::remove_cvref_t<T>>::value)
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
  void ObjectPropertiesVariant::visit(Visitor&& visitor)
  {
    std::visit(VisitorHelper<Visitor>{ std::forward<Visitor>(visitor) }, impl_);
  }

  template<class Visitor>
  void ObjectPropertiesVariant::visit(Visitor&& visitor) const
  {
    std::visit(VisitorHelper<Visitor>{ std::forward<Visitor>(visitor) }, impl_);
  }
}
