#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
/// \file
/// \brief
/// \make_name_ref{cppx,Truth}
/// is a drop-in replacement for `bool` without implicit conversion to types other than
/// `bool`.

#include <cppx-core/language/syntax/macro-use.hpp>          // CPPX_USE_STD
#include <cppx-core/language/tmp/basic-Enable_if_.hpp>      // cppx::Enable_if_

#include <type_traits>      // std::is_same_v

namespace cppx
{
    CPPX_USE_STD( enable_if_t, is_same_v );

    /// \brief A drop-in replacement for `bool` without implicit conversion to types
    /// other than `bool`.
    ///
    /// “Replacement”: e.g. indexing of a `std::vector<Truth>` will in practice produce
    /// a reference to a `Truth` item, which you can take the address of, rather than the
    /// proxy object you usually get with a `std::vector<bool>`. The proxy objects of the
    /// latter allows it to store just 1 bit per item, at a cost that includes marginally
    /// reduced efficiency and high inconvenience. That cost is avoided with `Truth`.
    ///
    /// “Drop-in”: Implicit conversions to and from `bool` type are a common cause of
    /// undesired overload resolution. `Truth` avoids this by only converting to and from
    /// `bool`. It's mostly a drop-in replacement for `bool` because you can use `Truth`
    /// values directly as `if` and loop conditions, and in boolean expressions.
    ///
    /// “Mostly”: as of C++17 `Truth`, like any other user-defined class type, can't be
    /// used as template value parameter type, but this may change with C++20.
    class Truth
    {
        bool        m_value;

        template< class T >
        static constexpr bool is_bool_ = std::is_same_v<T, bool>;

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
}  // namespace cppx
