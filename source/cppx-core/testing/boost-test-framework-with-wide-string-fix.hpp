#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
//
// In one translation unit, define BOOST_TEST_MODULE before including this.
// See the Boost Test documentation.

#include <cppx-core/testing/boost-test-framework.hpp>       // boost::*, CPPX_xxx

#include <cppx-core/language/syntax/macro-use.hpp>          // CPPX_USE_STD
#include <cppx-core/language/syntax/type-builders.hpp>      // cppx::(P_, Raw_array_)

#include <string_view>      // std::(wstring, u16string, u32string)
#include <string_view>      // std::(wstring_view, u16string_view, u32string_view)
#include <ostream>          // std::ostream
#include <iomanip>          // std::(setw, setfill)

//namespace boost::test_tools::tt_detail  // Depends on Boost version.. :(

namespace cppx::boost_fix
{
    CPPX_USE_STD( ostream, basic_string_view );

    /// @cond DOXY_SHOW_IMPL_DETAILS
    namespace impl
    {
        template< class Char >
        struct Char_type_id_;

        template<> struct Char_type_id_<char>{ enum{ value = 0 }; };
        template<> struct Char_type_id_<wchar_t>{ enum{ value = 1 }; };
        template<> struct Char_type_id_<char16_t>{ enum{ value = 2 }; };
        template<> struct Char_type_id_<char32_t>{ enum{ value = 3 }; };

        template< class Char >
        constexpr int char_type_id_ = Char_type_id_<Char>::value;
    }  // namespace impl
    /// @endcond

    template< class Char >
    inline auto print_on( ostream& os, const P_<const char> type_spec, const basic_string_view<Char>& ws )
        -> ostream&
    {
        static const Raw_array_<P_<const char>> prefixes  = { "", "L", "u",   "U" };

        os
            << type_spec
            << (*type_spec? "( " : "")
            << prefixes[impl::char_type_id_<Char>]
            << "\"";
        for( const Char wch : ws )
        {
            if( ' ' < wch and wch < 127 )
            {
                os << char( wch );
            }
            else
            {
                os
                    << "\\u"
                    << std::hex << std::setfill( '0' )
                    << std::setw( 2*sizeof( wchar_t ) ) << unsigned( wch )
                    << std::setfill( ' ' ) << std::dec
                    << "\" " << prefixes[impl::char_type_id_<Char>] << "\"";
            }
        }
        os << "\"" << (*type_spec? " )" : "");
        return os;
    }
}  // namespace cppx::boost_fix

// See <url: https://www.boost.org/doc/libs/1_64_0/libs/test/doc/html/boost_test/test_output/test_tools_support_for_logging/testing_tool_output_disable.html#ref_log_output_custom_customization_point>
namespace std       // For ADL lookup. Not formally permitted, but needed.
{
    inline auto boost_test_print_type( ostream& os, const wstring_view& ws )
        -> ostream&
    { return cppx::boost_fix::print_on( os, "wstring_view", ws ); }

    inline auto boost_test_print_type( ostream& os, const u16string_view& ws )
        -> ostream&
    { return cppx::boost_fix::print_on( os, "u16string_view", ws ); }

    inline auto boost_test_print_type( ostream& os, const u32string_view& ws )
        -> ostream&
    { return cppx::boost_fix::print_on( os, "u32string_view", ws ); }

    inline auto boost_test_print_type( ostream& os, const wstring& ws )
        -> ostream&
    { return cppx::boost_fix::print_on<wchar_t>( os, "wstring", ws ); }

    inline auto boost_test_print_type( ostream& os, const u16string& ws )
        -> ostream&
    { return cppx::boost_fix::print_on<char16_t>( os, "u16string", ws ); }

    inline auto boost_test_print_type( ostream& os, const u32string& ws )
        -> ostream&
    { return cppx::boost_fix::print_on<char32_t>( os, "u32string", ws ); }

    inline auto boost_test_print_type( ostream& os, const cppx::P_<const wchar_t> ws )
        -> ostream&
    { return cppx::boost_fix::print_on<wchar_t>( os, "", ws ); }

    inline auto boost_test_print_type( ostream& os, const cppx::P_<const char16_t> ws )
        -> ostream&
    { return cppx::boost_fix::print_on<char16_t>( os, "", ws ); }

    inline auto boost_test_print_type( ostream& os, const cppx::P_<char32_t> ws )
        -> ostream&
    { return cppx::boost_fix::print_on<char32_t>( os, "", ws ); }
}  // namespace std
