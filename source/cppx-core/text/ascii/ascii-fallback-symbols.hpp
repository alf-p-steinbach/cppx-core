#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

namespace cppx
{
    namespace best_effort
    {
    #ifdef CPPX_ASCII_PLEASE
        constexpr auto& left_quote_str      = "\"";
        constexpr auto& right_quote_str     = "\"";
        constexpr auto& bullet_str          = "*";
        constexpr auto& left_arrow_str      = "<-";
        constexpr auto& right_arrow_str     = "->";
    #else
        constexpr auto& left_quote_str      = "“";
        constexpr auto& right_quote_str     = "”";
        constexpr auto& bullet_str          = "•";
        constexpr auto& left_arrow_str      = "←";
        constexpr auto& right_arrow_str     = "→";
    #endif
    }  // namespace best_effort
}  // namespace cppx
