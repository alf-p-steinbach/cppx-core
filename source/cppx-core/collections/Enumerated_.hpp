#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/collections/size-checking.hpp>                  // cppx::n_items_in
#include <cppx-core/iterators/Forward_iterator_impl_.hpp>           // cppx::Forward_iterator_impl_
#include <cppx-core/language/syntax/type-assemblers.hpp>            // cppx::P_
#include <cppx-core/meta-type/type-traits.hpp>                      // cppx::Iterator_for_

namespace cppx
{
    CPPX_USE_STD( declval );

    template< class Collection >
    class Enumerated_
    {
        using Collection_iterator = Iterator_for_<Collection>;

        P_<Collection>      m_p_collection;

    public:
        using   Item        = decltype( *declval<Collection_iterator>() );  // Usually a ref.
        using   Item_value  = Unref_<Item>;

        struct Item_and_index
        {
            Item    item;
            Index   index;
        };

        class Iterator:
            public Forward_iterator_impl_<Iterator, Item_and_index>
        {
            Collection_iterator     m_current;
            Index                   m_index;
      
        public:
            void advance() { ++m_current; ++m_index; }
      
            auto operator*() const
                -> Item_and_index
            { return {*m_current, m_index}; }
                  
            friend auto operator==( const Iterator& a, const Iterator& b )
                -> bool
            { return a.m_current == b.m_current; }
      
            explicit Iterator( const Collection_iterator it, const Index i ):
                m_current( it),
                m_index( i )
            {}
        };

        auto begin() const
            -> Iterator
        { return Iterator( std::begin( *m_p_collection ), 0 ); }

        auto end() const
            -> Iterator
        { return Iterator( std::end( *m_p_collection ), n_items_in( *m_p_collection ) ); }

        explicit Enumerated_( Collection& c ):
            m_p_collection( &c )
        {}
    };

    template< class Collection >
    auto enumerated( Collection& c )
        -> Enumerated_<Collection>
    { return {c]; }

}  // namespace cppx
