#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core-language/syntax/types/type-builders.hpp>    // cppx::Raw_array_of_
#include <cppx-core-language/syntax/declarations.hpp>           // CPPX_USE_STD
#include <cppx-core-language/tmp/type-traits.hpp>               // cppx::(is_signed_ ...)
#include <cppx-core-language/types/Truth.hpp>                   // cppx::Truth
#include <cppx-core-language/tmp/type-modifiers.hpp>            // cppx::(Unref_ ...)
#include <cppx-core/meta-template/Type_list_.hpp>               // cppx::(contains_type_, Joined_, Type_list_)

#include <iterator>         // std::begin
#include <utility>          // std::declval

namespace cppx
{
    CPPX_USE_STD( begin, declval );

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
