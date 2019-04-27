#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
/// \file
/// \brief Provides the `only_lvalue_ref_to` helper for restricting macro arguments.

namespace cppx
{
    /// A helper for restricting macro arguments, used e.g. in `$items_of`.
    template< class Type >
    inline auto only_lvalue_ref_to( Type& c )
        -> Type&
    { return c; }

}  // namespace cppx
