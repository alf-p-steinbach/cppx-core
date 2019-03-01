#include <algorithm>        // std::max_element
#include <ctype.h>          // ::isspace
#include <iostream>         // std::(cin, cout, endl)
#include <iomanip>          // std::setw
#include <unordered_map>    // std::unordered_map    
#include <stdlib.h>         // EXIT_...
#include <string>           // std::(getline, string)
using namespace std;

auto main()
    -> int
{
    string username;
    unordered_map<char, int> counts;
    
    cout << ">>> The KWIC-like personal greeting program, using ASCII! <<<" << endl;
    cout << "Hi, what's your name (in lowercase & English letters only please)\n? ";
    getline( cin, username );
    if( cin.fail() )
    {
        #if defined( __unix__ ) or defined( __APPLE__ )
            if( cin.eof() ) { cout << endl; }
        #endif
        cerr << "!std::getline failed on std::cin" << endl;
        return EXIT_FAILURE;
    }

    cout << endl;
    for( const char ch: username )
    {
        if( not isspace( static_cast<unsigned char>( ch ) ) )
        {
            ++counts[ch];
        }
    }
    const auto it = max_element( counts.begin(), counts.end(),
        []( auto a, auto b ) -> bool { return a.second < b.second; }
        );
    if( it == counts.end() )     // Username empty or all spaces.
    {
        cout << "Have a nice day!" << endl;
        return EXIT_SUCCESS;
    }
    const char most_common = it->first;
    if( counts[most_common] == 1 )
    {
        cout << "All characters in your name are unique, " << username << "." << endl;
        return EXIT_SUCCESS;
    }

    cout << "Oh hi, " << username << "! Nice to meet you!" << endl;
    cout << "The/a most common character in your name is '" << most_common << "':" << endl;
    const size_t    first_index     = username.find( most_common );
    const size_t    last_index      = username.rfind( most_common );
    for( size_t i = first_index; i <= last_index; i = username.find( most_common, i + 1 ) )
    {
        cout    << setw( last_index - i ) << ""
                << username.substr( 0, i )
                << "|" << most_common << "|"
                << username.substr( i + 1 )
                << endl;
    }
    return EXIT_SUCCESS;
}
