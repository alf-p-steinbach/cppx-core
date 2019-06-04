#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/collections/Pointer_bytes.hpp>          // cppx::Pointer_bytes
#include <cppx-core/language/syntax/macro-use.hpp>          // CPPX_USE_STD
#include <cppx-core/language/syntax/type-assemblers.hpp>    // cppx::P_
#include <cppx-core/text/to-hex-string.hpp>                 // cppx::to_hex

#include <ostream>      // std::basic_ostream

namespace cppx {
    CPPX_USE_STD( basic_ostream, ios_base );

    template< class Char, class Traits >
    inline auto operator<<(basic_ostream<Char, Traits>& stream, const Pointer_bytes& bytes)
        -> basic_ostream<Char, Traits> &
    {
        const bool              uppercase   =
            ((stream.flags() & ios_base::uppercase) != 0);
        const P_<const char>    hex_digits  =
            (uppercase? hex_digits_uppercase : hex_digits_lowercase);

        static const P_<const char> lead_in[2][2] =
        {
            {"d-", "D-"}, {"c-", "C-"}
        };

        stream  << lead_in[bytes.is_code_pointer()][uppercase]
                << to_hex( bytes, hex_digits ).c_str();
        return stream;
    }

}  // namespace cppx
