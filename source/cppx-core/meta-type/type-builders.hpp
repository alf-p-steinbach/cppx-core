#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/core-language/syntax/macro_use.hpp>     // CPPX_USE_STD

#include <c/stddef.hpp>     // size_t
#include <array>            // std::array
#include <type_traits>      // std::(add_*, make_*, remove_*, conditional_t)

namespace cppx
{
    namespace impl
    {
        CPPX_USE_STD(
            add_const_t, array, make_signed_t, make_unsigned_t, remove_const_t,
            remove_pointer_t, remove_reference_t
            );

        //----------------------------------------------- Maybe all that's needed:

        template< bool condition, class A, class B >
        using Choose_ = std::conditional_t<condition, A, B>;

        template< class Some_type >
        using Type_ = Some_type;


        //----------------------------------------------- Specialized basic builders:
        //
        // Note: the more safe standard library generators such as std::add_pointer_t
        // are not used for commented builders because they would prevent template
        // argument deduction. The basic builders defined here are just names for the
        // conventional way of writing e.g. formal argument types. As such they carry
        // the same risk of unintended type result as the raw operator notation does,
        // but they have advantages such as supporting uniform `const` first notation,
        // more generally read-left-to-right declarations, and being self-descriptive.

        template< class Some_type >
        using Ref_ = Some_type&;                // std::add_lvalue_reference_t<Some_type>;

        template< class Some_reference_type >
        using Unref_ = std::remove_reference_t<Some_reference_type>;
        
        template< class Some_type >
        using Ptr_ = Some_type*;                // std::add_pointer_t<Some_type>;

        template< class Some_pointer_type >
        using Unptr_ = std::remove_pointer_t<Some_pointer_type>;

        template< class Integer >
        using Signed_ = std::make_signed_t< Integer >;

        template< class Integer >
        using Unsigned_ = std::make_unsigned_t< Integer >;

        template< class Some_type >
        using Const_ = std::add_const_t< Some_type >;

        template< class Some_type >
        using Unconst_ = std::remove_const_t< Some_type >;


        //----------------------------------------------- Special kinds of reference:
        //
        // As of C++17 there's no way to /enforce/ the meanings implied by these names,
        // so these are currently purely comment-like templates. At one time I thought
        // they were a good idea. As of late 2018 I've changed that opinion, but maybe
        // with some later version of C++ they can be defined with constraints and still
        // support template argument deduction.

        template< class Some_type >
        using Intended_temp_ref_ = Some_type&&;         // std::add_rvalue_reference_t<Some_type>;

        template< class Some_type >
        using Intended_forwarding_ref_ = Some_type&&;   // Also known as a “universal reference”.


        //----------------------------------------------- Arrays + general item type:

        template< size_t n, class Item >
        using Array_of_ = array<Item, n>;

        template< class Item >
        using Raw_array_ = Item[];

        template< size_t n, class Item >
        using Raw_array_of_ = Item[n];

        template< class Collection >
        struct Item_type_of_T_
        { using T = typename Collection::value_type; };

        template< class Item, size_t n >
        struct Item_type_of_T_<Raw_array_of_<n, Item>>
        { using T = Item; };                    // std::remove_extent_t.

        template< class Collection >
        using Item_type_of_ = typename Item_type_of_T_<Collection>::T;
    }  // namespace impl

    inline namespace type_builders {
        template< class Type >  using P_    = impl::Ptr_<Type>;     // Type*
        template< class Type >  using R_    = impl::Ref_<Type>;     // Type&
        using
            impl::Type_,
            impl::Unref_, impl::Unptr_,
            impl::Signed_, impl::Unsigned_, impl::Const_, impl::Unconst_,
            impl::Intended_temp_ref_, impl::Intended_forwarding_ref_,
            impl::Array_of_, impl::Raw_array_, impl::Raw_array_of_,
            impl::Item_type_of_;
    }  // inline namespace type_builders

    namespace all_type_builders
    {
        using namespace type_builders;
        using impl::Ref_, impl::Ptr_;
    }   // namespace all_type_builders
}  // namespace cppx
