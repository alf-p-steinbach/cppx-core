#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
/// \file
/// \brief
/// \make_name_ref{cppx,Unptr_},
/// \make_name_ref{cppx,Unref_},
/// \make_name_ref{cppx,Signed_},
/// \make_name_ref{cppx,Unsigned_},
/// \make_name_ref{cppx,Const_} and
/// \make_name_ref{cppx,Unconst_}.

/// The template aliases defined in this file generally do not support template argument
/// deduction. In contrast, the basic type assemblers like
/// \make_name_ref{cppx,P_} and
/// \make_name_ref{cppx,R_}, do. Those basic type assemblers are also offered by this
/// header, via a convenience include of
/// `<cppx-core/language/syntax/type-builders.hpp> `.

#include <cppx-core/language/syntax/type-builders.hpp>      // Convenience include.

#include <type_traits>      // std::(add_*, make_*, remove_*)

namespace cppx
{
    /// \brief Reduces a type `T*` to just `T`.
    template< class Some_pointer_type >
    using Unptr_        = std::remove_pointer_t<Some_pointer_type>;

    /// \brief Reduces a type `T&` or `T&&` to just `T`.
    template< class Some_reference_type >
    using Unref_        = std::remove_reference_t<Some_reference_type>;

    /// \brief For an integer type, produces the corresponding signed type.
    template< class Integer >
    using Signed_       = std::make_signed_t< Integer >;

    /// \brief For an integer type, produces the corresponding unsigned type.
    template< class Integer >
    using Unsigned_     = std::make_unsigned_t< Integer >;

    /// \brief For a type `T` produces `const T`.
    template< class Some_type >
    using Const_        = std::add_const_t< Some_type >;

    /// \brief For a type `const T` produces plain `T`.
    template< class Some_type >
    using Unconst_      = std::remove_const_t< Some_type >;

    namespace type_mutators
    {
        CPPX_USE_CPPX(
            Unptr_, Unref_, Signed_, Unsigned_, Const_, Unconst_
        );
    }  // namespace type_mutators
}  // namespace cppx
