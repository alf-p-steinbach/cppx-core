﻿#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core/meta-template/Enable_if_.hpp>       // cppx::Enable_if_
#include <cppx-core/meta-type/type-traits.hpp>          // cppx::is_base_and_derived_
#include <cppx-core/meta-type/type-builders.hpp>        // cppx::r

namespace cppx
{
    // `true` if a pure downcast via `dynamic_cast` succeeds.
    // `false` if the `dynamic cast` fails or gives a cross cast.
    //
    // Essentially whether a `static_cast<Derived*>( &o )` would do the Right Thing™.

    template<
        class Derived, class Type,
        class = Enable_if_<is_base_and_derived_<Type, Derived>>
        >
    inline auto is_of_derived_class_( const Type& o )
        -> bool
    {
        const auto p_derived = dynamic_cast<P_<const Derived>>( &o );
        return static_cast<P_<const Type>>( p_derived ) == &o;
    }
}  // namespace cppx
