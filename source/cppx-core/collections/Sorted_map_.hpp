#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core-language/syntax/declarations.hpp>           // CPPX_USE_STD
#include <cppx-core-language/types/Truth.hpp>                   // cppx::Truth

#include <map>                  // std::map

namespace cppx
{
    CPPX_USE_STD( map );

    template< class Key, class Value >
    class Sorted_map_
        : public map<Key, Value>
    {
    using Base = map<Key, Value>;
    public:
        using Base::map;
        using Base::operator[];

        auto operator[]( const Key& key ) const
            -> const Value&
        { return Base::at( key ); }
    };

    template< class Key, class Value, class Arg >
    auto is_in( const Sorted_map_<Key, Value>& map, const Arg& v )
        -> Truth
    { return map.count( v ) > 0; }

}  // namespace cppx
