#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
/// \file
/// \brief `is_base_and_derived_`, `is_same_type_`, `is_a_`, `is_const_`, `is_class_`,
/// `is_fixed_point_`, `is_floating_point_`, `is_integral_`, `is_integral_`,
/// `is_unsigned_`
///
/// `is_based_and_derived_` clarifies the roles of the template arguments, which are not
/// apparent in `std::is_base_of_t`. `is_based_and_derived_` is also more clean regarded
/// as English. `is_class` doesn't care if you feed it a reference, it then reports about
/// the referent type. The numerical category type traits provide a common notation for
/// checking also for fixed point type, which is an omission in the standard library. But
/// in general it's all mainly about readability and convenience.

#include <cppx-core/language/types/Truth.hpp>                   // cppx::Truth

#include <iterator>         // std::iterator_traits
#include <type_traits>      // std::(is_*, std::remove_reference_t)

namespace cppx
{
    //----------------------------------------------------------------------------------------------

    template< class Base, class Derived >
    constexpr Truth is_base_and_derived_    = std::is_base_of_v<Base, Derived>;

    template< class T, class U >
    constexpr Truth is_same_type_           = std::is_same_v<T, U>;

    template< class T, class U >
    constexpr Truth is_a_                   = is_same_type_<T, U> or is_base_and_derived_<T, U>;

    //----------------------------------------------------------------------------------------------

    template< class T >
    constexpr Truth is_const_           = std::is_const_v<std::remove_reference_t<T>>;

    template< class T >
    constexpr Truth is_class_           = std::is_class_v<T>;

    template< class T >
    constexpr Truth is_fixed_point_     = false;

    template< class T >
    constexpr Truth is_floating_point_  = std::is_floating_point_v<T>;

    template< class T >
    constexpr Truth is_integral_        = std::is_integral_v<T>;

    template< class Int >
    constexpr Truth is_signed_          = std::is_signed_v<Int>;

    template< class Int >
    constexpr Truth is_unsigned_        = std::is_unsigned_v<Int>;

}  // namespace cppx
