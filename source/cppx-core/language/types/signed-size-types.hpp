#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <c/stddef.hpp>     // size_t
#include <type_traits>      // std::make_signed_t

namespace cppx
{
    inline namespace size_types
    {
        using Size                  = std::make_signed_t< size_t >;     // ~ptrdiff_t
        using Index                 = Size;
        using Unsigned_size         = size_t;
        using Unsigned_index        = Unsigned_size;
    }

}  // namespace cppx
