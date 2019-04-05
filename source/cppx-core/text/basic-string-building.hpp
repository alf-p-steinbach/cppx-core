#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <string>           // std::string
#include <sstream>          // std::ostringstream

namespace cppx
{
    namespace basic_string_building
    {
        using std::string, std::ostringstream;
        using namespace std::string_literals;       // E.g. ""s

        template< class Type >
        inline auto operator<<( string& s, Type const& value )
            -> string&
        {
            ostringstream stream;
            stream << value;
            s += stream.str();
            return s;
        }

        template< class Type >
        inline auto operator<<( string&& s, Type const& value )
            -> string&&
        { return  move( operator<<( s, value ) ); }

    }  // namespace basic_string_building
}  // namespace cppx
