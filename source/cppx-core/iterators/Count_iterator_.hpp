#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/signed-sizes.hpp>      // cppx::Size
#include <cppx-core/meta-type/No_copy.hpp>

#include <iterator>     // std::iterator_traits

namespace cppx
{
    template< class Item >
    class Count_iterator_
    {
        Size        m_count     = 0;

        struct Proxy
        {
            operator Item () const { return {}; }
            void operator=( const Item& ) {}
        };

    public:
        auto count() const noexcept
            -> Size
        { return m_count; }

        // Optimization, to be manually invoked.
        void operator+=( const int n ) noexcept
        { m_count += n; }

        auto operator*() const noexcept
            -> Proxy
        { return {}; }

        auto operator++() noexcept
            -> Count_iterator_&
        {
            ++m_count;
            return *this;
        }
    };
}  // namespace cppx

namespace std
{
    template< class Item >
    struct iterator_traits< cppx::Count_iterator_< Item > >:
        iterator_traits<Item*>
    {};
}  // namespace std
