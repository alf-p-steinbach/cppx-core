#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/collections/dynamic-size-checking.hpp>              // cppx::n_items_of
#include <cppx-core-language/syntax/types/type-builders.hpp>            // cppx::P_
#include <cppx-core-language/syntax/declarations/macro-define_tag.hpp>  // CPPX_DEFINE_TAG
#include <cppx-core-language/types/Forward_iterator_impl_.hpp>          // cppx::Forward_iterator_impl_
#include <cppx-core-language/types/Truth.hpp>                           // cppx::Truth
#include <cppx-core/meta-type/collection-traits.hpp>                    // cppx::Iterator_for_

#include <initializer_list> // std::initializer_list
#include <iterator>         // std::begin

CPPX_DEFINE_TAG( Temporary );

namespace cppx
{
    CPPX_USE_STD( declval, initializer_list );

    template< class Collection >
    class Enumerated_
    {
        using Collection_iterator = Iterator_for_<Collection>;

        P_<Collection>      m_p_collection;

    public:
        using   Item        = decltype( *std::begin( declval<Collection&>() ) );    // Usually a ref.
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
                -> Truth
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
        { return Iterator( std::end( *m_p_collection ), n_items_of( *m_p_collection ) ); }

        explicit Enumerated_( Collection& c ):
            m_p_collection( &c )
        {}

        explicit Enumerated_( tag::Temporary, Collection&& c ):
            m_p_collection( &c )
        {}
    };

    template< class Collection >
    auto enumerated( Collection& c )
        -> Enumerated_<Collection>
    { return Enumerated_<Collection>( c ); }

    template< class Item >
    auto enumerated( const initializer_list<Item>& list )
        -> Enumerated_<const initializer_list<Item>>
    { return Enumerated_<const initializer_list<Item>>( list ); }
}  // namespace cppx
