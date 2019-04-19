#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
/// \file
/// \brief Concise, clear & consistent notation for number type properties.
///
/// The `std::numeric_limits` facility is very verbose, has in part cryptic names, is
/// non-systematic in what values mean for different kinds of types, and needlessly
/// (and bafflingly for one without historical knowledge of C++) expresses integral
/// values as values but floating point type values as functions that must be invoked.
/// Hence this more consistent and easy-to-use, but limited, facility.

#include <cppx-core/language/syntax/macro-use.hpp>          // CPPX_USE_STD, CPPX_USE_CPPX
#include <cppx-core/language/types/Truth.hpp>               // cppx::Truth

#include <limits>       // std::numeric_limits
#include <type_traits>  // std::is_integral_v

namespace cppx
{
    /// @cond DOXY_SHOW_IMPL_DETAILS
    CPPX_USE_STD( conditional_t );

    namespace impl
    {
        template< class T > using Nl_ = std::numeric_limits<T>;

        template< class T, bool is_integral_type = std::is_integral_v<T> >  // "bool" until C++20.
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

            static constexpr Truth  is_ieee_754_    = Nl_<T>::is_iec559;
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

    /// \brief The property values as members of class, so that they can be inherited in.
    template< class Type >
    struct Number_properties_;
    
    /// @cond DOXY_SHOW_IMPL_DETAILS
        template< class Type >
        struct Number_properties_: impl::Number_properties_<Type> {};
    /// @endcond

    /// \hideinitializer
    /// \brief FP only. Whether the implementation claims to conform to the IEEE 754 standard.
    ///    
    /// `is_ieee_754_<T>` is an alias for `std::numeric_limits<T>::is_iec559`.
    ///
    /// IEC 559 is just the European name of the IEEE 754 floating point standard.
    ///
    /// Note that (at the writing of this documentation) both the Visual C++ and g++
    /// compilers report IEEE 754 conformance when their fast-math options are used, which
    /// in particular causes incorrect NaN-checking, i.e. non-conformance.
    template< class T > constexpr Truth is_ieee_754_    = Number_properties_<T>::is_ieee_754;

    /// \hideinitializer
    /// \brief The largest representable-as-positive absolute value of the type.
    ///
    /// `largest_<T>` is an alias for `std::numeric_limits<T>::max()`.
    template< class T > constexpr T     largest_        = Number_properties_<T>::largest;

    /// \hideinitializer
    /// \brief The smallest non-zero absolute value of the type.
    ///
    /// For integer `T` this is just 1, and for floating point `T` the expression
    /// `smallest_<T>` is an alias for `std::numeric_limits<T>::min()`.
    template< class T > constexpr T     smallest_       = Number_properties_<T>::smallest;

    /// \hideinitializer
    /// \brief The largest positive value of the type.
    ///
    /// The expression `max_<T>` is an alias for `largest_<T>`.
    template< class T > constexpr T     max_            = Number_properties_<T>::max;

    /// \hideinitializer
    /// \brief The largest negative value of the type.
    ///
    /// For integer `T` the expression `min_<T>` is an alias for
    /// `std::numeric_limits<T>::min()`, which is usually/always `-largest_<T> - 1`.
    ///
    /// For floating point `T` the expression `min_<T>` is an alias for `-largest_<T>`.
    template< class T > constexpr T     min_            = Number_properties_<T>::min;

    /// \hideinitializer
    /// \brief FP only. E-notation maximum (largest positive) exponent value.
    ///
    /// The expression `max_e_<T>` is an alias for
    /// `std::numeric_limits<T>::max_exponent10`.
    template< class T > constexpr int   max_e_          = Number_properties_<T>::max_e;

    /// \hideinitializer
    /// \brief FP only. E-notation minimum (largest negative) exponent value.
    ///
    /// The expression `min_e_<T>` is an alias for
    /// `std::numeric_limits<T>::min_exponent10`.
    template< class T > constexpr int   min_e_          = Number_properties_<T>::min_e;

    /// \hideinitializer
    /// \brief Number of decimal digits that guaranteed can be represented.
    ///
    /// The expression `n_digits_<T>` is an alias for `std::numeric_limits<T>::digits10`.
    template< class T > constexpr int   n_digits_       = Number_properties_<T>::n_digits;

     /// \hideinitializer
    /// \brief FP only. The numeral system base of the floating point representation,
    /// 2 or 10.
    ///
    /// The C++ standard requires integer types to be represented in binary, as either
    /// two's complement (now universal), ones' complement or sign and magnitude. From
    /// C++20 it will require two's complement form. However, it allows a floating point
    /// type to use a representation in some other numeral system such as 10, decimal.
    ///
    /// The expression `radix_<T>` is an alias for `std::numeric_limits<T>::radix`.
    template< class T > constexpr int   radix_          = Number_properties_<T>::radix;

    /// \hideinitializer
    /// \brief The difference between 1 and the least floating point value greater than 1.
    ///
    /// The expression `epsilon_<T>` is an alias for `std::numeric_limits<T>::epsilon()`.
    template< class T > constexpr T     epsilon_        = Number_properties_<T>::epsilon;

    namespace number_properties
    {
        CPPX_USE_CPPX(
            is_ieee_754_, largest_, smallest_, max_, min_, max_e_, min_e_, n_digits_,
            radix_, epsilon_
            );
    }  // namespace number_properties

}  // namespace cppx
