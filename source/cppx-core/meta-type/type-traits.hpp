#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core-language/syntax/type-builders.hpp>          // cppx::Raw_array_of_
#include <cppx-core-language/syntax/macro-use.hpp>              // CPPX_USE_STD
#include <cppx-core-language/tmp/type-traits.hpp>               // cppx::(is_signed_ ...)
#include <cppx-core-language/types/Truth.hpp>                   // cppx::Truth
#include <cppx-core-language/tmp/type-mutators.hpp>             // cppx::(Unref_ ...)
#include <cppx-core/meta-template/Type_list_.hpp>               // cppx::(contains_type_, Joined_, Type_list_)

#include <iterator>         // std::begin
#include <utility>          // std::declval

namespace cppx
{
    CPPX_USE_STD( begin, declval );

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
    constexpr Truth is_a_cpp03_char_type_   = contains_type_<Char, Cpp03_char_literal_types>;

    template< class Char >
    constexpr Truth is_a_cpp11_char_type_   = contains_type_<Char, Cpp11_char_literal_types>;

    template< class Char >
    constexpr Truth is_a_char_type_         = is_a_cpp11_char_type_<Char>;  // Until C++20, maybe beyond.

    template< class Char >
    constexpr Truth is_a_char_variant_type_ = contains_type_<Char, Char_variant_types>;

    template< class Char >
    constexpr Truth is_a_byte_char_type_    = contains_type_<Char, Byte_char_types>;

    //----------------------------------------------------------------------------------------------

    template< class Iterator >
    using Item_for_iterator_            = typename std::iterator_traits<Iterator>::value_type;

    template< class Collection >
    using Item_for_collection_          = Unref_<decltype( *begin( declval<Collection&>() ) )>;

    template< class Collection >
    using Iterator_for_                 = decltype( begin( declval<Collection&>() ) );

    //template< class Raw_array >
    //using Item_for_array                = std::remove_extent_t<Raw_array>;

    ////----------------------------------------------------------------------------------------------

    //template< class Collection >
    //struct Item_type_of_T_
    //{ using T = typename Collection::value_type; };

    //template< class Item, size_t n >
    //struct Item_type_of_T_<Raw_array_of_<n, Item>>
    //{ using T = Item; };                    // std::remove_extent_t.

    //template< class Collection >
    //using Item_type_of_ = typename Item_type_of_T_<Collection>::T;

}  // namespace cppx
