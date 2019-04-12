#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/syntax/macro-use.hpp>  // CPPX_USE_STD
#include <cppx-core/language/types/C_str_.hpp>      // cppx::C_str

#include <string>           // std::string
#include <string_view>      // std::string_view
#include <sstream>          // std::ostringstream

namespace cppx
{
    namespace basic_string_building
    {
        CPPX_USE_STD( ostringstream, string, string_view );
        using namespace std::string_literals;       // E.g. ""s

        template< class Type >
        inline auto operator<<( string& s, const Type& value )
            -> string&
        {
            ostringstream stream;
            stream << value;
            s += stream.str();
            return s;
        }

        template<>
        inline auto operator<< <char>( string& s, const char& more )
            -> string&
        {
            s += more;
            return s;
        }

        template<>
        inline auto operator<< <C_str>( string& s, const C_str& more )
            -> string&
        {
            s += more;
            return s;
        }

        template<>
        inline auto operator<< <string_view>( string& s, const string_view& more )
            -> string&
        {
            s += more;
            return s;
        }

        template<>
        inline auto operator<< <string>( string& s, const string& more )
            -> string&
        {
            s += more;
            return s;
        }

        template< class Type >
        inline auto operator<<( string&& s, Type const& value )
            -> string&&
        { return  move( operator<<( s, value ) ); }

    }  // namespace basic_string_building
}  // namespace cppx
