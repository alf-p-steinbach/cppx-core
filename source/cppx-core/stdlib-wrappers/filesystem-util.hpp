#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/failure-handling/macro-fail.hpp>            // CPPX_FAIL
#include <cppx-core/language/syntax/macro-define_tag.hpp>       // CPPX_DEFINE_TAG
#include <cppx-core/language/syntax/macro-use.hpp>              // CPPX_USE_STD
#include <cppx-core/language/tmp-support/basic-Enable_if_.hpp>  // cppx::Enable_if_
#include <cppx-core/language/tmp-support/basic-type-traits.hpp> // cppx::is_same_type_
#include <cppx-core/language/types/C_str_.hpp>                  // cppx::C_str
#include <cppx-core/text/basic-string-building.hpp>             // cppx::operator<<
#include <cppx-core/text/string-util.hpp>                       // cppx::quoted

#include <c/assert.hpp>     // assert
#include <c/stdio.hpp>      // fopen, Windows _wfopen, FILE
#include <algorithm>        // std::copy
#include <filesystem>       // std::filesystem
#include <string>           // std::(string, wstring)
#include <typeinfo>         // std::type_info for use of typeid
#include <utility>          // std::exchange
#include <vector>           // std::vector

CPPX_DEFINE_TAG( Read );
CPPX_DEFINE_TAG( Write );
CPPX_DEFINE_TAG( Append );
namespace cppx
{
    namespace fs = std::filesystem;
    CPPX_USE_STD( copy, exchange, string, vector );

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

        template< class Type >
        inline void read( const P_<FILE> f, Type& o )
        {
            int n_read = fread( &o, sizeof( Type ), 1, f );
            hopefully( n_read == 1 )
                or $fail( ""s << "Failed to read " << typeid( Type ).name() );
        }

        template< class Type >
        inline auto read_( const P_<FILE> f )
            -> Type
        {
            Type result;
            read( f, result );
            return result;
        }

        template< class Type >
        inline void read_sequence( const P_<FILE> f, const P_<Type> p_start, const P_<Type> p_beyond )
        {
            const Size n = p_beyond - p_start;
            assert( n < INT_MAX );
            const int n_read = fread( p_start, sizeof( Type ), int( n ), f );
            hopefully( n_read == n )
                or $fail( ""s << "Failed to read " << n << " items of type " << typeid( Type ).name() );
        }

        template< class Type >
        inline auto read_sequence_( const Size n, const P_<FILE> f )
            -> vector<Type>
        {
            auto result = vector<Type>( n );

            if( n == 0 ) {
                return result;
            }

            read_sequence( f, &result[0], &result[0] + n );
            return result;
        }

        template< class Type >
        inline auto peek_( const P_<FILE> f )
            -> Type
        {
            Type result;
            const long read_position = ftell( f );
            read( f, result );
            fseek( f, read_position, SEEK_SET );
            return result;
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
