#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
/// \file
/// \brief Just includes `<c/math.hpp>`, `<complex>` and `<numeric>`, where the first
/// header provides Posix’ `M_PI` macro, as well as `M_E`, `M_LOG2E`, `M_LOG10E`, `M_LN2`,
/// `M_LN10`, `M_PI_2`, `M_PI_4`, `M_1_PI`,  `M_2_PI`, `M_2_SQRTPI`, `M_SQRT2` and
/// `M_SQRT1_2`.
///
/// In addition to the contents
/// of `<cmath>` and `<math.h>`, the  `<c/math.hpp>` header brings in `int` overloads
/// of `abs` and `div` from `<cstdlib>` and `<stdlib.h>`.

#include <c/math.hpp>       // <math.h>, <cmath>, <c/stdlib.hpp>
#include <complex>          // std::complex
#include <numeric>          // std::accumulate etc.
// Intentionally not including <valarray> because it doesn't follow std library conventions.
