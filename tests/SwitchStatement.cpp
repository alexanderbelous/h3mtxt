#include <h3mtxt/Map/Utils/SwitchStatement.h>

#include <string_view>

namespace
{
  enum class AnimalType
  {
    Cat  = 0,
    Bird = 1,
    Dog  = 2
  };

  template<AnimalType T>
  constexpr std::string_view getAnimalSound() noexcept;

  template<>
  constexpr std::string_view getAnimalSound<AnimalType::Cat>() noexcept
  {
    return "Meow";
  }

  template<>
  constexpr std::string_view getAnimalSound<AnimalType::Bird>() noexcept
  {
    return "Chirp";
  }

  template<>
  constexpr std::string_view getAnimalSound<AnimalType::Dog>() noexcept
  {
    return "Woof";
  }

  // Convert the function template getAnimalSound<T>() into an alias template,
  // so that it can be passed as a template template parameter to generateSwitchStatement().
  template<AnimalType T>
  using GetAnimalSoundTemplateAlias = SwitchStatement_NS::StaticConstant<&getAnimalSound<T>>;

  constexpr std::string_view getAnimalSoundDynamic(AnimalType animal_type) noexcept
  {
    // Generate a switch statement.
    // This is equivalent to
    //     switch (animal_type)
    //     {
    //     case AnimalType::Cat:
    //       return getAnimalSound<AnimalType::Cat>();
    //     case AnimalType::Bird:
    //       return getAnimalSound<AnimalType::Bird>();
    //     case AnimalType::Dog:
    //       return getAnimalSound<AnimalType::Dog>();
    //     default:
    //       throw std::out_of_range();
    //     }
    constexpr auto switch_statement =
      SwitchStatement_NS::generateSwitchStatement<AnimalType, 3, GetAnimalSoundTemplateAlias>();
    return switch_statement(animal_type);
  }

  static_assert(getAnimalSoundDynamic(AnimalType::Cat) == "Meow");
  static_assert(getAnimalSoundDynamic(AnimalType::Bird) == "Chirp");
  static_assert(getAnimalSoundDynamic(AnimalType::Dog) == "Woof");
}
