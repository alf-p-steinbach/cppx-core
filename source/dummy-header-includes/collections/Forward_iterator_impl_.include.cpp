#include <cppx-core/collections/Forward_iterator_impl_.hpp>

namespace
{
    struct S: cppx::Forward_iterator_impl_<S, int>
    {
        void advance() {}
        friend auto operator==( S const&, S const& ) -> bool { return true; }
    };

    const bool  v1  = (S() != S());
    int satisfy_linker = 42;
}  // namespace <anon>
