#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/calc/integer-operations.hpp>       // cppx::is_odd
#include <cppx-core/language/syntax/macro-use.hpp>

namespace cppx::math
{
    /// @cond DOXY_SHOW_IMPL_DETAILS
    namespace impl
    {
        template< class Number = double >
        inline auto intpow( const Number base, const int exponent )
            -> Number
        {
            Number result = 1;
            Number weight = base;
            for( int n = exponent; n != 0; weight *= weight )
            {
                if( is_odd( n ) )
                {
                    result *= weight;
                    --n;
                }
                else
                {
                    n /= 2;
                }
            }
            return result;
        }
    }  // namespace impl
    /// @endcond

    template< class Number = double >
    inline auto intpow( const Number base, const int exponent )
        -> Number
    {
        return (0?0
            : exponent == 0?        1.0
            : exponent < 0?         1.0/impl::intpow( base, -exponent )
            :                       impl::intpow( base, exponent )
            );
    }

    template< class Number = double >
    inline auto squared( const Number x )
        -> Number
    { return x*x; }

    template< class Number = double >
    inline auto cubed( const Number x )
        -> Number
    { return x*x*x; }

}  // namespace cppx::math

namespace cppx
{
    CPPX_USE_FROM_NAMESPACE( cppx::math,
        intpow, squared
        );
}  // namespace cppx
