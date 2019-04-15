#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/syntax/macro-use.hpp>          // CPPX_USE_...

#include <chrono>           // std::chrono::*
#include <ratio>            // std::(milli, micro, nano)
#include <type_traits>      // std::conditional

namespace cppx
{
    CPPX_USE_STD_NAMESPACE_NAMES( chrono );
    CPPX_USE_STD(
        conditional_t,
        milli, micro, nano
        );

    using Timer_clock = conditional_t<chrono::high_resolution_clock::is_steady,
        chrono::high_resolution_clock,
        chrono::steady_clock
        >;

    template< class Rep, class Period >
    inline auto as_seconds( const chrono::duration<Rep, Period> duration_value )
        -> double
    { return chrono::duration<double>( duration_value ).count(); }

    template< class Rep, class Period >
    inline auto as_milliseconds( const chrono::duration<Rep, Period> duration_value )
        -> double
    { return chrono::duration<double, milli>( duration_value ).count(); }

    template< class Rep, class Period >
    inline auto as_microseconds( const chrono::duration<Rep, Period> duration_value )
        -> double
    { return chrono::duration<double, micro>( duration_value ).count(); }

    template< class Rep, class Period >
    inline auto as_nanoseconds( const chrono::duration<Rep, Period> duration_value )
        -> double
    { return chrono::duration<double, nano>( duration_value ).count(); }

}  // namespace cppx
