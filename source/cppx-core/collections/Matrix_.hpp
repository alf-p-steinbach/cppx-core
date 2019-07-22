#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/collections/Range_.hpp>                 // cppx::(is_in, up_to_)
#include <cppx-core/failure-handling/macro-fail.hpp>        // CPPX_FAIL_
#include <cppx-core/language/syntax/macro-use.hpp>          // CPPX_USE_STD
#include <cppx-core/language/system/size-types.hpp>         // cppx::(Size, Index)
#include <cppx-core/text/basic-string-building.hpp>         // cppx::operator<<
#include <cppx-core/meta-type/type-traits.hpp>              // cppx::Item_for_collection_

#include <vector>       // std::vector
#include <stdexcept>    // std::out_of_range

namespace cppx
{
    CPPX_USE_STD( out_of_range, vector );

    template< class Item_param >
    class Matrix_
    {
        using Item = Item_param;

        vector<Item>        m_items;
        Size                m_width;
        Size                m_height;

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

        template< class Self
            , class = Enable_if_< is_a_< Matrix_, Unconst_< Self > > >
            >
        friend auto item_at( const Index col, const Index row, Self& self )
            -> Item_for_collection_<Self>&
        { return self.m_items[self.index_of( col, row )]; }

        template< class Self
            , class = Enable_if_< is_a_< Matrix_, Unconst_< Self > > >
            >
        friend auto item_at_checked( const Index col, const Index row, Self& self )
            -> Item_for_collection_<Self>&
        {
            hopefully(
                is_in( up_to( self.m_width ), col ) and
                is_in( up_to( self.m_height ), row )
            ) or CPPX_FAIL_( out_of_range,
                "Item position ("s << col << "," << row << ") is out of range"
            );
            return self.m_items[self.index_of( col, row )];
        }

        [[deprecated]]
        auto operator()( const Index col, const Index row ) const
            -> const Item&
        { return item_at( col, row, *this ); }

        [[deprecated]]
        auto operator()( const Index col, const Index row )
            -> Item&
        { return item_at( col, row, *this ); }

        [[deprecated]]
        auto at( const Index col, const Index row ) const
            -> const Item&
        { return item_at_checked( col, row, *this );  }

        [[deprecated]]
        auto at( const Index col, const Index row )
            -> Item&
        { return item_at_checked( col, row, *this );  }

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

    struct Matrix_position { Size x; Size y; };

    template< class Item>
    auto item_at( const Matrix_position& pos, const Matrix_<Item>& m )
        -> const Item&
    { return item_at( pos.x, pos.y, m ); }

    template< class Item>
    auto item_at( const Matrix_position& pos, Matrix_<Item>& m )
        -> Item&
    { return item_at( pos.x, pos.y, m ); }

    template< class Item>
    auto item_at_checked( const Matrix_position& pos, const Matrix_<Item>& m )
        -> const Item&
    { return item_at_checked( pos.x, pos.y, m ); }

    template< class Item>
    auto item_at_checked( const Matrix_position& pos, Matrix_<Item>& m )
        -> Item&
    { return item_at_checked( pos.x, pos.y, m ); }

}  // namespace cppx
