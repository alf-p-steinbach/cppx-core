// → examples/kwic-greeting/kwic-greeting.ascii.cpp
#include <cppx-core/_all_.hpp>

namespace app
{
    $use_cppx( Index, is_ascii_whitespace, is_empty, n_items_in, P_, spaces );
    $use_std( cin, cout, endl, getline, string, string_view, max_element, unordered_map );

    template< class Key, class Value >
    using Map_ = std::unordered_map<Key, Value>;

    template< class Value >
    using Sorted_set_ = std::set<Value>;

    auto input() -> string
    {
        string result;
        getline( cin, result )
            or $fail( "std::getline failed on std::cin" );
        return result;
    }

    auto code_indices_in( const string_view& sv )
        -> Map_<char, Sorted_set_<Index>>         // “ASCII code point” → “indices”
    {
        Map_<char, Sorted_set_<Index>> result;
        for( Index i = 0; i < n_items_in( sv ); ++i )
        {
            const char ch = sv[i];
            if( not is_ascii_whitespace( ch ) )
            {
                result[ch].insert( i );
            }
        }
        return result;
    }

    void run()
    {
        cout << ">>> The KWIC-like personal greeting program, for ASCII! <<<" << endl;
        cout << "Hi, what's your name (in lowercase & English letters only please)\n? ";
        const string username = input();
        
        const auto  code_indices    = code_indices_in( username );
        const auto  it_most_common  = max_element( $items( code_indices ),
            []( auto& a, auto& b ) { return a.second.size() < b.second.size(); }
            );

        cout << endl;
        if( it_most_common == end( code_indices ) )     // Username empty or all spaces.
        {
            cout << "Have a nice day!" << endl;
            return;
        }
        else if( it_most_common->second.size() == 1 )
        {
            cout << "All characters in your name are unique, " << username << "." << endl;
        }
        else
        {
            cout << "Oh hi, " << username << "! Nice to meet you!" << endl;
            const char ch = it_most_common->first;
            cout    << "The/a most common character in your name is '" << ch << "':" << endl;

            const auto& indices     = it_most_common->second;
            const Index max_index   = *max_element( $items( indices ) );
            
            cout << endl;
            for( const Index i: indices )
            {
                cout    << spaces( max_index - i )
                        << username.substr( 0, i )
                        << "|" << ch << "|"
                        << username.substr( i + 1 )
                        << endl;
            }
        }
    }
}

auto main() -> int
{
    try
    {
        app::run();
        return EXIT_SUCCESS;
    }
    catch( const std::exception& x )
    {
        $use_cppx( monospaced_bullet_block, description_lines_from );
        $use_std( cerr, endl, string );

        const string text = description_lines_from( x );
        cerr << "\n" << monospaced_bullet_block( text, "!" ) << endl;
    }
    return EXIT_FAILURE;
}
