#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

namespace cppx
{
    template< class Type >
    inline auto lvalue_ref_to( Type& c )
        -> Type&
    { return c; }

}  // namespace cppx
