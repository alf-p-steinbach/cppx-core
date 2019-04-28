// → examples/hello.cpp
#include <cppx-core/all.hpp>
$use_cppx( up_to, spaces );
$use_std( cout, endl );

auto main() -> int
{
    for( const int i: up_to( 7 ) )
    {
        cout << spaces( 36 - i*i ) << "cppx-core, yay!" << endl;
    }
}
