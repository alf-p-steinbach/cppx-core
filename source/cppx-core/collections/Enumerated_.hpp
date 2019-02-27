#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/iterators/Forward_iterator_impl_.hpp>
#include <cppx-core/language/syntax/type-assemblers.hpp>            // cppx::P_

namespace cppx
{
    template< class Collection >
    class Enumerated_
    {
        P_<Collection>      m_p_collection;

    public:
        using Item = Item_for_collection_<Collection>;
        explicit Enumerated_( Collection& c ):
            m_p_collection( &c )
        {}
    };

    template< class Collection >
    auto enumerated( Collection& c )
        -> Enumerated_<Collection>
    { return {c]; }

}  // namespace cppx
