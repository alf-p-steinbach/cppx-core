#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
//
// Mainly for use with range based `for` loops.

#include <cppx-core/collections/is_empty.hpp>                       // cppx::is_empty
#include <cppx-core/language/syntax/macro-use.hpp>                  // CPPX_USE_STD
#include <cppx-core/language/signed-sizes.hpp>                      // cppx::Size
//#include <cppx-core/meta-template/Enable_if_.hpp>                   // cppx::Enable_if_
//#include <cppx-core/meta-type/type-traits.hpp>                      // cppx::is_char_type_

#include <iterator>     // std::(begin, distance, end, prev, next, make_reverse_iterator, reverse_iterator )
#include <queue>        // std::queue
#include <stack>        // std::stack
#include <utility>      // std::(declval, move)

namespace cppx
{
    CPPX_USE_STD(
        begin, declval, distance, end, make_reverse_iterator, move, next, prev,
        queue, reverse_iterator, stack
        );

    template< class Iterator >
    class Span_
    {
        Iterator    m_first;
        Iterator    m_beyond;

    public:
        auto first() const      -> Iterator { return m_first; }
        auto beyond() const     -> Iterator { return m_beyond; }
        auto& front() const                 { return *m_first; }
        auto is_empty() const   -> bool     { return (m_first == m_beyond); }

        // Standard library & core language naming convention adapters.
        auto begin() const      -> Iterator { return m_first; }
        auto end() const        -> Iterator { return m_beyond; }
        auto empty() const      -> bool     { return (m_first == m_beyond); }

        Span_( const Iterator first, const Iterator beyond ):
            m_first( first ),
            m_beyond( beyond )
        {}

        template< class Collection >
        Span_( Collection& c ):
            m_first( begin( c ) ),
            m_beyond( end( c ) )
        {}
    };

    template< class Iterator >
    inline auto n_items_in( const Span_<Iterator>& range )
        -> Size
    { return distance( range.begin(), range.end() ); }

    template< class Iterator >
    inline auto span_of( const Iterator first, const Iterator beyond )
        -> Span_<Iterator>
    { return Span_<Iterator>( first, beyond ); }

    template< class Container >
    inline auto all_of( Container& c )
        -> Span_<decltype( begin( c ) )>
    { return span_of( begin( c ), end( c ) ); }

    template< class Item, class Container >
    auto all_of( const queue<Item, Container>& q )
        -> Span_<decltype( begin( declval<const Container>() ) )>
    {
        struct Accessible: queue<Item, Container>
        {
            static auto container_of( const queue<Item, Container>& q )
                -> const Container&
            { return q.*&Accessible::c; }
        };
    
        return all_of( Accessible::container_of( q ) );
    }

    template< class Item, class Container >
    auto all_of( const stack<Item, Container>& st )
        -> Span_<decltype( begin( declval<const Container>() ) )>
    {
        struct Accessible: stack<Item, Container>
        {
            static auto container_of( const stack<Item, Container>& st )
                -> const Container&
            { return st.*&Accessible::c; }
        };
    
        return all_of( Accessible::container_of( st ) );
    }

    template< class Container >
    inline auto all_but_first_of( Container& c )
        -> Span_<decltype( begin( c ) )>
    {
        const auto all = all_of( c );
        return span_of( next( all.first() ), all.beyond() );
    }

    template< class Container >
    inline auto all_but_first_n_of( Container& c, const Size n )
        -> Span_<decltype( begin( c ) )>
    {
        const auto all = all_of( c );
        return span_of( next( all.first(), n ), all.beyond() );
    }

    template< class Container >
    inline auto all_but_last_of( Container& c )
        -> Span_<decltype( begin( c ) )>
    {
        const auto all = all_of( c );
        return span_of( all.first(), prev( all.beyond() ) );
    }

    template<
        class Char, Size n
        //,class = Enable_if_<is_a_char_type_<Char>>
        >
    inline auto text_span_of_literal( const Raw_array_of_<n, const Char>& string_literal )
        -> Span_<P_<const Char>>
    { return all_but_last_of( string_literal ); }

    template< class Container >
    inline auto all_but_last_n_of( Container& c, const Size n )
        -> Span_<decltype( begin( c ) )>
    {
        const auto all = all_of( c );
        return span_of( all.first(), prev( all.beyond(), n ) );
    }

    template< class Container >
    inline auto reversed( Container& c )
        -> Span_<reverse_iterator<decltype( begin( c ) )>>
    {
        const auto all = all_of( c );
        return span_of(
            make_reverse_iterator( all.beyond() ),
            make_reverse_iterator( all.first() )
            );
    }

}  // namespace cppx
