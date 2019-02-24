#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/syntax/macro-use.hpp>               // CPPX_USE_STD

#include <unordered_map>            // std::unordered_map

namespace cppx
{
    CPPX_USE_STD( unordered_map );

    template< class Key, class Value >
    class Map_
        : public unordered_map<Key, Value>
    {
    using Base = unordered_map<Key, Value>;
    public:
        using Base::unordered_map;
        using Base::operator[];

        auto operator[]( const Key& key ) const
            -> const Value&
        { return Base::at( key ); }
    };

    template< class Key, class Value, class Arg >
    auto is_in( const unordered_map<Key, Value>& map, const Arg& v )
        -> bool
    { return map.count( v ) > 0; }

}  // namespace cppx
