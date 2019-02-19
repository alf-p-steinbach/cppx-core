#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/syntax/macro-use.hpp>          // CPPX_USE_STD

#include <exception>            // std::(rethrow_exception)
#include <stdexcept>            // std::(exception_ptr)

namespace cppx
{
    CPPX_USE_STD( exception_ptr, rethrow_exception );

    namespace impl
    {
        inline auto stored_ptr()
            -> exception_ptr&
        {
            static exception_ptr the_stored_ptr;
            return the_stored_ptr;
        }
    }

    inline auto replace_stored_x_with( const exception_ptr& p )
        -> exception_ptr
    {
        exception_ptr original = impl::stored_ptr();
        impl::stored_ptr() = p;
        return original;
    }

    inline void clear_stored_x()
    {
        impl::stored_ptr() = nullptr;
    }

    inline void rethrow_any_stored_x()
    {
        const exception_ptr p = impl::stored_ptr();
        if( p != nullptr )
        {
            impl::stored_ptr() = nullptr;
            rethrow_exception( p );
        }
    }
}  // namespace cppx
