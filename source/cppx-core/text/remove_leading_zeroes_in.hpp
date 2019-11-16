#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/syntax/macro-use.hpp>
#include <cppx-core/language/syntax/type-builders.hpp>      // cppx::P_
#include <cppx-core/language/system/size-types.hpp>         // cppx::Size

#include <algorithm>        // std::copy
#include <string>           // std::string

namespace cppx {
    CPPX_USE_STD( copy, string );

    inline auto remove_leading_zeroes_in( const P_<char> p_start, const P_<char> p_beyond )
        -> Size         // New string length
    {
        if( p_start == p_beyond ) {
            return 0;
        }

        char* p = p_start;
        while( p != p_beyond and *p == '0' ) {
            ++p;
        }
        if( p == p_beyond ) {
            return 1;
        }
        if( p != p_start ) {
            copy( p, p_beyond, p_start );
        }
        return p_beyond - p;
    }

    inline void remove_leading_zeroes_in( string& s )
    {
        const Size new_length = remove_leading_zeroes_in(
            s.data(),
            s.data() + s.size()
        );
        s.resize( new_length );
    }

}  // namespace cppx
