#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core-language/syntax/declarations.hpp>                       // CPPX_USE_STD
#include <cppx-core-language/syntax/collection-util/Sequence_.hpp>          // cppx::(is_in, up_to_)
#include <cppx-core-language/syntax/flow-control/x-throwing.hpp>            // CPPX_FAIL_
#include <cppx-core-language/types/system-dependent/size-types.hpp>         // cppx::(Size, Index)
#include <cppx-core-language/syntax/string-expressions.hpp>                 // cppx::operator<<
#include <cppx-core/meta-type/collection-traits.hpp>                        // cppx::Item_for_collection_

#include <vector>       // std::vector
#include <stdexcept>    // std::out_of_range
#include <utility>      // std::move

namespace cppx
{
    CPPX_USE_STD( move, out_of_range, vector );

    namespace matrix {
        struct Width        { Size value; };
        struct Height       { Size value; };
        struct Position     { Size x; Size y; };

        struct Basic_types
        {
            using Width         = matrix::Width;
            using Height        = matrix::Height;
            using Position      = matrix::Position;
        };

        class Abstract_layout:
            public Basic_types
        {
            Size                m_width;
            Size                m_height;

        protected:
            auto operator=( const Abstract_layout& other ) -> Abstract_layout& = default;
            auto operator=( Abstract_layout&& ) -> Abstract_layout& = default;

            Abstract_layout( const Abstract_layout& other ) = default;
            Abstract_layout( Abstract_layout&& other ) = default;

            constexpr Abstract_layout(): m_width( 0 ), m_height( 0 ) {}

            constexpr Abstract_layout( const Width width, const Height height ):
                m_width( width.value ),
                m_height( height.value )
            {}

        public:
            constexpr auto width() const  -> Size   { return m_width; }
            constexpr auto height() const -> Size   { return m_height; }
            constexpr auto n_items() const -> Size  { return m_width*m_height; }

            constexpr auto index_of( const Index col, const Index row ) const
                -> Index
            { return row*m_width + col; }

            constexpr auto col_of( const Index i ) const
                -> Index
            { return i % m_width; }

            constexpr auto row_of( const Index i ) const
                -> Index
            { return i / m_width; }

            constexpr auto index_of( const Position& pos ) const
                -> Index
            { return index_of( pos.x, pos.y ); }

            constexpr auto position_of_index( const Index i ) const
                -> Position
            { return Position{ col_of( i ), row_of( i ) }; }
        };

        class Layout:
            public Abstract_layout
        {
        public:
            auto operator=( const Layout& other ) -> Layout& = default;
            auto operator=( Layout&& ) -> Layout& = default;

            constexpr Layout() = default;
            constexpr Layout( const Width width, const Height height ):
                Abstract_layout( width, height )
            {}

            Layout( Layout& other ) = default;
            Layout( Layout&& other ) = default;
        };
    }  // namespace matrix

    template< class Item_param >
    class Abstract_matrix_:
        public matrix::Abstract_layout
    {
    public:
        using Item = Item_param;

    private:
        vector<Item>        m_items;

        template< class Self >
        static auto impl_item_at( const Index col, const Index row, Self& self )
            -> Item_for_collection_<Self>&
        { return self.m_items[self.index_of( col, row )]; }

        template< class Self >
        static auto impl_item_at_checked( const Index col, const Index row, Self& self )
            -> Item_for_collection_<Self>&
        {
            hopefully(  is_in( zero_to( self.m_width ), col ) and
                        is_in( zero_to( self.m_height ), row )
                ) or CPPX_FAIL_( out_of_range,
                    "Item position ("s << col << "," << row << ") is out of range"
            );
            return self.m_items[self.index_of( col, row )];
        }

    protected:
        Abstract_matrix_():
            Abstract_layout( Width{ 0 }, Height{ 0 } ),
            m_items()
        {}

        Abstract_matrix_(
            const Width     width,
            const Height    height,
            const Item&     init_value = Item()
            ):
            Abstract_layout( width, height ),
            m_items( n_items(), init_value )
        {}

        Abstract_matrix_( const Abstract_matrix_& other ) = default;
        Abstract_matrix_( Abstract_matrix_&& other ) = default;

        auto operator=( const Abstract_matrix_& other ) -> Abstract_matrix_& = default;
        auto operator=( Abstract_matrix_&& other ) -> Abstract_matrix_& = default;

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
    };

    template< class Item >
    inline auto item_at(
        const Index col, const Index row, const Abstract_matrix_<Item>& m
        ) -> const Item&
    { return m( col, row ); }

    template< class Item >
    inline auto item_at(
        const Index col, const Index row, Abstract_matrix_<Item>& m
        ) -> Item&
    { return m( col, row ); }

    template< class Item >
    inline auto item_at_checked(
        const Index col, const Index row, const Abstract_matrix_<Item>& m
        ) -> const Item&
    { return m.at( col, row ); }

    template< class Item >
    inline auto item_at_checked(
        const Index col, const Index row, Abstract_matrix_<Item>& m
        ) -> Item&
    { return m.at( col, row ); }

    template< class Item>
    inline auto item_at(
        const matrix::Position& pos, const Abstract_matrix_<Item>& m
        ) -> const Item&
    { return item_at( pos.x, pos.y, m ); }

    template< class Item>
    inline auto item_at(
        const matrix::Position& pos, Abstract_matrix_<Item>& m
        ) -> Item&
    { return item_at( pos.x, pos.y, m ); }

    template< class Item>
    inline auto item_at_checked(
        const matrix::Position& pos, const Abstract_matrix_<Item>& m
        ) -> const Item&
    { return item_at_checked( pos.x, pos.y, m ); }

    template< class Item>
    inline auto item_at_checked(
        const matrix::Position& pos, Abstract_matrix_<Item>& m
        ) -> Item&
    { return item_at_checked( pos.x, pos.y, m ); }

    template< class Item_param, Size w, Size h >
    class Fixed_size_matrix_:
        public Abstract_matrix_<Item_param>
    {
        using AM_base = Abstract_matrix_<Item_param>;

    public:
        using Item = typename AM_base::Item;    // Alias Item_param.

        static constexpr matrix::Layout layout = matrix::Layout(
            matrix::Width{ w },
            matrix::Height{ h }
        );

        auto operator=( const Fixed_size_matrix_& other )
            -> Fixed_size_matrix_&
        {
            static_cast<AM_base&>( *this ) = other;
            return *this;
        }

        auto operator=( Fixed_size_matrix_&& other )
            -> Fixed_size_matrix_&
        {
            static_cast<AM_base&>( *this ) = move( other );
            return *this;
        }

        Fixed_size_matrix_( const Item& init_value = Item() ):
            AM_base( matrix::Width{ w }, matrix::Height{ h }, init_value )
        {}

        Fixed_size_matrix_( const Fixed_size_matrix_& other ):
            AM_base( other )
        {}

        Fixed_size_matrix_( Fixed_size_matrix_&& other ):
            AM_base( move( other ) )
        {}
    };

    template< class Item_param, Size size_param >
    class Square_matrix_:
        public Fixed_size_matrix_<Item_param, size_param, size_param>
    {
        using FSM_base = Fixed_size_matrix_<Item_param, size_param, size_param>;

    public:
        static constexpr Size matrix_size = size_param;

        auto operator=( const Square_matrix_& other ) -> Square_matrix_&    = default;
        auto operator=( Square_matrix_&& other ) -> Square_matrix_&         = default;
        using FSM_base::Fixed_size_matrix_;     // General constructors.
        Square_matrix_( const Square_matrix_& )                             = default;
        Square_matrix_( Square_matrix_&& )                                  = default;
    };

    template< class Item_param >
    class Matrix_:
        public Abstract_matrix_<Item_param>
    {
        using AM_base = Abstract_matrix_<Item_param>;

    public:
        using Item = typename AM_base::Item;    // Alias Item_param.

        auto operator=( const Matrix_& other ) -> Matrix_&                  = default;
        auto operator=( Matrix_&& other ) -> Matrix_&                       = default;
        using AM_base::Abstract_matrix_;        // General constructors.
        Matrix_( const Matrix_& )                                           = default;
        Matrix_( Matrix_&& )                                                = default;

        template< Size w, Size h >
        auto operator=( const Fixed_size_matrix_<Item, w, h>& other )
            -> Matrix_&
        {
            static_cast<AM_base&>( *this ) = other;
            return *this;
        }

        template< Size w, Size h >
        auto operator=( Fixed_size_matrix_<Item, w, h>&& other )
            -> Matrix_&
        {
            static_cast<AM_base&>( *this ) = move( other );
            return *this;
        }

        template< Size w, Size h >
        Matrix_( const Fixed_size_matrix_<Item, w, h>& other ):
            AM_base( other )
        {}

        template< Size w, Size h >
        Matrix_( Fixed_size_matrix_<Item, w, h>&& other ):
            AM_base( move( other ) )
        {}
    };

}  // namespace cppx
