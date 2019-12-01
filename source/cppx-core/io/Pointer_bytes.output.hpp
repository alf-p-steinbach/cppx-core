#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/collections/Pointer_bytes.hpp>          // cppx::Pointer_bytes
#include <cppx-core-language/syntax/macro-use.hpp>          // CPPX_USE_STD
#include <cppx-core-language/syntax/type-builders.hpp>      // cppx::P_
#include <cppx-core-language/text/to-hex-string.hpp>        // cppx::to_hex

#include <ostream>      // std::basic_ostream

namespace cppx {
    CPPX_USE_STD( basic_ostream, ios_base );

    template< class Char, class Traits >
    inline auto operator<<(basic_ostream<Char, Traits>& stream, const Pointer_bytes& bytes)
        -> basic_ostream<Char, Traits> &
    {
        const bool use_uppercase   = ((stream.flags() & ios_base::uppercase) != 0);
        return stream << spec_of( bytes, use_uppercase );
    }

}  // namespace cppx
