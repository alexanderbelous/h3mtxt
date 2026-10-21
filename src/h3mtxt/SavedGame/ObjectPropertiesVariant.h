#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Constants/ObjectClass.h>
#include <h3mtxt/SavedGame/Constants/ObjectPropertiesType.h>
#include <h3mtxt/SavedGame/ObjectProperties.h>

#include <algorithm>
#include <array>
#include <cstddef>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace h3svg
{
  // Stores ObjectClass and the "simple" properties of an Adventure Map object.
  class ObjectPropertiesVariant
  {
  public:
    // Same as ObjectPropertiesVariant(ObjectClass::NONE, ObjectProperties<ObjectPropertiesType::None>{}).
    inline ObjectPropertiesVariant() noexcept;

    // Constructs an ObjectPropertiesVariant storing the properties of the given Adventure Map object.
    // \param object_class - ObjectClass of the Adventure Map object.
    // \param properties - properties of the Adventure Map object.
    // \throw std::logic_error if getObjectPropertiesType(object_class) != T.
    template<ObjectPropertiesType T>
    constexpr ObjectPropertiesVariant(ObjectClass object_class, const ObjectProperties<T>& properties);

    inline ObjectPropertiesVariant(const ObjectPropertiesVariant& other) noexcept;

    inline ObjectPropertiesVariant(ObjectPropertiesVariant&& other) noexcept;

    inline ObjectPropertiesVariant& operator=(const ObjectPropertiesVariant& other) noexcept;

    inline ObjectPropertiesVariant& operator=(ObjectPropertiesVariant&& other) noexcept;

    inline ~ObjectPropertiesVariant();

    inline bool operator==(const ObjectPropertiesVariant& other) const noexcept;

    // \return ObjectClass of the stored alternative.
    constexpr ObjectClass objectClass() const noexcept;

    // \return getObjectPropertiesType(this->objectClass()).
    constexpr ObjectPropertiesType type() const noexcept;

    // \return a mutable reference to the stored ObjectProperties<T>.
    // \throw std::logic_error if this->type() != T.
    template<ObjectPropertiesType T>
    constexpr ObjectProperties<T>& get();

    // \return a const reference to the stored ObjectProperties<T>.
    // \throw std::logic_error if this->type() != T.
    template<ObjectPropertiesType T>
    constexpr const ObjectProperties<T>& get() const;

    // \return a pointer to the stored ObjectProperties<T>,
    //         or nullptr if this->type() != T.
    template<ObjectPropertiesType T>
    constexpr ObjectProperties<T>* get_if() noexcept;

    // \return a pointer to the stored ObjectProperties<T>,
    //         or nullptr if this->type() != T.
    template<ObjectPropertiesType T>
    constexpr const ObjectProperties<T>* get_if() const noexcept;

    template<ObjectClass T>
    void set(const ObjectProperties<getObjectPropertiesType(T)>& properties);

    template<class Visitor>
    constexpr void visit(Visitor&& visitor);

    template<class Visitor>
    constexpr void visit(Visitor&& visitor) const;

  private:
    // max(sizeof(ObjectProperties<T>)) over all valid T.
    static constexpr std::size_t kMaxObjectPropertiesSizeof =
      [] <std::size_t... Indices> (std::index_sequence<Indices...>) consteval
      {
        return std::max({ sizeof(ObjectProperties<static_cast<ObjectPropertiesType>(Indices)>)... });
      }(std::make_index_sequence<kNumObjectPropertiesTypes>{});\

    // max(alignof(ObjectProperties<T>)) over all valid T.
    static constexpr std::size_t kMaxObjectPropertiesAlignof =
      [] <std::size_t... Indices> (std::index_sequence<Indices...>) consteval
      {
        return std::max({ alignof(ObjectProperties<static_cast<ObjectPropertiesType>(Indices)>)... });
      }(std::make_index_sequence<kNumObjectPropertiesTypes>{});

    template<ObjectPropertiesType T>
    constexpr ObjectProperties<T>& getUnsafe();

    template<ObjectPropertiesType T>
    constexpr const ObjectProperties<T>& getUnsafe() const;

    inline void destructCurrentAlternative();

    inline void copyConstructAlternative(const ObjectPropertiesVariant& other) noexcept;

    template<class Self, class Visitor>
    class VisitorHelper;

    // ObjectClass of the stored alternative.
    ObjectClass object_class_ = ObjectClass::NONE;

    // Type-unsafe union of ObjectProperties<T> over all valid T.
    alignas(kMaxObjectPropertiesAlignof) unsigned char data_[kMaxObjectPropertiesSizeof] {};
  };

  ObjectPropertiesVariant::ObjectPropertiesVariant() noexcept
  {
    // Construct ObjectProperties<ObjectPropertiesType::None>.
    new(&data_) ObjectProperties<ObjectPropertiesType::None>();
  }

  template<ObjectPropertiesType T>
  constexpr ObjectPropertiesVariant::ObjectPropertiesVariant(ObjectClass object_class, const ObjectProperties<T>& properties):
    object_class_{ object_class }
  {
    if (getObjectPropertiesType(object_class) != T)
    {
      throw std::logic_error("ObjectPropertiesVariant::ObjectPropertiesVariant(): invalid ObjectPropertiesType "
                             "for the input ObjectClass.");
    }
    new(&data_) ObjectProperties<T>(properties);
  }

  ObjectPropertiesVariant::ObjectPropertiesVariant(const ObjectPropertiesVariant& other) noexcept
  {
    copyConstructAlternative(other);
  }

  ObjectPropertiesVariant::ObjectPropertiesVariant(ObjectPropertiesVariant&& other) noexcept:
    ObjectPropertiesVariant(other) // Delegate to copy constructor.
  {}

  ObjectPropertiesVariant& ObjectPropertiesVariant::operator=(const ObjectPropertiesVariant& other) noexcept
  {
    if (type() == other.type())
    {
      visit([&other] <ObjectPropertiesType T> (ObjectProperties<T>& properties)
            {
              properties = other.getUnsafe<T>();
            });
      object_class_ = other.object_class_;
    }
    else
    {
      destructCurrentAlternative();
      copyConstructAlternative(other);
    }
    return *this;
  }

  ObjectPropertiesVariant& ObjectPropertiesVariant::operator=(ObjectPropertiesVariant&& other) noexcept
  {
    // Delegate to copy assignment.
    return (*this) = other;
  }

  ObjectPropertiesVariant::~ObjectPropertiesVariant()
  {
    destructCurrentAlternative();
  }

  bool ObjectPropertiesVariant::operator==(const ObjectPropertiesVariant& other) const noexcept
  {
    if (object_class_ != other.object_class_)
    {
      return false;
    }
    bool are_equal = false;
    visit([&other, &are_equal] <ObjectPropertiesType T> (const ObjectProperties<T>& properties)
          {
            are_equal = (properties == other.getUnsafe<T>());
          });
    return are_equal;
  }

  constexpr ObjectClass ObjectPropertiesVariant::objectClass() const noexcept
  {
    return object_class_;
  }

  constexpr ObjectPropertiesType ObjectPropertiesVariant::type() const noexcept
  {
    return getObjectPropertiesType(objectClass());
  }

  template<ObjectPropertiesType T>
  constexpr ObjectProperties<T>& ObjectPropertiesVariant::get()
  {
    return const_cast<ObjectProperties<T>&>(std::as_const(*this).get<T>());
  }

  // \return a const reference to the stored ObjectProperties<T>.
  // \throw std::bad_variant_access if this->type() != T.
  template<ObjectPropertiesType T>
  constexpr const ObjectProperties<T>& ObjectPropertiesVariant::get() const
  {
    if (type() != T)
    {
      throw std::logic_error("h3svg::ObjectPropertiesVariant::get(): ObjectPropertiesType doesn't match "
                             "the type of the stored alternative.");
    }
    return getUnsafe<T>();
  }

  template<ObjectPropertiesType T>
  constexpr ObjectProperties<T>* ObjectPropertiesVariant::get_if() noexcept
  {
    return const_cast<ObjectProperties<T>*>(std::as_const(*this).get_if<T>());
  }

  // \return a pointer to the stored ObjectProperties<T>,
  //         or nullptr if this->type() != T.
  template<ObjectPropertiesType T>
  constexpr const ObjectProperties<T>* ObjectPropertiesVariant::get_if() const noexcept
  {
    return (type() == T) ? &(getUnsafe<T>()) : nullptr;
  }

  template<ObjectPropertiesType T>
  constexpr ObjectProperties<T>& ObjectPropertiesVariant::getUnsafe()
  {
    return const_cast<ObjectProperties<T>&>(std::as_const(*this).getUnsafe<T>());
  }

  template<ObjectPropertiesType T>
  constexpr const ObjectProperties<T>& ObjectPropertiesVariant::getUnsafe() const
  {
    return *static_cast<const ObjectProperties<T>*>(static_cast<const void*>(&data_));
  }

  void ObjectPropertiesVariant::destructCurrentAlternative()
  {
    // Explicitly call the destructor of the current alternative.
    visit([] <ObjectPropertiesType T> (ObjectProperties<T>& properties)
          {
            properties.~ObjectProperties();
          });
  }

  void ObjectPropertiesVariant::copyConstructAlternative(const ObjectPropertiesVariant& other) noexcept
  {
    void* const address = static_cast<void*>(&data_);
    other.visit([address] <ObjectPropertiesType T> (const ObjectProperties<T>& properties)
                {
                  new(address) ObjectProperties<T>(properties);
                });
    object_class_ = other.object_class_;
  }

  template<class Self, class Visitor>
  class ObjectPropertiesVariant::VisitorHelper
  {
  public:
    static_assert(std::is_same_v<std::remove_cvref_t<Self>, ObjectPropertiesVariant>,
                  "Self must be the same as ObjectPropertiesVariant or a cvref-qualified version thereof.");

    constexpr void operator()(Self&& self, Visitor&& visitor) const;

  private:
    using FunctionPtr = void(*)(Self&&, Visitor&&);

    template<ObjectPropertiesType T>
    static constexpr void visitAlternative(Self&& self, Visitor&& visitor)
    {
      std::forward<Visitor>(visitor)(std::forward<Self>(self).getUnsafe<T>());
    }

    static constexpr std::array<FunctionPtr, kNumObjectPropertiesTypes> kTable =
      [] <std::size_t... Indices> (std::index_sequence<Indices...>) consteval
      {
        return std::array<FunctionPtr, kNumObjectPropertiesTypes>{
          &visitAlternative<static_cast<ObjectPropertiesType>(Indices)>...
        };
      }(std::make_index_sequence<kNumObjectPropertiesTypes>{});
  };

  template<class Self, class Visitor>
  constexpr void ObjectPropertiesVariant::VisitorHelper<Self, Visitor>::operator()(Self&& self,
                                                                                   Visitor&& visitor) const
  {
    const std::size_t function_idx = static_cast<std::size_t>(self.type());
    return kTable[function_idx](std::forward<Self>(self), std::forward<Visitor>(visitor));
  }

  template<class Visitor>
  constexpr void ObjectPropertiesVariant::visit(Visitor&& visitor)
  {
    VisitorHelper<ObjectPropertiesVariant&, Visitor>{}(*this, std::forward<Visitor>(visitor));
  }

  template<class Visitor>
  constexpr void ObjectPropertiesVariant::visit(Visitor&& visitor) const
  {
    VisitorHelper<const ObjectPropertiesVariant&, Visitor>{}(*this, std::forward<Visitor>(visitor));
  }
}
