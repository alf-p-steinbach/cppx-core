#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

// The `std::numeric_limits` facility is very verbose, has in part cryptic names, is
// non-systematic in what values mean for different kinds of types, and needlessly
// (and bafflingly for one without historical knowledge of C++) expresses integral
// values as values but floating point type values as functions that must be invoked.
// Hence the following more consistent and easy-to-use, but limited, facility.

#include <cppx-core/language/syntax/macro-use.hpp>          // CPPX_USE_STD

#include <limits>       // std::numeric_limits
#include <type_traits>  // std::is_integral_v

namespace cppx
{
    CPPX_USE_STD( conditional_t );

    /// @cond DOXY_SHOW_IMPL_DETAILS
    namespace impl
    {
        template< class T > using Nl_ = std::numeric_limits<T>;

        template< class T, bool is_integral_type = std::is_integral_v<T> >
        struct Number_properties_;

        template< class T >
        struct Number_properties_<T, true>    // Integral types
        {
            static_assert( std::is_integral_v<T> );

            static constexpr T      largest         = Nl_<T>::max();
            static constexpr T      smallest        = 1;                // Smallest non-zero.
            static constexpr T      max             = largest;
            static constexpr T      min             = Nl_<T>::min();    // Usually `-largest_ - 1`.
            static constexpr int    n_digits_       = Nl_<T>::digits10;
        };

        template< class T >
        struct Number_properties_<T, false>    // Floating point and fixed point types
        {
            static_assert( not std::is_integral_v<T> );

            static constexpr bool   is_ieee_754_    = Nl_<T>::is_iec559;
            static constexpr T      largest         = Nl_<T>::max();
            static constexpr T      smallest        = Nl_<T>::min();    // Smallest non-zero.
            static constexpr T      max             = largest;
            static constexpr T      min             = -largest;         // Largest negative.
            static constexpr int    max_e           = Nl_<T>::max_exponent10;
            static constexpr int    min_e           = Nl_<T>::min_exponent10;
            static constexpr int    n_digits        = Nl_<T>::digits10;
            static constexpr int    radix           = Nl_<T>::radix;
            static constexpr T      epsilon         = Nl_<T>::epsilon();
        };

        //TODO: good isnan()
    }  // namespace impl
    /// @endcond

    template< class Type >
    using Number_properties_ = impl::Number_properties_<Type>;

    inline namespace number_properties
    {
        template< class T > constexpr bool  is_ieee_754_    = Number_properties_<T>::is_ieee_754;
        template< class T > constexpr T     largest_        = Number_properties_<T>::largest;
        template< class T > constexpr T     smallest_       = Number_properties_<T>::smallest;
        template< class T > constexpr T     max_            = Number_properties_<T>::max;
        template< class T > constexpr T     min_            = Number_properties_<T>::min;
        template< class T > constexpr int   max_e_          = Number_properties_<T>::max_e;
        template< class T > constexpr int   min_e_          = Number_properties_<T>::min_e;
        template< class T > constexpr int   n_digits_       = Number_properties_<T>::n_digits;
        template< class T > constexpr int   radix_          = Number_properties_<T>::radix;
        template< class T > constexpr T     epsilon_        = Number_properties_<T>::epsilon;
    }  // namespace number_properties

}  // namespace cppx
