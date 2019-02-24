<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Example: a KWIC-like greeting program](#example-a-kwic-like-greeting-program)
  - [1 – The ASCII-based variant.](#1--the-ascii-based-variant)
  - [1.1 – … and one `#include` to bind them all.](#11---and-one-include-to-bind-them-all)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->


# Example: a KWIC-like greeting program

Much of the point of the *cppx-core* library is to support good programming practices that otherwise would involve too much code, in answers to people's questions on the net, and in discussions on the net. And so this example is a possible such answer's or discussion's code example. It's a more realistic use of the library than the “hello” program.

The program asks for the user's name and if that name contains one or more repeated characters it reports one that has the maximum count, as the most common character in the name, and then presents the name repeatedly but offset horizontally so that occurrences of that character line up vertically:

> `>>> The KWIC-like personal greeting program, using ASCII! <<<`  
> `Hi, what's your name (in lowercase & English letters only please)`  
> `? ` ***alfa bravo charlie***
>  
> `Oh hi, alfa bravo charlie! Nice to meet you!`  
> `The/a most common character in your name is 'a':`  
>  
> <code>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|a|lfa bravo charlie</code>  
> <code>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;alf|a| bravo charlie</code>  
> <code>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;alfa br|a|vo charlie</code>  
> <code>alfa bravo ch|a|rlie</code>  

The example interaction above is for the ASCII text encoding variant of the program. ASCII text uses only one byte per character, one `char` value per character, which gives simpler code than with the more general UTF-8 encoding. The UTF-8 based variant is slightly more complicated, and so even though I did that first here it's presented last.

By the way, “KWIC” means *key word in context*.

It was once a popular exercise for students, similar to this example, but with a key word lining up vertically instead of just a single character.

## 1 – The ASCII-based variant.

~~~cpp
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
        const Index max_index = *max_element( $items( indices ) );
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
~~~

## 1.1 – … and one `#include` to bind them all.

Code:

~~~cpp
#include <cppx-core/_all_.hpp>
~~~

This includes everything from the library, including a *guaranteed set of standard library headers*.

Every folder in *cppx-core*  has an ***\_all\_.hpp*** file that includes everything in that folder and subfolders. Thus, using the top level *\_all\_.hpp* file includes everything. You can include smaller subsets by including a sub-folder's *\_all\_.hpp*, or a specific header (they're all self-sufficient, with no requirements), or at the top level you can alternatively include ***all-except-io.hpp***.

The guaranteed set of standard library headers is provided by 

~~~cpp
#include <cppx-core/stdlib-includes/basic-general.hpp>
#include <cppx-core/stdlib-includes/basic-io.hpp>
~~~

The non-i/o headers provided by *stdlib-includes/basic-general.hpp* are generally those that correspond to either C++ core langauge features, or to core language features in some other similar languages like Java and C#:

* algorithm, array, atomic, chrono, deque, functional, initializer_list, iosfwd, iterator, map, memory, mutex, numeric, optional, queue, random, set, stack, stdexcept, string, string_view, thread, unordered_map, unordered_set, utility, vector.

The i/o headers provided by *stdlib-includes/basic-io.hpp* are just all the C++17 i/o headers, because there are just a few:

* filesystem, fstream, iomanip, iostream, sstream

Note: the *\<iostream\>* header guaranteed includes *\<ios\>*, *\<streambuf\>*, *\<istream\>* and *\<ostream\>*, so you get those too.

