#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/failure-handling/macro-fail.hpp>            // CPPX_FAIL
#include <cppx-core-language/syntax/macro-define_tag.hpp>       // CPPX_DEFINE_TAG
#include <cppx-core-language/syntax/macro-use.hpp>              // CPPX_USE_STD
#include <cppx-core-language/syntax/type-builders.hpp>          // cppx::Type_
#include <cppx-core-language/tmp/Enable_if_.hpp>                // cppx::Enable_if_
#include <cppx-core-language/tmp/type-traits.hpp>               // cppx::is_same_type_
#include <cppx-core-language/system/size-types.hpp>             // cppx::Size
#include <cppx-core-language/types/C_str_.hpp>                  // cppx::C_str
#include <cppx-core/stdlib-wrappers/filesystem-util.hpp>        // cppx::fs::*
#include <cppx-core/text/basic-string-building.hpp>             // cppx::operator<<
#include <cppx-core/text/string-util.hpp>                       // cppx::quoted

#include <c/assert.hpp>     // assert
#include <c/stdio.hpp>      // fopen, Windows _wfopen, FILE
#include <algorithm>        // std::copy
#include <string>           // std::(string, wstring)
#include <typeinfo>         // std::type_info for use of typeid
#include <utility>          // std::exchange
#include <vector>           // std::vector

CPPX_DEFINE_TAG( Read );
CPPX_DEFINE_TAG( Write );
CPPX_DEFINE_TAG( Append );
namespace cppx
{
    CPPX_USE_STD( copy, exchange, string, vector );

    inline auto open_c_file( const fs::path& path, const C_str options )
        -> Type_<FILE*>
    {
        #ifdef _WIN32
            using std::wstring;
            const auto woptions = wstring( options, options + strlen( options ) );
            return _wfopen( path.wstring().c_str(), woptions.c_str() );
        #else
            return fopen( path.string().c_str(), options );
        #endif
    }

    template< class T >
    inline void read( const Type_<FILE*> f, T& o )
    {
        const Size n_read = fread( &o, sizeof( T ), 1, f );
        hopefully( n_read == 1 )
            or $fail( ""s << "Failed to read " << typeid( T ).name() );
    }

    template< class T >
    inline auto read_( const Type_<FILE*> f )
        -> T
    {
        T result;
        read( f, result );
        return result;
    }

    template< class T >
    inline void read_sequence(
        const Type_<FILE*>      f,
        const Type_<T*>         p_start,
        const Type_<T*>         p_beyond
    )
    {
        const Size n = p_beyond - p_start;
        assert( n < INT_MAX );
        const Size n_read = fread( p_start, sizeof( T ), int( n ), f );
        hopefully( n_read == n )
            or $fail( ""s << "Failed to read " << n << " items of type " << typeid( T ).name() );
    }

    template< class T >
    inline auto read_sequence_( const Type_<FILE*> f, const Size n )
        -> vector<T>
    {
        auto result = vector<T>( n );

        if( n == 0 ) {
            return result;
        }

        read_sequence( f, &result[0], &result[0] + n );
        return result;
    }

    inline auto read_c_string( const Type_<FILE*> f )
        -> string
    {
        string s;
        int ch;
        while( (ch = fgetc( f )) != EOF and ch != 0 ) {
            s += char( ch );
        }
        return s;
    }

    template< class T >
    inline auto peek_( const Type_<FILE*> f )
        -> T
    {
        T result;
        const long read_position = ftell( f );
        read( f, result );
        fseek( f, read_position, SEEK_SET );
        return result;
    }

    template< class T >
    auto from_bytes_( const Type_<const Byte*> p_first )
        -> T
    {
        T result;
        memcpy( &result, p_first, sizeof( T ) );
        return result;
    }

    template< class T >
    auto sequence_from_bytes_( const Type_<const Byte> p_first, const Size n )
        -> vector<T>
    {
        vector<T> result;
        if( n <= 0 ) {
            return result;
        }

        result.reserve( n );
        for( const Index i: zero_to( n ) ) {
            result.push_back( from_bytes_<T>( p_first + i*sizeof( T ) ) );
        }
        return result;
    }

    class C_file
    {
        C_file( const C_file& ) = delete;
        auto operator=( const C_file& ) -> C_file& = delete;

        Type_<FILE*>    m_file;

    public:
        auto file_pointer() const
            -> Type_<FILE*>
        { return m_file; }

        operator Type_<FILE*> () const { return file_pointer(); }

        auto release()
            -> Type_<FILE*>
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
}  // cppx
