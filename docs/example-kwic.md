<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Example: a KWIC-like greeting program](#example-a-kwic-like-greeting-program)
  - [1 – The ASCII-based variant.](#1--the-ascii-based-variant)
  - [1.1 – “… and one `#include` to bind them all”.](#11---and-one-include-to-bind-them-all)
  - [1.2 – An `app` namespace.](#12--an-app-namespace)
  - [1.3 – `using`-declaring names from libraries.](#13--using-declaring-names-from-libraries)
  - [1.4 – Throwing an exception via the `$fail` macro.](#14--throwing-an-exception-via-the-fail-macro)
  - [1.5 –  Using the *cppx-core* support for signed integer arithmetic.](#15---using-the-cppx-core-support-for-signed-integer-arithmetic)
  - [1.6 – Using the *cppx-core* ASCII support.](#16--using-the-cppx-core-ascii-support)
  - [1.7 – The `$items` macro.](#17--the-items-macro)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->


# Example: a KWIC-like greeting program

This example is a possible code part of an answer on a Q&A site such as Stack Overflow, or in a response in a technical discussion e.g. on Reddit.

The program (perhaps a student exercise) asks for the user's name and if that name contains one or more repeated characters it reports one that has the maximum count, as the most common character in the name, and then presents the name repeatedly but offset horizontally so that occurrences of that character line up vertically:

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
    $use_namespace_name_in( cppx, ascii );

    $use_cppx(
        enumerated, Index, is_empty, length_of, Map_, n_items_in, spaces
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
        for( const auto current: enumerated( s ) )
        {
            result[current.item].push_back( current.index );
        }
        return result;
    }

    auto nonspace_char_indices_in( const string_view& s )
        -> Char_indices
    {
        Char_indices result = char_indices_in( s );
        for( const char ch : ascii::whitespace_characters() )
        {
            result.erase( ch );
        }
        return result;
    }

    void run()
    {
        cout << ">>> The KWIC-like personal greeting program, using ASCII! <<<" << endl;
        cout << "Hi, what's your name (in lowercase & English letters only please)\n? ";
        const string username = input();

        const Char_indices  char_indices    = nonspace_char_indices_in( username );
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
~~~

## 1.1 – “… and one `#include` to bind them all”.

Code:

~~~cpp
#include <cppx-core/_all_.hpp>
~~~

This line includes everything from the library, including a guaranteed set of standard library headers.

Every folder in *cppx-core*  has an ***\_all\_.hpp*** file that includes everything in that folder and subfolders. Thus, using the top level *\_all\_.hpp* file includes everything. You can include smaller subsets by including a sub-folder's *\_all\_.hpp*, or a specific header (they're all self-sufficient, with no requirements), or at the top level you can alternatively include ***all-except-io.hpp***.

The guaranteed set of standard library headers is provided by 

~~~cpp
#include <cppx-core/stdlib-includes/basic-general.hpp>
#include <cppx-core/stdlib-includes/basic-io.hpp>
~~~

The non-i/o headers provided by *stdlib-includes/basic-general.hpp* are generally those that correspond to either C++ core langauge features, or to core language features in some other similar languages like Java and C#:

* *\<algorithm\>*, *\<array\>*, *\<atomic\>*, *\<chrono\>*, *\<deque\>*, *\<functional\>*, *\<initializer\_list\>*, *\<iosfwd\>*, *\<iterator\>*, *\<map\>*, *\<memory\>*, *\<mutex\>*, *\<numeric\>*, *\<optional\>*, *\<queue\>*, *\<random\>*, *\<set\>*, *\<stack\>*, *\<stdexcept\>*, *\<string\>*, *\<string\_view\>*, *\<thread\>*, *\<unordered_map\>*, *\<unordered\_set\>*, *\<utility\>*, *\<vector\>*.

The i/o headers provided by *stdlib-includes/basic-io.hpp* are just all the C++17 i/o headers, because there are just a few:

* *\<filesystem>*, *\<fstream>*, *\<iomanip>*, *\<iostream>*, *\<sstream>*.

Note: the *\<iostream\>* header guaranteed includes *\<ios\>*, *\<streambuf\>*, *\<istream\>* and *\<ostream\>*, so you get those too.


## 1.2 – An `app` namespace.

Code:

~~~cpp
namespace app
{
    ⋮
}  // namespace app
~~~

With *cppx-core* it's easy to `using`-declare identifiers from other namespaces, and that's best done within your own namespace, not in the global namespace.

In particular, introducing identifiers directly into the global namespace can be problematic in a header.

So, in order to keep to good programming practices that work in general, I here use an `app` namespace for everything but the `main` function.

## 1.3 – Easily make nested namespaces, directly available.

Code:

~~~cpp
    $use_namespace_name_in( cppx, ascii );
~~~

This expands to

~~~cpp
    namespace ascii = cppx::ascii;
~~~

With a longer namespace name than “`ascii`”, the **`$use_namespace_name_in`** macro invocation will in general be shorter than the expansion. You also get shorter invocation code than the expansion when you want to use two or more namespaces nested in the same namespace, in which case you can use the `$use_namespace_names_in` “plural form” macro. In any case it avoids the name repetition, i.e. it's more DRY  –  *Don't Repeat Yourself*  –  and hence less error prone.

It would be nice with direct language support for this.

This macro is provided by *cppx-core/language/syntax/macro-use.hpp*.


## 1.4 – Easily make stuff from namespaces, directly available.

Code:

~~~cpp
    $use_cppx(
        Index, is_ascii_whitespace, is_empty, length_of, Map_, n_items_in, spaces
        );
    $use_std(
        cin, cout, end, endl, getline, string, string_view, max_element, vector
        );
~~~

This expands to

~~~cpp
using cppx::Index;
using cppx::is_ascii_whitespace;
using cppx::is_empty;
using cppx::length_of;
using cppx::Map_;
using cppx::n_items_in;
using cppx::spaces;

using std::cin;
using std::cout;
using std::end;
using std::endl;
using std::getline;
using std::string;
using std::string_view;
using std::max_element;
using std::vector;
~~~

The **`$use_cppx`** macro is a more readable non-shouting alias for `CPPX_USE_CPPX`, and ditto, **`$use_std`** is a more readable non-shouting alias for `CPPX_USE_STD`. They `using`-declare the specified names, from respectively the `cppx` and `std` namespaces. The **`cppx` namespace** contains stuff from the *cppx-core* (and later also the *C++ Band Aid*) library, and the `std` namespace contains stuff from the C++ standard library.

Both macros are defined in terms of the more general `CPPX_USE_FROM_NAMESPACE`, alias **`$use_from_namespace`**, which you can use to `using`-declare names from other namespaces.

It would be nice with direct language support for this.

These macros are provided by *cppx-core/language/syntax/macro-use.hpp*.

## 1.5 – Easily throw an exception with throw point information.

Code:

~~~cpp
    auto input() -> string
    {
        string result;
        getline( cin, result )
            or $fail( "std::getline failed on std::cin" );
        return result;
    }
~~~

The simple `$fail` invocation expands, via some other macros, to

~~~cpp
    cppx::fail<std::runtime_error>(
        std::string( "std::getline failed on std::cin" ),
        ::cppx::Source_location( __FILE__, __LINE__, {}, __func__ )
        )
~~~

… except that the expansion is all on one source code line, crucial for `__LINE__`.

As shown the **`$fail`** macro uses the **`cppx::fail`** function to throw the exception. And the `cppx::fail` function has `bool` return type, though it never returns!, in order to facilitate usage like the “`… or $fail`” pattern above. When it's used within a `catch` block then the current exception is nested via the standard C++11 mechanism.

In this example there's no exception nesting, and the message can look like this (here running the program in Windows):

> `>>> The KWIC-like personal greeting program, using ASCII! <<<`  
> `Hi, what's your name (in lowercase & English letters only please)`  
> `?` ***^Z***  
>  
> <code>!&nbsp;&nbsp;&nbsp;input - std::getline failed on std::cin</code>  
> <code>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;>File "kwic-greeting.ascii.cpp" at line 19</code>  

The **`^Z`** is from typing a <kbd>Ctrl</kbd>+<kbd>Z</kbd>, which in Windows signifies end-of-text, like an end-of-file.

Fine point: in order to get straight ASCII quote characters, like **`"`**, I defined **`CPPX_USE_ASCII_PLEASE`** when I built the program. The default roundish UTF-8 encoded quote characters don't play well in an ordinary non-WSL Windows console window, even with active codepage 65001. Instead of the macro symbol definition I could have provided a custom *config.hpp* file via an include path override, or I could have edited the default one.

This functionality is at a higher level, and involving more arbitrary choices, than what can reasonably be provided by a core language feature, but it is within the remit of the standard library.

The `$fail` macro is provided by *cppx-core/failure-handling/macro-fail.hpp*.

## 1.6 –  Avoiding unsigned types for numbers.

Code:

~~~cpp
    using Char_indices = Map_<char, vector<Index>>;
~~~

When an unsigned type like `size_t` is used for numbers, the implicit conversions from signed to unsigned type can result in wrap-around to Really Large&trade; values, leading to some nasty bugs. For example, the C++ rules guarantee that `std::string("Hello").length() < -87`. Coming from some other language that's unexpected and quite counter-intuitive, the stuff that bugs are made of.

Using signed integer types for numbers helps avoid that, and also lets the compiler optimize certain constructs that it's not allowed to optimize with unsigned type. Essentially that's because with a signed type the compiler can assume that there will be no wrap-around, whereas with unsigned type the language guarantees wrap-around. I.e. signed types are not only safer but also potentially more efficient.

The *cppx-core* **`Index`** type is an alias for the standard library's `ptrdiff_t` type, i.e. it's a signed index type of maximal practical range with a self-descriptive name.

*cppx-core/language/types/signed-size-types.hpp* also provides a signed size type called **`Size`**, that's also just an alias for `ptrdiff_t`. To avoid signed/unsigned mismatch warnings these types are supported by signed result functions such as **`n_items_of`** and (for strings) **`length_of`**. Both these functions are provided by *cppx-core/collections/size-checking.hpp*.

You can think of the *cppx-core* **`Map_`** class template as an alias for `std::unordered_map`. Actually it's a derived class in order to provide the missing `[]` indexing operator for a `const` `unordered_map` object, so more precisely it's like an alias for an `unordered_map` with more uniform access notation. So, a variable of type `Char_indices` is a set of pairs, where each pair contains a `char` value and a corresponding `vector` of signed type indices.


## 1.7 – Easily access both index and item value in a range based `for`.

Code:

~~~cpp
    auto char_indices_in( const string_view& s )
        -> Char_indices
    {
        Char_indices result;
        for( const auto current: enumerated( s ) )
        {
            result[current.item].push_back( current.index );
        }
        return result;
    }
~~~

This function builds up a mapping from each `char` value in `s`, to a vector of indices where that `char` value occurs. Thus, in the loop body both a `char` item in `s`, and its index, are needed. The **`enumerated`** function makes that easy by providing a virtual collection of `Item_and_index` pairs:

~~~cpp
    using   Item        = decltype( *declval<Collection>().begin() );  // Usually a ref.

    struct Item_and_index
    {
        Item    item;
        Index   index;
    };
~~~

So, in each iteration of the range based `for ` loop above, the `current` variable is one such `Item_and_index`. Since the collection here is a `const std::string` the `Item` type is a `const char&`. Effectively that's just a `char`.

The basic idea comes from the Python language's built-in function `enumerate`, and the name `enumerated` was chosen to make that connection very clear.

One alternative is to loop over references to the `char` items and *calculate* each item's index:

~~~cpp
    auto char_indices_in( const string_view& s )
        -> Char_indices
    {
        Char_indices result;
        for( const char& ch: s )
        {
            const Index i = &ch - &s[0];
            result[ch].push_back( i );
        }
        return result;
    }
~~~

This introduces a perhaps non-obvious calculation.

Another alternative, sort of the opposite, is to loop over index values and calculate each item reference from the index:

~~~cpp
    auto char_indices_in( const string_view& s )
        -> Char_indices
    {
        Char_indices result;
        for( int i: Range( 0, length_of( s ) ) )
        {
            const char ch = s[i];
            result[ch].push_back( i );
        }
        return result;
    }
~~~

This replaces the first alternative's unusual calculation with a more common and easily understood one, just ordinary `[]` indexing.

**`Range`** is `cppx::Range`, which allows simple counting loops to be expressed as range based `for` loops. This particular usage could alternatively have been expressed as `for(int i: up_to(1+length_of(s)))`. The **`up_to`** function is just a convenience function that produces `Range`s.


## 1.8 – ASCII support.

Code:

~~~cpp
    auto nonspace_char_indices_in( const string_view& s )
        -> Char_indices
    {
        Char_indices result = char_indices_in( s );
        for( const char ch : ascii::whitespace_characters() )
        {
            result.erase( ch );
        }
        return result;
    }
~~~

The **`cppx::ascii`** namespace provides several ASCII support functions, plus names for the ASCII control characters. The `ascii::whitespace_characters` function provides a reference to a Meyers' singleton string, initialized on the first call with the ASCII characters that `::isspace` (from the C library) returns `true` for. Alternatively `ascii::is_whitespace` function could have been used in the code that creates the mapping, in `char_indices_in`, but that would not have given such a nice separation of issues to discuss here.


## 1.9 – The `$items` macro.

Code:

~~~cpp
    void run()
    {
        cout << ">>> The KWIC-like personal greeting program, using ASCII! <<<" << endl;
        cout << "Hi, what's your name (in lowercase & English letters only please)\n? ";
        const string username = input();

        const Char_indices  char_indices    = char_indices_in( username );
        const auto          it_most_common  = max_element( $items( char_indices ),
            []( auto& a, auto& b ) { return a.second.size() < b.second.size(); }
            );
~~~

As most standard library functions that deal with collections, `std::max_element` takes a pair of iterators as arguments instead of directly taking the collection or something more abstract that represents the collection.

The adoption of the *Ranges* library into the C++ standard library will address this, but for now  –  or even then, e.g. as a disambiguation technique  –  you can use the *cppx-core* **`$items`** macro.

There's a check to ensure that the argument, here `char_indices`, is not an rvalue expression, because that could have made the macro call a function twice, then possibly repeating some side effect of that function.
