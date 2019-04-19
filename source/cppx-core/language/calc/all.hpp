#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/calc/floating-point-operations.hpp>
#include <cppx-core/language/calc/integer-operations.hpp>
#include <cppx-core/language/calc/number-type-properties.hpp>
#include <cppx-core/language/calc/std-calc.hpp>

namespace cppx
{
    /// \brief Provides integer `is_even`, `is_odd`, `intdiv`, `intmod`,
    /// `intsquare`, `intcube`, `intmin`, `intmax`, and floating point `intpow`,
    /// `squared` and `cubed` functions.
    namespace calc {}

    /// \brief Provides number type properties `is_ieee_754_`, `largest_`,
    /// `smallest_`, `max_`, `min_`, `max_e_`, `min_e_`, `n_digits_`,
    /// `radix_` and `epsilon_`.
    namespace number_properties {}
}
