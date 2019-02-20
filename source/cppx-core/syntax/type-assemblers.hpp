#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

// This file intentionally does not use the standard library or other cppx-core files.

namespace cppx
{
    inline namespace type_assemblers
    {
        //----------------------------------------------- Specialized basic builders:
        //
        // Note: the more safe standard library generators such as std::add_pointer_t
        // are not used for the commented builders because they would prevent template
        // argument deduction. The basic builders defined here are just names for the
        // conventional way of writing e.g. formal argument types. As such they carry
        // the same risk of unintended type result as the raw operator notation does,
        // but they have advantages such as supporting uniform `const` first notation,
        // more generally read-left-to-right declarations, and being self-descriptive.

        template< class Some_type >
        using Type_ = Some_type;

        template< class Some_type >
        using P_ = Some_type*;                  // std::add_pointer_t<Some_type>;

        template< class Some_type >             // >>> !Preferably use `T&`, not `R_<T>`.
        using R_ = Some_type&;                  // std::add_lvalue_reference_t<Some_type>;

        template< class Item >
        using Raw_array_ = Item[];

        template< size_t n, class Item >
        using Raw_array_of_ = Item[n];
    }  // inline namespace type_assemblers

    namespace ptr_and_ref
    {
        template< class T > using Ptr_ = P_<T>;
        template< class T > using Ref_ = R_<T>;
    }   // namespace all_type_builders
}  // namespace cppx
