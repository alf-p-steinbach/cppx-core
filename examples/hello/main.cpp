#include <cppx-core/_all_.hpp>

auto main() -> int
{
    $use_std( cout, endl );

    for( const int i : cppx::up_to( 7 ) )
    {
        cout << "Cppx Core is great, yay!" << endl;
    }
}
