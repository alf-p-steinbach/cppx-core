#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
//
// This class is used by the CPPX_FAIL macro. It can't use things that use CPPX_FAIL.
// Line and character position indexing is 1-based.

#include <cppx-core/collections/is_empty.hpp>                       // cppx::is_empty
#include <cppx-core/failure-handling/Abstract_source_location.hpp>  // cppx::Abstract_source_location
#include <cppx-core-language/syntax/declarations.hpp>               // CPPX_USE_STD
#include <cppx-core-language/tmp/Enable_if_.hpp>                    // cppx::Enable_if_

#include <optional>                 // std::optional
#include <utility>                  // std::Enable_if_
#include <type_traits>              // std::is_same_v
#include <optional>                 // std::optional
#include <utility>                  // std::move
#include <type_traits>              // std::(Enable_if_, is_same_v)

//TODO: improve, clean

namespace cppx
{
    CPPX_USE_STD( string, move, optional );

    class Source_location:
        public Abstract_source_location
    {
        string  m_filename;
        int     m_linenumber;
        int     m_character_position;       // -1 if none.
        string  m_function_name;            // Empty if none.

    public:
        auto filename() const           -> string   override { return m_filename; }
        auto linenumber() const         -> int      override { return m_linenumber; }
        auto character_position() const -> int      override { return m_character_position; }
        auto function_name() const      -> string   override { return m_function_name; }

        using Abstract_source_location::function_name_or_unspecified;
        using Abstract_source_location::file_and_line;
        using Abstract_source_location::file_line_and_pos;
        using Abstract_source_location::failpoint_spec;
        using Abstract_source_location::operator string;

        Source_location(
            string              filename,
            optional<int>       linenumber          = {},
            optional<int>       character_position  = {},
            optional<string>    function_name       = {}
            ):
            m_filename( move( filename ) ),
            m_linenumber( linenumber.value_or( -1 ) ),
            m_character_position( character_position.value_or( -1 ) ),
            m_function_name( move( function_name ).value_or( "" ) )
        {}
    };

}  // namespace cppx
