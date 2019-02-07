#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <cppx-core/collections/Forward_iterator_impl_.hpp>

#include <c/assert.hpp>

namespace cppx{
    
    template< class Integer >
    class Range_
    {
        Integer     m_lower;
        Integer     m_upper;

        class Iterator:
            public Forward_iterator_impl_<Iterator, Integer>
        {
            Integer     m_current;

        public:
            void advance() { ++m_current; }

            auto operator*() const noexcept
                -> Integer
            { return m_current; }
            
            friend auto operator==( const Iterator& a, const Iterator& b ) noexcept
                -> bool
            { return a.m_current == b.m_current; }

            explicit Iterator( const Integer value ) noexcept
                : m_current{ value }
            {}
        };

    public:
        constexpr auto lower() const noexcept -> Integer { return m_lower; }
        constexpr auto upper() const noexcept -> Integer { return m_upper; }

        constexpr auto size() const noexcept -> Integer { return 1 + m_upper - m_lower; }

        constexpr auto contains( const Integer x ) const noexcept
            -> bool
        { return m_lower <= x and x <= m_upper; }

        auto begin() const noexcept  -> Iterator     { return Iterator( m_lower ); }
        auto end() const noexcept    -> Iterator     { return Iterator( m_upper + 1 ); }

        constexpr Range_( const Integer lower, const Integer upper ) noexcept
            : m_lower( lower )
            , m_upper( upper )
        {}
    };

    using Range = Range_<int>;

    inline constexpr auto up_to( const int n ) noexcept
        -> Range
    { return Range( 0, n - 1 ); }

    template< class Integer >
    void reversed( const Range_<Integer>& ) = delete;           // TODO: implement

}  // namespace cppx
