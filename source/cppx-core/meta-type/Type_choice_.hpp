#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <type_traits>      // std::conditional_t

namespace cppx
{

    template< bool condition, class A, class B >
    using Type_choice_ = std::conditional_t<condition, A, B>;

}  // namespace cppx
