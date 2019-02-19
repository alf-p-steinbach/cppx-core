#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/syntax/macro-use.hpp>

#include <c/math.hpp>
#include <limits>           // std::numeric_limits

namespace cppx
{
    // Using explicit `using` declarations instead of `inline` namespace to avoid ambiguity
    // elsewhere for the nested namespace name `impl`.
    namespace math
    {
        using std::numeric_limits;

#ifdef M_PI
        const auto e                = M_E;              // e              2.71828182845904523536
        const auto log2e            = M_LOG2E;          // log2(e)        1.44269504088896340736
        const auto log10e           = M_LOG10E;         // log10(e)       0.434294481903251827651
        const auto ln2              = M_LN2;            // ln(2)          0.693147180559945309417
        const auto ln10             = M_LN10;           // ln(10)         2.30258509299404568402
        const auto pi               = M_PI;             // pi             3.14159265358979323846
                                                        // pi/2 M_PI_2    1.57079632679489661923
                                                        // pi/4 M_PI_4    0.785398163397448309616
                                                        // 1/pi M_1_PI    0.318309886183790671538
                                                        // 2/pi M_2_PI    0.636619772367581343076
        const auto inv_sqrt_pi      = M_2_SQRTPI/2;     // 2/sqrt(pi)     1.12837916709551257390
        const auto sqrt2            = M_SQRT2;          // sqrt(2)        1.41421356237309504880
        const auto inv_sqrt2        = M_SQRT1_2;        // 1/sqrt(2)      0.707106781186547524401
#else
        const auto e                = 2.71828182845904523536;
        const auto log2e            = 1.44269504088896340736;
        const auto log10e           = 0.434294481903251827651;
        const auto ln2              = 0.693147180559945309417;
        const auto ln10             = 2.30258509299404568402;
        const auto pi               = 3.14159265358979323846;
                                      //1.57079632679489661923
                                      //0.785398163397448309616
                                      //0.318309886183790671538
                                      //0.636619772367581343076
        const auto inv_sqrt_pi      = 1.12837916709551257390;
        const auto sqrt2            = 1.41421356237309504880;
        const auto inv_sqrt2        = 0.707106781186547524401;
#endif
        constexpr bool has_nan      = numeric_limits<double>::has_quiet_NaN;

        template< class Number = double >
        constexpr auto nan()
            -> double
        { return numeric_limits<Number>::quiet_NaN(); }

        constexpr bool has_infinity = numeric_limits<double>::has_infinity;

        template< class Number = double >
        constexpr auto infinity()
            -> double
        { return numeric_limits<Number>::infinity(); }

    }  // namespace math

    CPPX_USE_FROM_NAMESPACE( math,
        e, log2e, log10e, ln2, ln10, pi, inv_sqrt_pi, sqrt2, inv_sqrt2,
        has_nan, nan, has_infinity, infinity
        );

}  // namespace cppx
