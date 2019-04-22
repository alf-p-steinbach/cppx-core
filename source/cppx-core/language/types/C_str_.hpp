﻿#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
/// \file
/// \brief Simple C string pointer type names such as `C_str` for `char const*`.
///
/// The shortest names like `C_str` stand for `const` string data. The prefix `Mutable_`,
/// as in `Mutable_c_str`, indicates mutable string data. This naming reflects
/// an experience that handling `const` string data is by far most common.
///
/// Using the type names avoids issues with non-reading direction placement of `*`,
/// and it supports prefix `const`. For example, instead of
///
///     char const* const s = "Blah";
///
/// ... you can write
///
///     const C_str s = "Blah";
///
/// Of course, for this particular example it would be silly to throw away the string
/// length information, so one should better use `std::string_view` and write
///
///     constexpr string_view s = "Blah";

#include <cppx-core/language/types/type-makers.hpp>     // cppx::(P_, Const_, Unconst_)

namespace cppx
{
    // Enable_if_<is_a_cpp03_char_type_<Unconst_<Char>>>
    template< class Char >
    using C_str_            = P_<Const_<Char>>;     // Effectively `Char const*`.

    template< class Char >
    using Mutable_c_str_    = P_<Unconst_<Char>>;   // Effectively `Unconst_<Char>*`.

    using C_str                 = C_str_<char>;             // Effectively `char const*`.
    using Wide_c_str            = C_str_<wchar_t>;          // Effectively `wchar_t const*`.
    using Mutable_c_str         = Mutable_c_str_<char>;     // Effectively `char*`.
    using Mutable_wide_c_str    = Mutable_c_str_<wchar_t>;  // Effectively `wchar_t*`.

} // namespace cppx
