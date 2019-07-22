#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/collections/Range_.hpp>                 // cppx::(is_in, up_to_)
#include <cppx-core/failure-handling/macro-fail.hpp>        // CPPX_FAIL_
#include <cppx-core/language/syntax/macro-use.hpp>          // CPPX_USE_STD
#include <cppx-core/language/system/size-types.hpp>         // cppx::(Size, Index)
#include <cppx-core/text/basic-string-building.hpp>         // cppx::operator<<

#include <vector>       // std::vector
#include <stdexcept>    // std::out_of_range

namespace cppx
{
    CPPX_USE_STD( out_of_range, vector );

    template< class Item >
    class Matrix_
    {
        vector<Item>        m_items;
        Size                m_width;
        Size                m_height;

        template< class Result, class Self >
        static auto checked_at( Self& self, const Index col, const Index row )
            -> Result&
        {
            hopefully(
                is_in( up_to( self.m_width ), col ) and
                is_in( up_to( self.m_height ), row )
                )
                or CPPX_FAIL_( out_of_range,
                    "Item position ("s << col << "," << row << ") is out of range"
                    );
            return self.m_items[self.index_of( col, row )];
        }

    public:
        auto n_items() const -> Size    { return m_items.size(); }
        auto width() const  -> Size     { return m_width; }
        auto height() const -> Size     { return m_height; }

        auto begin() const      { return m_items.begin(); }
        auto end() const        { return m_items.end();  }
        auto data() const       { return m_items.data(); }
        auto begin()            { return m_items.begin(); }
        auto end()              { return m_items.end();  }
        auto data()             { return m_items.data(); }

        auto index_of( const Index col, const Index row ) const
            -> Index
        { return row*m_width + col; }

        auto col_of( const Index i ) const
            -> Index
        { return i % m_width; }

        auto row_of( const Index i ) const
            -> Index
        { return i / m_width; }

        auto operator()( const Index col, const Index row ) const
            -> const Item&
        { return m_items[index_of( col, row )]; }

        auto operator()( const Index col, const Index row )
            -> Item&
        { return m_items[index_of( col, row )]; }

        auto at( const Index col, const Index row ) const
            -> const Item&
        { return checked_at<const Item>( *this, col, row );  }

        auto at( const Index col, const Index row )
            -> Item&
        { return checked_at<Item>( *this, col, row );  }

        Matrix_():
            m_items(),
            m_width( 0 ),
            m_height( 0 )
        {}

        Matrix_( const Size width, const Size height, const Item& init_value = Item() ):
            m_items( width*height, init_value ),
            m_width( width ),
            m_height( height )
        {}
    };
}  // namespace cppx
