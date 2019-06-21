#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/stdlib-wrappers/type_info-util.hpp>     // cppx::Type_name_of_
#include <cppx-core/language/syntax/macro-use.hpp>          // CPPX_USE_STD
#include <cppx-core/language/syntax/type-assemblers.hpp>    // cppx::P_

#include <ostream>      // std::basic_ostream

namespace cppx {
    CPPX_USE_STD( basic_ostream, ios_base );

    template< class Char, class Traits, class Type >
    inline auto operator<<(basic_ostream<Char, Traits>& stream, const Type_name_of_<Type>& name )
        -> basic_ostream<Char, Traits> &
    { return stream << name.value();}

}  // namespace cppx
