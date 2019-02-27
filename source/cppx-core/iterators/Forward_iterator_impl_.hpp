#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core/language/syntax/macro-use.hpp>              // CPPX_USE_STD
#include <cppx-core/language/syntax/type-assemblers.hpp>        // cppx::P_
#include <cppx-core/language/types/signed-size-types.hpp>       // cppx::(Size)

#include <c/stddef.hpp>                             // ptrdiff_t
#include <iterator>                                 // std::(begin, end, forward_iterator_tag)

// Example usage:
//
//      class Iterator:
//          public Forward_iterator_impl_<Iterator, Integer>
//      {
//          Integer     m_current;
//      
//      public:
//          void advance() { ++m_current; }
//      
//          auto operator*() const
//              -> Integer
//          { return m_current; }
//                  
//          friend auto operator==( const Iterator& a, const Iterator& b )
//              -> bool
//          { return a.m_current == b.m_current; }
//      
//          explicit Iterator( const Integer value )
//              : m_current{ value }
//          {}
//      };

namespace cppx
{
    CPPX_USE_STD( forward_iterator_tag );
    
    template< class Derived, class Value_type_param >
    class Forward_iterator_impl_
    {
        auto derived_self()
            -> Derived&
        { return static_cast<Derived&>( *this ); }

    public:
        // `std::iterator_traits` types:
        using difference_type       = Size;
        using value_type            = Value_type_param;  // decltype( *declval<Derived>() );
        using pointer               = P_<value_type>;
        using reference             = const value_type&;
        using iterator_category     = forward_iterator_tag;

        using Value = Value_type_param;

        auto operator++()
            -> const Derived&
        {
            derived_self().advance();
            return derived_self();
        }
        
        auto operator++( int )
            -> Derived
        {
            Derived original = derived_self();
            derived_self().advance();
            return original;
        }

        friend auto operator!=( const Derived& a, const Derived& b )
            -> bool
        { return not(a == b); }
    };

}  // namespace cppx
