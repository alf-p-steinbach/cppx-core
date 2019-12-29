#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/config.hpp>                         // cppx::use_ascii_substitutes
#include <cppx-core-language/tmp/Type_choice_.hpp>      // cppx::Type_choice_

namespace cppx
{
    namespace utf8_symbols
    {
        struct Strings
        {
            static constexpr auto& left_quote_str      = "“";
            static constexpr auto& right_quote_str     = "”";
            static constexpr auto& bullet_str          = "•";
            static constexpr auto& left_arrow_str      = "←";
            static constexpr auto& right_arrow_str     = "→";
        };
    }

    namespace ascii_symbols
    {
        struct Strings
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
            !!use_ascii_substitutes, ascii_symbols::Strings, utf8_symbols::Strings
            >;

        inline constexpr auto& left_quote_str   = Symbol_strings::left_quote_str;
        inline constexpr auto& right_quote_str  = Symbol_strings::right_quote_str;
        inline constexpr auto& bullet_str       = Symbol_strings::bullet_str;
        inline constexpr auto& left_arrow_str   = Symbol_strings::left_arrow_str;
        inline constexpr auto& right_arrow_str  = Symbol_strings::right_arrow_str;
    }  // namespace best_effort

}  // namespace cppx
