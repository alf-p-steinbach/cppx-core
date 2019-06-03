#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/syntax/macro-use.hpp>          // CPPX_USE_STD
#include <cppx-core/language/system/size-types.hpp>         // cppx::Size

#include <utility>      // std::forward

namespace cppx {
    CPPX_USE_STD( forward );

    template< auto F > struct Buffer_size_for_;

    template< auto F, class... Args >
    constexpr auto buffer_size_for_( Args&&... args )
        -> Size
    { return Buffer_size_for_<F>::value( forward<Args>( args )... ); }
}  // namespace cppx
