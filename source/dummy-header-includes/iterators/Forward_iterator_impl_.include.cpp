#include <cppx-core/iterators/Forward_iterator_impl_.hpp>

using cppx::Truth;
namespace
{
    struct S: cppx::Forward_iterator_impl_<S, int>
    {
        void advance() {}
        friend auto operator==( S const&, S const& ) -> Truth { return true; }
    };

    const Truth  v1  = (S() != S());
    int satisfy_linker = 42;
}  // namespace <anon>
