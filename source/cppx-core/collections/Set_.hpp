#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core-language/syntax/macro-define_tag.hpp>       // CPPX_DEFINE_TAG
#include <cppx-core-language/syntax/Sequence_.hpp>              // cppx::Sequence_
#include <cppx-core-language/types/Truth.hpp>                   // cppx::Truth

#include <initializer_list>     // std::initializer_list
#include <utility>              // std::move
#include <unordered_set>        // std::unordered_set

CPPX_DEFINE_TAG( Iterators );       // tag::Iterators
CPPX_DEFINE_TAG( Values );          // tag.:Values
namespace cppx
{
    CPPX_USE_STD(
        initializer_list, move, unordered_set
        );

    template< class Key >
    class Set_
        : public unordered_set<Key>
    {
        using Base = unordered_set<Key>;

    public:
        Set_() {}

        Set_( const Base& other ):
            Base( other )
        {}

        Set_( Base&& other ):
            Base( move( other ) )
        {}

        Set_( const Key& a_key ):
            Base( &a_key, &a_key + 1 )
        {}

        // Only meaningful for integer-like Key:
        template< class Integer >
        Set_( const Sequence_<Integer> range ):
            Base( range.begin(), range.end() )
        {}
        
        Set_( tag::Values, initializer_list<Key> values ):
            Base( move( values ) )
        {}
        
        template< class Input_iterator >
        Set_( tag::Iterators, const Input_iterator first, const Input_iterator beyond ):
            Base( first, beyond )
        {}
    };

    template< class Key, class Arg >
    auto is_in( const unordered_set<Key>& set, const Arg& v )
        -> Truth
    { return set.count( v ) > 0; }


    //-------------------------------------  Explicit conversions to set:

    template< class Key >
    inline auto as_set( const Key& a_key )
        -> Set_<Key>
    { return { a_key }; }
    
    template< class Integer >
    inline auto as_set( const Sequence_<Integer> range )
        -> Set_<Integer>
    { return { range }; }
    
    template< class Key >
    inline auto as_set( const initializer_list<Key>& values )
        -> Set_<Key>
    { return { values }; }


    //-------------------------------------  Math-like set operations:

    template< class Key >
    auto set_union( const unordered_set<Key>& a, const unordered_set<Key>& b )
        -> Set_<Key>
    {
        const unordered_set<Key>& smallest  = (a.size() < b.size()? a : b);
        const unordered_set<Key>& largest   = (a.size() < b.size()? b : a);
        
        Set_<Key> result = largest;
        for( const Key& key : smallest )
        {
            result.insert( key );
        }
        return result;
    }

    template< class Key, class Arg >
    auto set_union( const unordered_set<Key>& a, const Arg& b )
        -> Set_<Key>
    { return set_union( a, Set_<Key>( b ) ); }
    
    template< class Key, class Arg >
    auto set_union(  const Arg& a, const unordered_set<Key>& b )
        -> Set_<Key>
    { return set_union( Set_<Key>( a ), b ); }

    template< class Key >
    auto set_difference( const unordered_set<Key>& a, const unordered_set<Key>& b )
        -> Set_<Key>
    {
        Set_<Key> result = a;
        for( const Key& key : b )
        {
            result.erase( key );
        }
        return result;
    }

    template< class Key, class Arg >
    auto set_difference( const unordered_set<Key>& a, const Arg& b )
        -> Set_<Key>
    { return set_difference( a, Set_<Key>( b ) ); }
    
    template< class Key >
    auto set_intersection( const unordered_set<Key>& a, const unordered_set<Key>& b )
        -> Set_<Key>
    {
        const unordered_set<Key>& smallest  = (a.size() < b.size()? a : b);
        const unordered_set<Key>& largest   = (a.size() < b.size()? b : a);
        
        Set_<Key> result;
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
    auto set_difference( Set_<Key>&& a, const unordered_set<Key>& b )
        -> Set_<Key>&&
    {
        for( const Key& key : b )
        {
            a.erase( key );
        }
        return move( a );
    }

}  // namespace cppx
