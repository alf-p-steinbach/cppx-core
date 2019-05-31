#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/failure-handling/macro-fail.hpp>            // CPPX_FAIL
#include <cppx-core/language/syntax/macro-define_tag.hpp>       // CPPX_DEFINE_TAG
#include <cppx-core/language/syntax/macro-use.hpp>              // CPPX_USE_STD
#include <cppx-core/language/tmp-support/basic-Enable_if_.hpp>  // cppx::Enable_if_
#include <cppx-core/language/tmp-support/basic-type-traits.hpp> // cppx::is_same_type_
#include <cppx-core/language/types/C_str_.hpp>                  // cppx::C_str
#include <cppx-core/text/basic-string-building.hpp>             // cppx::operator<<
#include <cppx-core/text/string-util.hpp>                       // cppx::quoted

#include <c/stdio.hpp>      // fopen, Windows _wfopen
#include <algorithm>        // std::copy
#include <filesystem>       // std::filesystem
#include <string>           // std::(string, wstring)
#include <utility>          // std::exchange

CPPX_DEFINE_TAG( Read );
CPPX_DEFINE_TAG( Write );
CPPX_DEFINE_TAG( Append );
namespace cppx
{
    namespace fs = std::filesystem;
    CPPX_USE_STD( copy, exchange, string );

    inline namespace fs_util
    {
        template<
            class Fs_path,
            class = Enable_if_<is_same_type_<Fs_path, fs::path>>
        >
            auto utf8_from( const Fs_path& path )
            -> string
        {
            if constexpr( is_same_type_<string, decltype( path.u8string() )> )
            {
                return path.u8string();
            }
            else
            {
                $with( path.u8string() ) { return string( _.begin(), _.end() ); }
            }
        }

        inline auto open_c_file( const fs::path& path, const C_str options )
            -> P_<FILE>
        {
            #ifdef _WIN32
                using std::wstring;
                const auto woptions = wstring( options, options + strlen( options ) );
                return _wfopen( path.wstring().c_str(), woptions.c_str() );
            #else
                return fopen( path.string().c_str(), options );
            #endif
        }

        class C_file
        {
            C_file( const C_file& ) = delete;
            auto operator=( const C_file& ) -> C_file& = delete;

            P_<FILE>    m_file;

        public:
            auto file_pointer() const
                -> P_<FILE>
            { return m_file; }
        
            operator P_<FILE> () const { return file_pointer(); }

            auto release()
                -> P_<FILE>
            { return exchange( m_file, nullptr ); }

            ~C_file()
            {
                if( m_file ) { fclose( m_file ); }
            }

            C_file( tag::Read, const fs::path& path ):
                m_file( open_c_file( path, "rb" ) )
            {
                hopefully( m_file != nullptr )
                    or CPPX_FAIL(
                        "Unable to open "s << quoted( cppx::utf8_from( path ) ) << " for reading"
                    );
            }

            C_file( tag::Write, const fs::path& path ):
                m_file( open_c_file( path, "wb" ) )
            {
                hopefully( m_file != nullptr )
                    or CPPX_FAIL(
                        "Unable to open "s << quoted( cppx::utf8_from( path ) ) << " for writing"
                    );
            }

            C_file( tag::Append, const fs::path& path ):
                m_file( open_c_file( path, "wab" ) )
            {
                hopefully( m_file != nullptr )
                    or CPPX_FAIL(
                        "Unable to open "s << quoted( cppx::utf8_from( path ) ) << " for appending"
                    );
            }
        };
    }  // namespace fs_util
}  // cppx
