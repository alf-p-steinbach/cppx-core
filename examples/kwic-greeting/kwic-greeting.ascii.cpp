// → examples/kwic-greeting/kwic-greeting.ascii.cpp
#include <cppx-core/_all_.hpp>

namespace app
{
    $use_namespace_name_in( cppx, ascii );

    $use_cppx( Index, is_empty, length_of, Map_, n_items_in, spaces );
    $use_std( cin, cout, end, endl, getline, string, string_view, max_element, vector );

    auto input() -> string
    {
        string result;
        getline( cin, result )
            or $fail( "std::getline failed on std::cin" );
        return result;
    }

    using Char_counts = Map_<char, int>;    // “ASCII code point” → “count”

    auto nonspace_char_counts_in( const string_view& s )
        -> Char_counts
    {
        Char_counts result;
        for( const char ch: s )
        {
            if( not ascii::is_whitespace( ch ) )
            {
                ++result[ch];
            }
        }
        return result;
    }

    void run()
    {
        cout << ">>> The KWIC-like personal greeting program, using ASCII! <<<" << endl;
        cout << "Hi, what's your name (in lowercase & English letters only please)\n? ";
        const string username = input();
        cout << endl;

        const Char_counts   counts          = nonspace_char_counts_in( username );
        const auto          it_most_common  = max_element( $items( counts ),
            []( auto a, auto b ) { return a.second < b.second; }
            );

        if( it_most_common == end( counts ) )   // Username empty or all spaces.
        {
            cout << "Have a nice day!" << endl;
            return;
        }

        const char ch  = it_most_common->first;
        if( counts[ch] == 1 )
        {
            cout << "All characters in your name are unique, " << username << "." << endl;
            return;
        }

        cout << "Oh hi, " << username << "! Nice to meet you!" << endl;
        cout << "The/a most common character in your name is '" << ch << "':" << endl;
        cout << endl;
        const Index     first_index     = username.find( ch );
        const Index     last_index      = username.rfind( ch );
        for( Index i = first_index; i >= 0; i = username.find( ch, i + 1 ) )
        {
            cout    << spaces( last_index - i )
                    << username.substr( 0, i )
                    << "|" << ch << "|"
                    << username.substr( i + 1 )
                    << endl;
        }
    }
}  // namespace app

auto main() -> int
{
    $use_cppx( description_lines_from, monospaced_bullet_block );
    $use_std( cerr, endl, exception, string );

    try
    {
        app::run();
        return EXIT_SUCCESS;
    }
    catch( const exception& x )
    {
        #if defined( __unix__ ) or defined( __APPLE__ )
            if( cin.eof() ) { cout << endl; }
        #endif
        const string text = description_lines_from( x );
        cerr << monospaced_bullet_block( text, "!" ) << endl;
    }
    return EXIT_FAILURE;
}
