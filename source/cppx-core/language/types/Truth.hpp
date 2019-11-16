#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
/// \file
/// \brief
/// \make_name_ref{cppx,Truth}
/// is a drop-in replacement for `bool` without implicit conversion from/to types other
/// than `bool`.

#include <cppx-core/language/syntax/macro-use.hpp>              // CPPX_USE_STD
#include <cppx-core/language/tmp/Enable_if_.hpp>                // cppx::Enable_if_

#include <type_traits>      // std::is_same_v

namespace cppx
{
    CPPX_USE_STD( enable_if_t, is_same_v );

    /// \brief A drop-in replacement for `bool` without implicit conversion from/to types
    /// other than `bool`.
    ///
    /// Implicit conversions to and from `bool` type are a common cause of
    /// undesired overload resolution. `Truth` only converts implicitly to and from
    /// `bool`. It's mostly a drop-in replacement for `bool` because you can use `Truth`
    /// values directly as conditions in `if` and loop statements, and in boolean
    /// operator expressions.
    ///
    /// “Mostly”: as of C++17 `Truth`, like any other user-defined class type, can't be
    /// used as template value parameter type, but this may change with C++20.
    ///
    /// Unplanned positive effect: indexing of a `std::vector<Truth>` produces a reference
    /// to a `Truth` item, which you can take the address of, rather than the proxy object
    /// that you usually get with a `std::vector<bool>`. The proxy objects of the latter
    /// allows it to store just 1 bit per item, at a cost that includes marginally reduced
    /// efficiency and high inconvenience. That cost is avoided with `Truth` as item type.

    template< class T >
    static constexpr bool is_bool_ = std::is_same_v<T, bool>;

    template< class Truth_class >
    struct Truth_values_
    {
        static const Truth_class yes;
        static const Truth_class no;
    };

    class Truth:
        public Truth_values_<Truth>
    {
        bool        m_value;

    public:
        /// \brief Implicit conversion to `bool` (only).
        ///
        /// Implicit conversion to `bool` because that's needed for template args.
        /// Restricted via SFINAE because overload resolution, want predictability.
        template<
            class Result,
            class = Enable_if_<is_bool_<Result>>
            >
        constexpr operator Result() const noexcept { return m_value; }

        /// \brief Construction from `bool` (only).
        ///
        /// Construction SFINAE-restricted to `bool` argument.
        template<
            class Arg,
            class = Enable_if_<is_bool_<Arg>>
            >
        constexpr Truth( const Arg value ) noexcept: m_value( value ) {}
    };

    template< class Truth_class >
    const Truth_class Truth_values_<Truth_class>::yes   = true;

    template< class Truth_class >
    const Truth_class Truth_values_<Truth_class>::no    = false;
    
    constexpr auto is_true( const Truth value )
        -> Truth
    { return value; }

    constexpr auto is_false( const Truth value )
        -> Truth
    { return not value; }

    constexpr auto operator!=( const Truth lhs, const Truth rhs )
        -> bool
    { return !!lhs != !!rhs; }

    constexpr auto operator<=( const Truth lhs, const Truth rhs )
        -> bool
    { return !!lhs <= !!rhs; }

    constexpr auto operator<( const Truth lhs, const Truth rhs )
        -> bool
    { return !!lhs < !!rhs; }

    constexpr auto operator==( const Truth lhs, const Truth rhs )
        -> bool
    { return !!lhs == !!rhs; }

    constexpr auto operator>=( const Truth lhs, const Truth rhs )
        -> bool
    { return !!lhs >= !!rhs; }

    constexpr auto operator>( const Truth lhs, const Truth rhs )
        -> bool
    { return !!lhs > !!rhs; }

}  // namespace cppx
