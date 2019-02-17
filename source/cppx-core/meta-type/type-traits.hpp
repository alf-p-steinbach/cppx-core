#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/core-language/signed-sizes.hpp>     // cppx::Size
#include <cppx-core/meta-template/Type_list_.hpp>       // cppx::(contains_type_, Type_list_)

#include <iterator>         // std::iterator_traits
#include <type_traits>      // std::(is_base_of_v, is_class_v, is_integral_v, is_unsigned_v, is_same_v, *)

namespace cppx
{
    using Char_variant_types            = Type_list_<unsigned char, signed char>;
    using Byte_char_types               = Type_list_<char, unsigned char, signed char>;

    using Cpp03_char_literal_types              = Type_list_<char, wchar_t>;
    using Char_literal_types_introduced_in_11   = Type_list_<char16_t, char32_t>;
    using Cpp11_char_literal_types              = Joined_<
        Cpp03_char_literal_types,
        Char_literal_types_introduced_in_11
        >;

    //Char_types_introduced_in_20 = Type_list_<char8_t>;
    //using Cpp20_char_literal_types          = Joined_<Cpp11_char_literal_types, Char_literal_types_introduced_in_20>;

    template< class Char >
    constexpr bool is_a_cpp03_char_type_    = contains_type_<Char, Cpp03_char_literal_types>;

    template< class Char >
    constexpr bool is_a_cpp11_char_type_    = contains_type_<Char, Cpp11_char_literal_types>;

    template< class Char >
    constexpr bool is_a_char_type_          = is_a_cpp11_char_type_<Char>;  // Until C++20, maybe beyond.

    template< class Char >
    constexpr bool is_a_char_variant_type_  = contains_type_<Char, Char_variant_types>;

    template< class Char >
    constexpr bool is_a_byte_char_type_     = contains_type_<Char, Byte_char_types>;

    //----------------------------------------------------------------------------------------------

    template< class Iterator >
    using Item_for_iterator_            = typename std::iterator_traits<Iterator>::value_type;

    template< class Collection >
    using Item_for_collection_          = typename Collection::value_type;

    template< class Raw_array >
    using Item_for_array                = std::remove_extent_t<Raw_array>;

    //----------------------------------------------------------------------------------------------

    template< class Base, class Derived >
    constexpr bool is_base_and_derived_ = std::is_base_of_v<Base, Derived>;

    template< class T, class U >
    constexpr bool is_same_type_        = std::is_same_v<T, U>;

    template< class T, class U >
    constexpr bool is_a_                = is_same_type_<T, U> or is_base_and_derived_<T, U>;

    //----------------------------------------------------------------------------------------------

    template< class T >
    constexpr bool is_const_            = std::is_const_v<T>;

    template< class T >
    constexpr bool is_class_            = std::is_class_v<T>;

    template< class T >
    constexpr bool is_fixed_point_      = false;

    template< class T >
    constexpr bool is_floating_point_   = std::is_floating_point_v<T>;

    template< class T >
    constexpr bool is_integral_         = std::is_integral_v<T>;

    template< class Int >
    constexpr bool is_signed_           = std::is_signed_v<Int>;

    template< class Int >
    constexpr bool is_unsigned_         = std::is_unsigned_v<Int>;

}  // namespace cppx

constexpr bool gah = cppx::is_same_type_<bool, char>;
