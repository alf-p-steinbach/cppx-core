#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <c/stddef.hpp>         // ptrdiff_t, size_t

namespace cppx
{
    inline namespace size_types
    {
        using Size                  = ptrdiff_t;
        using Index                 = Size;
        using Unsigned_size         = size_t;
        using Unsigned_index        = Unsigned_size;
    }

}  // namespace cppx

// The 0 here is for convenience: change it to 1 to see Intellisense analysis.
#if 0 or defined( CPPX_SIZE_TYPE_CHECKS )
#   include <type_traits>           // std::(is_signed_v, is_unsigned_v, is_same_v)
    namespace cppx{
        static_assert( std::is_signed_v<Size> );
        static_assert( std::is_unsigned_v<Unsigned_size> );
        static_assert( sizeof( Size ) == sizeof( Index ) );
    }
#endif
