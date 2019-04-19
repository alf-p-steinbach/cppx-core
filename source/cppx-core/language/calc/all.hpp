#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/calc/floating-point-operations.hpp>
#include <cppx-core/language/calc/integer-operations.hpp>
#include <cppx-core/language/calc/named-numbers.hpp>
#include <cppx-core/language/calc/number-type-properties.hpp>
#include <cppx-core/language/calc/std-calc.hpp>

namespace cppx
{
    /// \brief Functions and constants typically available on a scientific calculator,
    /// but somehow missing from the standard library.
    ///
    /// Integer functions `is_even`, `is_odd`, `intdiv`, `intmod`,
    /// `intsquare`, `intcube`, `intmin`, `intmax`, and floating point `intpow`,
    /// `squared` and `cubed` functions. Floating point functions `has_nan`_,
    /// `has_nan`, `has_infinity_`, `has_infinity`. Floating point constants  `e`,
    /// `log2e`, `log10e`, `ln2`, `ln10`, `pi`, `inv_sqrt_pi`, `sqrt2`, `inv_sqrt2`,
    /// `nan_`, `nan`, `infinity_`, `infinity`.
    namespace calc {}

    /// \brief Concise, clear and consistent number type properties.
    ///
    /// `is_ieee_754_`, `largest_`,
    /// `smallest_`, `max_`, `min_`, `max_e_`, `min_e_`, `n_digits_`,
    /// `radix_` and `epsilon_`.
    namespace number_properties {}
}
