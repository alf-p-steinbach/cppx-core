#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

namespace cppx
{
    /// A helper for the `$items_of` macro, used there to prevent rvalue arguments.
    template< class Type >
    inline auto lvalue_ref_to( Type& c )
        -> Type&
    { return c; }

}  // namespace cppx
