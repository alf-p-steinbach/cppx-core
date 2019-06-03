#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/syntax/macro-use.hpp>          // CPPX_USE_STD
#include <cppx-core/language/system/size-types.hpp>         // cppx::Size

#include <utility>      // std::forward

namespace cppx {
    CPPX_USE_STD( forward );

    template< class F >
    struct Call_operator_for_
    {
        template< class... Args >
        inline decltype(auto) operator()( Args&&... args ) const
        {
            return F::the_function( forward<Args>( args )... );
        }
    };

    template< class F, class... Args >
    constexpr auto buffer_size_for_( Args&&... args )
        -> Size
    { return F::its_buffer_size( forward<Args>( args )... ); }
}  // namespace cppx
