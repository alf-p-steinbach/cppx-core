#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core-language/syntax/macro-define_tag.hpp>       // CPPX_DEFINE_TAG
#include <cppx-core-language/syntax/Sequence_.hpp>              // cppx::Sequence_
#include <cppx-core-language/types/Truth.hpp>                   // cppx::Truth

#include <initializer_list>     // std::initializer_list
#include <utility>              // std::move
#include <set>                  // std::set

CPPX_DEFINE_TAG( Iterators );       // tag::Iterators
CPPX_DEFINE_TAG( Values );          // tag::Values
namespace cppx
{
    CPPX_USE_STD(
        initializer_list, move, set
        );

    template< class Key >
    class Sorted_set_
        : public set<Key>
    {
        using Base = set<Key>;

    public:
        Sorted_set_() {}

        Sorted_set_( const Base& other ):
            Base( other )
        {}

        Sorted_set_( Base&& other ):
            Base( move( other ) )
        {}

        Sorted_set_( const Key& a_key ):
            Base( &a_key, &a_key + 1 )
        {}

        // Only meaningful for integer-like Key:
        template< class Integer >
        Sorted_set_( const Sequence_<Integer> range ):
            Base( range.begin(), range.end() )
        {}
        
        Sorted_set_( tag::Values, initializer_list<Key> values ):
            Base( move( values ) )
        {}
        
        template< class Input_iterator >
        Sorted_set_( tag::Iterators, const Input_iterator first, const Input_iterator beyond ):
            Base( first, beyond )
        {}
    };

    template< class Key, class Arg >
    auto is_in( const set<Key>& set, const Arg& v )
        -> Truth
    { return set.count( v ) > 0; }


    //-------------------------------------  Explicit conversions to set:

    template< class Key >
    inline auto as_sorted_set( const Key& a_key )
        -> Sorted_set_<Key>
    { return { a_key }; }
    
    template< class Integer >
    inline auto as_sorted_set( const Sequence_<Integer> range )
        -> Sorted_set_<Integer>
    { return { range }; }
    
    template< class Key >
    inline auto as_sorted_set( const initializer_list<Key>& values )
        -> Sorted_set_<Key>
    { return { values }; }


    //-------------------------------------  Math-like set operations:

    template< class Key >
    auto set_union( const set<Key>& a, const set<Key>& b )
        -> Sorted_set_<Key>
    {
        const set<Key>& smallest  = (a.size() < b.size()? a : b);
        const set<Key>& largest   = (a.size() < b.size()? b : a);
        
        Sorted_set_<Key> result = largest;
        for( const Key& key : smallest )
        {
            result.insert( key );
        }
        return result;
    }

    template< class Key, class Arg >
    auto set_union( const set<Key>& a, const Arg& b )
        -> Sorted_set_<Key>
    { return set_union( a, Sorted_set_<Key>( b ) ); }
    
    template< class Key, class Arg >
    auto set_union(  const Arg& a, const set<Key>& b )
        -> Sorted_set_<Key>
    { return set_union( Sorted_set_<Key>( a ), b ); }

    template< class Key >
    auto set_difference( const set<Key>& a, const set<Key>& b )
        -> Sorted_set_<Key>
    {
        Sorted_set_<Key> result = a;
        for( const Key& key : b )
        {
            result.erase( key );
        }
        return result;
    }

    template< class Key, class Arg >
    auto set_difference( const set<Key>& a, const Arg& b )
        -> Sorted_set_<Key>
    { return set_difference( a, Sorted_set_<Key>( b ) ); }
    
    template< class Key >
    auto set_intersection( const set<Key>& a, const set<Key>& b )
        -> Sorted_set_<Key>
    {
        const set<Key>& smallest    = (a.size() < b.size()? a : b);
        const set<Key>& largest     = (a.size() < b.size()? b : a);
        
        Sorted_set_<Key> result;
        for( const Key& key : smallest )
        {
            if( is_in( largest, key ) )
            {
                result.insert( key );
            }
        }
        return result;
    }


    //-------------------------------------  Efficiency for temporaries

    template< class Key >
    auto set_difference( Sorted_set_<Key>&& a, const set<Key>& b )
        -> Sorted_set_<Key>&&
    {
        for( const Key& key : b )
        {
            a.erase( key );
        }
        return move( a );
    }

}  // namespace cppx
