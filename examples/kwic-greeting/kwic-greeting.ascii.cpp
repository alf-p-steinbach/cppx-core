// → examples/kwic-greeting/kwic-greeting.ascii.cpp
#include <cppx-core/_all_.hpp>

namespace app
{
    $use_cppx(
        Index, is_ascii_whitespace, is_empty, length_of, Map_, n_items_in, spaces
        );
    $use_std(
        cin, cout, end, endl, getline, string, string_view, max_element, vector
        );

    auto input() -> string
    {
        string result;
        getline( cin, result )
            or $fail( "std::getline failed on std::cin" );
        return result;
    }

    using Char_indices = Map_<char, vector<Index>>;     // “ASCII code point” → “indices”

    auto char_indices_in( const string_view& s )
        -> Char_indices
    {
        Char_indices result;
        for( Index i = 0; i < length_of( s ); ++i )
        {
            const char ch = s[i];
            if( not is_ascii_whitespace( ch ) )
            {
                result[ch].push_back( i );
            }
        }
        return result;
    }

    void run()
    {
        cout << ">>> The KWIC-like personal greeting program, using ASCII! <<<" << endl;
        cout << "Hi, what's your name (in lowercase & English letters only please)\n? ";
        const string username = input();

        const Char_indices  char_indices    = char_indices_in( username );
        const auto          it_most_common  = max_element( $items( char_indices ),
            []( auto& a, auto& b ) { return a.second.size() < b.second.size(); }
            );

        cout << endl;
        if( it_most_common == end( char_indices ) )     // Username empty or all spaces.
        {
            cout << "Have a nice day!" << endl;
            return;
        }

        const char ch       = it_most_common->first;
        const auto& indices = it_most_common->second;

        if( n_items_in( indices ) == 1 )
        {
            cout << "All characters in your name are unique, " << username << "." << endl;
            return;
        }

        cout << "Oh hi, " << username << "! Nice to meet you!" << endl;
        cout << "The/a most common character in your name is '" << ch << "':" << endl;
        cout << endl;
        const Index max_index = indices.back();
        for( const Index i: indices )
        {
            cout    << spaces( max_index - i )
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
        const string text = description_lines_from( x );
        cerr << "\n" << monospaced_bullet_block( text, "!" ) << endl;
    }
    return EXIT_FAILURE;
}
