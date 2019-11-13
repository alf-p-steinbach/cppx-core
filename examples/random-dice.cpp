#include <cppx-core/all.hpp>

auto main()
    -> int
{
    $use_std( cout, endl );
    $use_cppx( Random, repeat_times );
    
    auto die = Random::Integers( 6 );
    repeat_times( 12, [&]{
        cout << die.next() + 1 << ' ';
        } );
    cout << endl;
}
