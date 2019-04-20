#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/config.hpp>                         // cppx::use_ascii_substitutes
#include <cppx-core/language/types/type-makers.hpp>     // cppx::Type_choice_

namespace cppx
{
    namespace utf8
    {
        struct Symbol_strings
        {
            static constexpr auto& left_quote_str      = "“";
            static constexpr auto& right_quote_str     = "”";
            static constexpr auto& bullet_str          = "•";
            static constexpr auto& left_arrow_str      = "←";
            static constexpr auto& right_arrow_str     = "→";
        };
    }

    namespace ascii
    {
        struct Symbol_strings
        {
            static constexpr auto& left_quote_str      = "\"";
            static constexpr auto& right_quote_str     = "\"";
            static constexpr auto& bullet_str          = "*";
            static constexpr auto& left_arrow_str      = "<-";
            static constexpr auto& right_arrow_str     = "->";
        };
    }

    namespace best_effort
    {
        using Symbol_strings = Type_choice_<
            !!use_ascii_substitutes, ascii::Symbol_strings, utf8::Symbol_strings
            >;

        constexpr auto& left_quote_str      = Symbol_strings::left_quote_str;
        constexpr auto& right_quote_str     = Symbol_strings::right_quote_str;
        constexpr auto& bullet_str          = Symbol_strings::bullet_str;
        constexpr auto& left_arrow_str      = Symbol_strings::left_arrow_str;
        constexpr auto& right_arrow_str     = Symbol_strings::right_arrow_str;
    }  // namespace best_effort

}  // namespace cppx
