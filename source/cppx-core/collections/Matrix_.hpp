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

    namespace matrix {
        struct Width{ Size value; };
        struct Height{ Size value; };
        struct Position { Size x; Size y; };

        struct Basic_types
        {
            using Width     = matrix::Width;
            using Height    = matrix::Height;
            using Position  = matrix::Position;
        };

        class Layout:
            public Basic_types
        {
            Size                m_width;
            Size                m_height;

        public:
            auto width() const  -> Size     { return m_width; }
            auto height() const -> Size     { return m_height; }
            auto n_items() const -> Size    { return m_width*m_height; }

            auto index_of( const Index col, const Index row ) const
                -> Index
            { return row*m_width + col; }

            auto col_of( const Index i ) const
                -> Index
            { return i % m_width; }

            auto row_of( const Index i ) const
                -> Index
            { return i / m_width; }

            auto index_of_position( const Position& pos )
                -> Index
            { return index_of( pos.x, pos.y ); }

            auto position_of_index( const Index i )
                -> Position
            { return Position{ col_of( i ), row_of( i ) }; }

            Layout(): m_width( 0 ), m_height( 0 ) {}

            Layout(
                const Width     width,
                const Height    height
                ):
                m_width( width.value ),
                m_height( height.value )
            {}
        };
    }  // namespace matrix

    template< class Item_param >
    class Matrix_:
        public matrix::Layout
    {
        using Item = Item_param;

        vector<Item>        m_items;

        template< class Self >
        static auto impl_item_at( const Index col, const Index row, Self& self )
            -> Item_for_collection_<Self>&
        { return self.m_items[self.index_of( col, row )]; }

        template< class Self >
        static auto impl_item_at_checked( const Index col, const Index row, Self& self )
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

    public:
        auto begin() const      { return m_items.begin(); }
        auto end() const        { return m_items.end();  }
        auto data() const       { return m_items.data(); }
        auto begin()            { return m_items.begin(); }
        auto end()              { return m_items.end();  }
        auto data()             { return m_items.data(); }

        auto operator()( const Index col, const Index row ) const
            -> const Item&
        { return impl_item_at( col, row, *this ); }

        auto operator()( const Index col, const Index row )
            -> Item&
        { return impl_item_at( col, row, *this ); }

        auto at( const Index col, const Index row ) const
            -> const Item&
        { return impl_item_at_checked( col, row, *this );  }

        auto at( const Index col, const Index row )
            -> Item&
        { return impl_item_at_checked( col, row, *this );  }

        Matrix_():
            Layout( Width{ 0 }, Height{ 0 } ),
            m_items()
        {}

        Matrix_(
            const Width     width,
            const Height    height,
            const Item&     init_value = Item()
            ):
            Layout( width, height ),
            m_items( n_items(), init_value )
        {}
    };

    template< class Item >
    inline auto item_at( const Index col, const Index row, const Matrix_<Item>& m )
        -> const Item&
    { return m( col, row ); }

    template< class Item >
    inline auto item_at( const Index col, const Index row, Matrix_<Item>& m )
        -> Item&
    { return m( col, row ); }

    template< class Item >
    inline auto item_at_checked( const Index col, const Index row, const Matrix_<Item>& m )
        -> const Item&
    { return m.at( col, row ); }

    template< class Item >
    inline auto item_at_checked( const Index col, const Index row, Matrix_<Item>& m )
        -> Item&
    { return m.at( col, row ); }

    template< class Item>
    inline auto item_at( const matrix::Position& pos, const Matrix_<Item>& m )
        -> const Item&
    { return item_at( pos.x, pos.y, m ); }

    template< class Item>
    inline auto item_at( const matrix::Position& pos, Matrix_<Item>& m )
        -> Item&
    { return item_at( pos.x, pos.y, m ); }

    template< class Item>
    inline auto item_at_checked( const matrix::Position& pos, const Matrix_<Item>& m )
        -> const Item&
    { return item_at_checked( pos.x, pos.y, m ); }

    template< class Item>
    inline auto item_at_checked( const matrix::Position& pos, Matrix_<Item>& m )
        -> Item&
    { return item_at_checked( pos.x, pos.y, m ); }

}  // namespace cppx
