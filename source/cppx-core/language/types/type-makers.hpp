#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

// The template aliases defined in this file generally do not support template argument
// deduction. In contrast, the basic type assemblers like P_ and R_, do.

#include <cppx-core/language/syntax/type-assemblers.hpp>

#include <c/stddef.hpp>     // size_t
#include <array>            // std::array
#include <type_traits>      // std::(add_*, make_*, remove_*, conditional_t)

namespace cppx
{
    inline namespace type_makers
    {
        template< bool condition, class A, class B >        // "bool" until C++20
        using Type_choice_  = std::conditional_t<condition, A, B>;

        template< class Some_pointer_type >
        using Unptr_        = std::remove_pointer_t<Some_pointer_type>;

        template< class Some_reference_type >
        using Unref_        = std::remove_reference_t<Some_reference_type>;
        
        template< class Integer >
        using Signed_       = std::make_signed_t< Integer >;

        template< class Integer >
        using Unsigned_     = std::make_unsigned_t< Integer >;

        template< class Some_type >
        using Const_        = std::add_const_t< Some_type >;

        template< class Some_type >
        using Unconst_      = std::remove_const_t< Some_type >;


        //----------------------------------------------- Arrays:

        template< size_t n, class Item >
        using Array_of_                 = std::array<Item, n>;

    }  // inline namespace type_makers

    namespace all_type_builders
    {
        using namespace type_assemblers;
        using namespace ptr_and_ref;
        using namespace type_makers;
    }   // namespace all_type_builders
}  // namespace cppx
