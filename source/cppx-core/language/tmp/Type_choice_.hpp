#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
/// \file
/// \brief
/// \make_name_ref{cppx,Type_choice_}

#include <type_traits>      // std::conditional_t

namespace cppx
{
    /// \brief Reduces to type `A` if the condition holds, otherwise type `B`.
    /// \param condition    A compile time boolean expression.
    /// \param A            Result type when the condition holds.
    /// \param B            Result type when the condition doesn't hold.
    template< bool condition, class A, class B >        // "bool" until C++20
    using Type_choice_  = std::conditional_t<condition, A, B>;

}  // namespace cppx
