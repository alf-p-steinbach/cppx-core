#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
/// \file
/// \brief Just includes `<c/math.hpp>`, `<complex>` and `<numeric>`.
///
/// In addition to the contents
/// of `<cmath>` and `<math.h>`, the first header brings in  `int` overloads of `abs` and `div` 
/// from `<cstdlib>` and `<stdlib.h>`. By default the Posix standard's `M_PI` etc. are defined.

#include <c/math.hpp>       // <math.h>, <cmath>, <c/stdlib.hpp>
#include <complex>          // std::complex
#include <numeric>          // std::accumulate etc.
// Intentionally not including <valarray> because it doesn't follow std library conventions.
