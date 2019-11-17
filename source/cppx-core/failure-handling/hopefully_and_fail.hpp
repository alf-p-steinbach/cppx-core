#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/failure-handling/Abstract_source_location.hpp>  // cppx::Abstract_source_location
#include <cppx-core-language/syntax/all.hpp>                        // CPPX_USE_STD, [[noreturn]]
#include <cppx-core-language/types/Truth.hpp>                       // cppx::Truth

#include <stdexcept>        // std::runtime_error
#include <exception>        // std::throw_with_nested
#include <string>           // std::string
#include <utility>          // std::forward

namespace cppx
{
    inline namespace hopefully_and_fail {}  // See bottom part of this file.

    namespace hf
    {
        CPPX_USE_STD(
            forward,
            current_exception, runtime_error, string, throw_with_nested 
            );

        [[noreturn]]
        inline void noreturn() { throw 666; }

        //------------------------------------------ hopefully & fail
        //
        // The default `fail` function's exception can be caught as a `std::runtime_error`.
        // It's the current exception, if any, that's nested. And the nested exception
        // /can/ just be ignored at the exception handling site.
        //
        // The rationale of the nesting is to not discard useful information even though
        // it carries some overhead, because throwing should be rare, not the normal case.
        //
        // Typical usage patterns:
        //
        //      1;
        //      getline( cin, s )
        //          or fail( "foo - getline failed" );
        //
        //      2;
        //      const ptrdiff_t n_values = to_wide_from_utf8( &s[0], &wide_s[0] );
        //      hopefully( n_values >= 0 )
        //          or fail( "foo - to_wide_from_utf8 failed" );
        //      wide_s.resize( n_values );
        //
        // In future `fail` may be extended to support error codes by throwing a
        // `std::system_error`, which is derived from `std::runtime_error` and carries an
        // error code.

        inline auto hopefully( const Truth condition )
            -> Truth
        { return condition; }

        template< class X, class... More_args >
        //[[noreturn]]
        inline auto fail_( const string& message, More_args&&... more_args )
            -> Truth
        {
            // This checking is necessary for MinGW g++ 8.2.0. Not sure if the standard
            // requires it. It would be a design to attract bugs, if it were required.

            const Truth in_exception_handling = (current_exception() != nullptr);
            if( in_exception_handling )
            {
                // std::throw_with_nested is guaranteed [[noreturn]].
                throw_with_nested( X( message, forward<More_args>( more_args )... ) );
            }
            else
            {
                throw X( message, forward<More_args>( more_args )...  );
            }
        }

        template< class... More_args >
        //[[noreturn]]
        inline auto fail( const string& message, More_args&&... more_args )
            -> Truth
        { return fail_<runtime_error>( message, forward<More_args>( more_args )... ); }

        inline auto rich_exception_text(
            const string&                       message,
            const Abstract_source_location&     throw_point
            ) -> string
        {
            return string()
                + throw_point.function_name_or_unspecified() + " - " + message + "\n"
                + string( 4, ' ' ) + ">" + throw_point.file_and_line();
        }

        template< class X = runtime_error, class... More_args >
        //[[noreturn]]
        inline auto fail_with_location(
            const Abstract_source_location&     throw_point,
            const string&                       message,
            More_args&&...                      more_args
            ) -> Truth
        {
            return fail_<X>(
                rich_exception_text( message, throw_point ),
                forward<More_args>( more_args )...
                );
        }

        //------------------------------------------ Success, Failure & `>>`
        //
        // A unified notation that provides separation of failure /checking/ and
        // /throwing/ of exception with possibly costly to construct arguments.
        //
        // Since the `or` is the built-in `or` the arguments to `fail` are only evaluated
        // in the case of failure, which means the normal case is efficient.
        //
        // Typical usage patterns, here using a Windows' function that returns `HRESULT`:
        //
        //      CoInitialize( nullptr, COINIT_MULTITHREADED ) >> Success()
        //          or $fail( "CoInitialize failed" );
        //
        // where
        //
        //      auto operator>>( const HRESULT hr, Success )
        //          -> Truth
        //      { return SUCCEEDED( hr ); }

        struct Success{};
        struct Failure{};

        template< class Value >
        auto operator>>( const Value& v, Failure )
            -> Truth
        { return not (v >> Success{}); }

        struct Is_zero{};

        template< class Value >
        auto operator>>( const Value& v, Is_zero )
            -> Truth
        { return v == 0; }

    }  // namespace hf

    inline namespace hopefully_and_fail {

        using hf::noreturn;
        using hf::hopefully;
        using hf::fail_;
        using hf::fail;
        using hf::fail_with_location;

        using hf::Success;
        using hf::Failure;
        using hf::Is_zero;
        using hf::operator>>;

    }  // inline namespace hopefully_and_fail
}  // namespace cppx
