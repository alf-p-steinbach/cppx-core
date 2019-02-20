﻿#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/tmp/basic-Enable_if_.hpp>          // cppx::Enable_if_
#include <cppx-core/language/tmp/basic-type-traits.hpp>         // cppx::is_const_
#include <cppx-core/syntax/macro-use.hpp>                       // CPPX_USE_STD

#include <functional>   // std::(ref, reference_wrapper)

namespace cppx
{
    CPPX_USE_STD( ref, reference_wrapper );

    template< class Type
        ,class = Enable_if_<not is_const_<Type>>
        >
    class In_out_ref_:
        public reference_wrapper<Type>
    {
        template< class U, class > friend auto in_out_ref( U& o ) -> In_out_ref_<U>;

        In_out_ref_( Type& o ):
            reference_wrapper<Type>( o )
        {}

    public:
        In_out_ref_( reference_wrapper<Type>&& ref ):
            reference_wrapper<Type>( ref )
        {}
    };

    template<
        class Type,
        class = Enable_if_<not is_const_<Type>>
        >
    auto inline in_out_ref( Type& o )
        -> In_out_ref_<Type>
    { return In_out_ref_<Type>( o ); }

}  // namespace cppx
