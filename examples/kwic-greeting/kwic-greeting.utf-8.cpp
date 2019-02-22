#include <cppx-core/_all_.hpp>

namespace app
{
    $use_namespace_name_in( cppx, utf8 );
    $use_cppx( Index, is_empty, P_, spaces );
    $use_std( cin, cout, endl, getline, string, string_view, max_element, unordered_map );

    template< class Key, class Value >
    using Map_ = std::unordered_map<Key, Value>;

    template< class Value >
    using Sorted_set_ = std::set<Value>;

    auto input() -> string
    {
        string result;
        getline( cin, result )
            or $fail( "std::getline(cin,...) failed" );
        return result;
    }

    struct Utf8_index { Index i_code; Index i_byte; };  // n'th code group i_code = n - 1.
    
    auto operator<( const Utf8_index& a, const Utf8_index& b )
        -> bool
    { return a.i_code < b.i_code; }

    auto code_indices_in( const string_view& sv )
        -> Map_<string, Sorted_set_<Utf8_index>>    // “UTF-8 code point bytes” → “indices”
    {
        Map_<string, Sorted_set_<Utf8_index>> result;
        Index i = 0;
        for(    P_<const char>  p_code = sv.data(),
                                p_next_code,
                                p_beyond = p_code + sv.length();
                p_code != p_beyond;
                p_code = p_next_code )
        {
            p_next_code = utf8::next( p_code );

            const int       n_bytes     = p_next_code - p_code;
            const int       byte_index  = p_code - sv.data();
            result[string( p_code, n_bytes )].insert( Utf8_index{ i, byte_index } );
            ++i;
        }
        return result;
    }

    void run()
    {
        cout << "The KWIC-like personal greeting program!" << endl;
        cout << "Hi, what´s your name (in lowercase please)? ";
        const string username = input();
        if( is_empty( username ) )
        {
            cout << "Have a nice day!" << endl;
            return;
        }
        
        const auto  code_indices    = code_indices_in( username );
        const auto  it_most_common  = max_element( $items( code_indices ),
            []( auto& a, auto& b ) { return a.second.size() < b.second.size(); }
            );
        
        if( it_most_common->second.size() == 1 )
        {
            cout << "All characters in your name are unique, " << username << "." << endl;
        }
        else
        {
            const string_view ch = it_most_common->first;
            cout    << "The/a most common character in “" << username 
                    << "” is “" << ch << "”." << endl;

            const auto& indices     = it_most_common->second;
            const Index max_i_code  = max_element( $items( indices ),
                []( auto& a, auto& b ) { return a.i_code < b.i_code; }
                )->i_code;
            
            cout << endl;
            for( const Utf8_index& i: indices )
            {
                cout    << spaces( max_i_code - i.i_code )
                        << username.substr( 0, i.i_byte )
                        << "|" << ch << "|"
                        << username.substr( i.i_byte + ch.length() )
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
        $use_std( cerr, endl );

        cerr << "!" << monospaced_bullet_block( description_lines_from( x ) ) << endl;
    }
    return EXIT_FAILURE;
}
