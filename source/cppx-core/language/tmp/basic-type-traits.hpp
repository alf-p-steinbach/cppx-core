#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/types/Truth.hpp>                   // cppx::Truth

#include <iterator>         // std::iterator_traits
#include <type_traits>      // std::(is_base_of_v, is_class_v, is_integral_v, is_unsigned_v, is_same_v, *)

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
    constexpr Truth is_const_           = std::is_const_v<T>;

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
