#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
/// \file
/// \brief Just a tad more readable than `enable_if_t`.

#include <utility>

namespace cppx
{

    /// \brief Just a tad more readable than `enable_if_t`.
    template< bool condition, class Result = void >     // "bool" until C++20
    using Enable_if_ = std::enable_if_t<condition, Result>;

}  // namespace cppx
