#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/syntax/macro-use.hpp>          // CPPX_USE_STD
#include <cppx-core/language/types/signed-size-types.hpp>   // cppx::(Index, Size)

namespace cppx
{
    CPPX_USE_STD( forward );

    template< class Func, class... Args >
    void repeat( const Size n, const Func& f, Args&&... args )
    {
        for( Index i = 0; i < n; ++i )
        {
            f( forward<Args>( args )... );
        }
    }
}
