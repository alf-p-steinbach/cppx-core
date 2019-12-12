#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/failure-handling/Abstract_source_location.hpp>  // cppx::Abstract_source_location
#include <cppx-core-language/syntax/exception-throwing.hpp>         // cppx::(fail, hopefully, noreturn, Success, Failure, Is_zero, operator>>)
#include <cppx-core-language/syntax/declarations.hpp>               // CPPX_USE_STD
#include <cppx-core-language/types/Truth.hpp>                       // cppx::Truth

#include <stdexcept>        // std::runtime_error
#include <exception>        // std::throw_with_nested
#include <string>           // std::string
#include <utility>          // std::forward

namespace cppx
{
    namespace hopefully_and_fail
    {
        CPPX_USE_STD(
            forward,
            current_exception, runtime_error, string, throw_with_nested 
            );

        inline auto rich_exception_text(
            const string&                       message,
            const Abstract_source_location&     throw_point
            ) -> string
        {
            return string()
                + throw_point.function_name_or_unspecified() + " - " + message + "\n"
                + string( 4, ' ' ) + ">" + throw_point.file_and_line();
        }

        template< class X, class... More_args >
        //[[noreturn]]
        inline auto fail_with_location_(
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

        template< class... More_args >
        //[[noreturn]]
        inline auto fail_with_location(
            const Abstract_source_location&     throw_point,
            const string&                       message,
            More_args&&...                      more_args
            ) -> Truth
        {
            return fail_with_location_<runtime_error>(
                throw_point,
                message,
                forward<More_args>( more_args )...
                );
        }
    }  // namespace hopefully_and_fail

    using hopefully_and_fail::rich_exception_text;
    using hopefully_and_fail::fail_with_location_;
    using hopefully_and_fail::fail_with_location;
}  // namespace cppx
