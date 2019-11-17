<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Example: a KWIC-like ASCII based greeting program.](#example-a-kwic-like-ascii-based-greeting-program)
  - [1 – The complete code.](#1--the-complete-code)
  - [2 – “… one `#include` to bind them all”.](#2---one-include-to-bind-them-all)
  - [3 – An `app` namespace.](#3--an-app-namespace)
  - [4 – Easily make stuff from namespaces, directly available.](#4--easily-make-stuff-from-namespaces-directly-available)
  - [5 – Easily also make nested namespaces directly available.](#5--easily-also-make-nested-namespaces-directly-available)
  - [6 – Easily throw an exception with throw point information.](#6--easily-throw-an-exception-with-throw-point-information)
  - [7 –  Collection wrappers for clarity & more complete functionality.](#7---collection-wrappers-for-clarity--more-complete-functionality)
  - [8 – ASCII support.](#8--ascii-support)
  - [9 – Easily pass `begin`/`end` pairs with the `$items` macro.](#9--easily-pass-beginend-pairs-with-the-items-macro)
  - [10 –  With slight effort, avoid unsigned types for numbers.](#10---with-slight-effort-avoid-unsigned-types-for-numbers)
  - [11 – Easily display the messages of nested exceptions.](#11--easily-display-the-messages-of-nested-exceptions)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->


# Example: a KWIC-like ASCII based greeting program.

This example could have been a code part of an answer on a Q&A site such as Stack Overflow, or in a response in a technical discussion e.g. on Reddit.

The program (perhaps a student exercise) asks for the user's name and if that name contains one or more repeated characters it reports one that has the maximum count, as the most common character in the name, and then presents the name repeatedly but offset horizontally so that occurrences of that character line up vertically:

> `>>> The KWIC-like personal greeting program, using ASCII! <<<`  
> `Hi, what's your name (in lowercase & English letters only please)`  
> `? ` ***alfa bravo charlie delta***
>  
> `Oh hi, alfa bravo charlie delta! Nice to meet you!`  
> `The/a most common character in your name is 'a':`  
>  
> <code>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|a|lfa bravo charlie delta</code>  
> <code>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;alf|a| bravo charlie delta</code>  
> <code>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;alfa br|a|vo charlie delta</code>  
> <code>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;alfa bravo ch|a|rlie delta</code>  
> <code>alfa bravo charlie delt|a|</code>   

The interaction above is for the ASCII text encoding variant of the program. ASCII text uses only one byte per character, one `char` value per character, which gives simpler code than with the more general UTF-8 encoding. The UTF-8 based variant (not discussed here) is therefore slightly more complicated.

By the way, “KWIC” means *key word in context*.

KWIC was once a popular exercise for students, similar to this example, but with key words lining up vertically instead of just a single character. With just a *letter in context* it's more of a KWIC-like LIC. In both cases it's something *lined up vertically*, LUV.

## 1 – The complete code.

~~~cpp
// → examples/kwic-greeting/kwic-greeting.ascii.cpp
#include <cppx-core/_all_.hpp>

namespace app
{
    $use_cppx( Index, Map_, spaces );
    $use_std( cin, cout, end, endl, getline, string, string_view, max_element );

    $use_namespace_name_in( cppx, ascii );

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
        const auto          it_most_common  = max_element(
            $items( counts ),
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
    $use_std( cerr, cin, cout, endl, exception, string );

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
~~~

## 2 – “… one `#include` to bind them all”.

Code:

~~~cpp
#include <cppx-core/_all_.hpp>
~~~

This line includes everything from the library, including a guaranteed set of standard library headers.

Every folder in *cppx-core*  has an ***\_all\_.hpp*** file that includes everything in that folder and subfolders. Thus, using the top level *\_all\_.hpp* file includes everything. You can include smaller subsets by including a sub-folder's *\_all\_.hpp*, or a specific header (they're all self-sufficient, with no requirements), or at the top level you can alternatively include ***all-except-io.hpp***.

The guaranteed set of standard library headers is provided by 

~~~cpp
#include <cppx-core/stdlib-includes/general.hpp>
#include <cppx-core/stdlib-includes/io.hpp>
~~~

The non-i/o headers provided by *cppx-core/stdlib-includes/general.hpp* are generally those that correspond to either C++ core language features, or to core language features in some other similar languages like Java and C#:

* *\<algorithm\>*, *\<array\>*, *\<atomic\>*, *\<chrono\>*, *\<deque\>*, *\<functional\>*, *\<initializer\_list\>*, *\<iosfwd\>*, *\<iterator\>*, *\<map\>*, *\<memory\>*, *\<mutex\>*, *\<numeric\>*, *\<optional\>*, *\<queue\>*, *\<random\>*, *\<set\>*, *\<stack\>*, *\<stdexcept\>*, *\<string\>*, *\<string\_view\>*, *\<thread\>*, *\<unordered_map\>*, *\<unordered\_set\>*, *\<utility\>*, *\<variant\>*, *\<vector\>*.

The i/o headers provided by *cppx-core/stdlib-includes/io.hpp* are just all the C++17 i/o headers, because there are just a few:

* *\<filesystem>*, *\<fstream>*, *\<iomanip>*, *\<iostream>*, *\<sstream>*.

Note: the *\<iostream\>* header guaranteed includes *\<ios\>*, *\<streambuf\>*, *\<istream\>* and *\<ostream\>*, so you get those too.


## 3 – An `app` namespace.

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

## 4 – Easily make stuff from namespaces, directly available.

Code:

~~~cpp
    $use_cppx( Index, Map_, spaces );
    $use_std( cin, cout, end, endl, getline, string, string_view, max_element );
~~~

This expands to

~~~cpp
using cppx::Index;
using cppx::Map_;
using cppx::spaces;
using std::cin;
using std::cout;
using std::end;
using std::endl;
using std::getline;
using std::string;
using std::string_view;
using std::max_element;
~~~

The **`$use_cppx`** macro is an alias for `CPPX_USE_CPPX`, and ditto, **`$use_std`** is an alias for `CPPX_USE_STD`. They `using`-declare the specified names, from respectively the `cppx` and `std` namespaces. The **`cppx`** namespace contains stuff from the *cppx-core* library, but it's a cross-library namespace: it's also used for stuff in the *C++ Band Aid* library.

Both macros are defined in terms of the more general `CPPX_USE_FROM_NAMESPACE`, alias **`$use_from_namespace`**, which you can use to `using`-declare names from other namespaces.

These macros are provided by *cppx-core-language/syntax/macro-use.hpp*.


## 5 – Easily also make nested namespaces directly available.

Code:

~~~cpp
    $use_namespace_name_in( cppx, ascii );
~~~

This expands to

~~~cpp
    namespace ascii = cppx::ascii;
~~~

The **`$use_namespace_name_in`** macro has a corresponding “plural form” macro **`$use_namespace_names_in`** for when you want to use two or more nested namespaces from the same namespace. 

I'm sorry, the names are verbose. The plural form can still save typing, but one doesn't often need to refer unqualified to multiple nested namespaces… So, this notation is more about avoiding the name repetition in the expansion; it's a more DRY notation  –  *Don't Repeat Yourself*.

Like `$use_cppx`, `$use_std` and `$use_from_namespace`, the `$use_namespace_name_in` and `$use_namespace_names_in` macros are provided by *cppx-core-language/syntax/macro-use.hpp*.


## 6 – Easily throw an exception with throw point information.

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

The **`$fail`** macro uses the **`fail`** function to throw the exception; the simple `$fail` invocation expands, via some other macros, to

~~~cpp
    ::cppx::fail<std::runtime_error>(
        std::string( "std::getline failed on std::cin" ),
        ::cppx::Source_location( __FILE__, __LINE__, {}, __func__ )
        )
~~~

… except that the expansion is all on one source code line, crucial for `__LINE__`.

Though it never returns the `fail` function has `bool` return type, in order to facilitate usage like the “`… or $fail`” pattern above. When there is a `std::current_exception()`, then that current exception is nested in the thrown one via the standard C++11 mechanism. *cppx-core* supports accessing the nested messages in a simple way via `call_with_description_lines_from`, or more directly via `description_lines_from`.

In this example there's no exception nesting, and the message can look like this:

> <code>input - std::getline failed on std::cin</code>  
> <code>&nbsp;&nbsp;&nbsp;&nbsp;>File "kwic-greeting.ascii.cpp" at line 19</code>  

In practice this only happens when the user specifies *end of file* for the standard input stream.

Fine point: in order to get straight ASCII quote characters, like **`"`**, I defined **`CPPX_ASCII_PLEASE`** when I built the program. The default roundish UTF-8 encoded quote characters don't play well in an ordinary non-WSL Windows console window, even with active codepage 65001. Instead of the macro symbol definition I could have provided a custom *config.hpp* file via an include path override, or I could have edited the default one.

This macro and its cast of support functions are all provided by headers in the *cppx-core/failure-handling/* folder, e.g. *cppx-core/failure-handling/macro-fail.hpp*.

## 7 –  Collection wrappers for clarity & more complete functionality.

Code:

~~~cpp
    using Char_counts = Map_<char, int>;    // “ASCII code point” → “count”
~~~

You can think of the *cppx-core* **`Map_`** class template as an alias for `std::unordered_map`. Actually it's a derived class in order to provide the missing `[]` indexing operator for a `const` `unordered_map` object, so more precisely it's like an alias for an `unordered_map` with more uniform access notation. So, a variable of type `Char_counts` is a set of pairs, where each pair contains a `char` value and a corresponding count.

`Map_` has a sibling type **`Sorted_map`**, that you can think of as an alias for `std::map`. In the standard library the type that reasonably is the default kind of map, `std::unordered_map`, has the longest and less readable name. That's because it wasn't added until C++11, but the *cppx-core* names `Map` and `Sorted_map` let you use the shortest and most clear name for the most commonly used kind of map.

Similarly to the `Map` and `Sorted_map` pair, there is **`Set`** and **`Sorted_set`**. While the map types are only supported by one convenience function, **`is_in`**, the set types have a host of support functions. For example, there is **`set_difference`**, the same *name* as the standard library's `std::set_difference`, but with the crucial difference that `cppx::set_difference` can be applied to `std::set`s (or `cppx::Set`s). Why the standard library's set operations don't support the standard library's set types, is a perplexing mystery, growing with each new version of the standard. But *cppx-core* fixes that.

These types and functions are all provided by headers in the *cppx-core/collections/* folder, e.g. *cppx-core/collections/Map_.hpp*.


## 8 – ASCII support.

Code:

~~~cpp
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
~~~

The **`cppx::ascii`** namespace provides a number of ASCII support functions, e.g. **`ascii::is_whitespace`**, plus names of practically useful ASCII control characters, e.g. **`ascii::escape`** (which is defined as `'\x1B'`).

The standard library provides the `::isspace` function from the C standard library, but this function has Undefined Behavior if it's passed a negative value other than `EOF`, such as a directly passed non-ASCII `char`. The `cppx::ascii::is_whitespace` function is more safe: it can be called with any `char` value. Also it's more reliable in that it will always return `false` for non-ASCII values, regardless of the C level locale.

The standard library also provides a `std::isspace` function overload that takes a `char` and a `std::locale` as arguments. That doesn't suffer from the correctness problems of `::isspace`, but is less efficient and gives more contorted calling code. And likewise for other `cppx::ascii` functions: it's not functionality that's entirely missing in the standard library, but functionality where the standard library, for historical reasons, namely the C++ roots in 1970's C and the generalization of iostreams in the 1990s, makes the calling code brittle, or unclear, or inefficient.

These functions and control character names are all provided by headers in the *cppx-core/text/ascii/* folder, mainly *cppx-core/text/ascii/ascii-util.hpp*.


## 9 – Easily pass `begin`/`end` pairs with the `$items` macro.

Code:

~~~cpp
    void run()
    {
        cout << ">>> The KWIC-like personal greeting program, using ASCII! <<<" << endl;
        cout << "Hi, what's your name (in lowercase & English letters only please)\n? ";
        const string username = input();
        cout << endl;

        const Char_counts   counts          = nonspace_char_counts_in( username );
        const auto          it_most_common  = max_element(
            $items( counts ),
            []( auto a, auto b ) { return a.second < b.second; }
            );
~~~

As most standard library functions that deal with collections, `std::max_element` takes a pair of iterators as arguments instead of directly taking the collection or something more abstract that represents the collection.

The adoption of the [*Ranges* library](https://github.com/ericniebler/range-v3) into the C++ standard library will address this, but for now  –  or even then, e.g. as a disambiguation technique  –  you can use the *cppx-core* **`$items`** macro.

There's a check to ensure that the argument, here `counts`, is not an rvalue expression, because that could have made the macro call a function twice, then possibly repeating some side effect of that function.

The `$items` macro is provided by *cppx-core-language/syntax/macro-items.hpp*.


## 10 –  With slight effort, avoid unsigned types for numbers.

Code:

~~~cpp
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
~~~

When an unsigned type like `size_t` is used for numbers, the implicit conversions from signed to unsigned type can result in wrap-around to Really Large&trade; values, leading to some nasty bugs. For example, the C++ rules guarantee that `std::string("Hello").length() < -87`. Coming from some other language that's unexpected and quite counter-intuitive, the stuff that epic bugs are made of. Laugh or cry? Cry, definitely.

Using signed integer types for numbers helps avoid that, and also lets the compiler optimize certain constructs that it's not allowed to optimize with unsigned type. That's because with a signed type the compiler can assume that there will be no wrap-around, whereas with unsigned type the language guarantees wrap-around. I.e. signed types are not only safer but also potentially more efficient.

Consequently *cppx-core* provides an **`Index`** type as an alias for `std::make_signed_t<size_t>`, i.e. it's a signed index type of maximal practical range with a short self-descriptive name.

It's not defined as just an alias for `ptrdiff_t` (the type of a pointer difference) because to be most practical it needs to be the exact same size as `size_t`. And the C++ standard doesn't guarantee that `ptrdiff_t` is the same size as `size_t`.  On the contrary, for a 16-bit system it requires that `ptrdiff_t` is at least 17 bits (!), while `size_t` can be just 16 bits.

Now, with the default allocator the size type of a `std::string`, a `std::vector` or whatever, is `size_t`. And e.g. `std::string::npos` is defined as `size_t(-1)`, the maximum `size_t` value. But crucially, since it results from casting `-1` to `size_t`, converting it back to a signed type that's not larger than `size_t`, must in practice result in the original `-1`. Hence in the loop above the continuation condition is `i >= 0`. With a `size_t` loop variable the condition would instead be the more verbose `i != string::npos`, or, using the fact that `string::npos` is a large value, `i <= last_index`.

So, ***how to express a loop condition*** can depend crucially on whether the loop variable is of a signed or unsigned type. With the signed `Index` type you can get simple conditions as above, and you can avoid wrap-around problems. But using `Index` doesn't remove all the dangers: coding as if it were an unsigned type can yield bugs.

*cppx-core-language/system/size-types.hpp* also provides a signed size type called **`Size`**, that's an alias for `Index`. To avoid signed/unsigned mismatch warnings these types are supported by signed result functions such as **`n_items_of`** and (for strings) **`length_of`**. Both these functions are provided by *cppx-core/collections/size-checking.hpp*.


## 11 – Easily display the messages of nested exceptions.

Code:

~~~cpp
auto main() -> int
{
    $use_cppx( description_lines_from, monospaced_bullet_block );
    $use_std( cerr, cin, cout, endl, exception, string );

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
~~~

Since in this program no nested exceptions are thrown, the result of **`description_lines_from`**`(x)` is the same as `x.what()` produces. So, I used `description_lines_from` mainly just to be able to explain it. For a nested exception `x.what()` produces only the top level exception's text, whereas `description_lines_from` adds the nested exceptions' messages as additional lines.

The **`monospaced_bullet_block`** function indents the lines, by default with 4 spaces, and places the specified symbol text at the start of the first line, so that this program's possible exception message

> <code>input - std::getline failed on std::cin</code>  
> <code>&nbsp;&nbsp;&nbsp;&nbsp;>File "kwic-greeting.ascii.cpp" at line 19</code>  

is presented as the block

> <code>!&nbsp;&nbsp;&nbsp;input - std::getline failed on std::cin</code>  
> <code>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;>File "kwic-greeting.ascii.cpp" at line 19</code>  

The purpose of the symbol, here **`!`**, is to identify each top level exception in a sequence of exception message presentations, plus to identify the exception message presentation as such when it follows ordinary output.

`description_lines_from` is implemented in terms of **`call_with_description_lines_from`**, which delves recursively into the nested exceptions by throwing and catching them:

~~~cpp
    inline void call_with_description_lines_from(
        const exception&                            x,
        const function<void( const C_str )>&        f
        )
    {
        f( x.what() );
        try
        {
            rethrow_if_nested( x );
        }
        catch( const exception& rx )
        {
            call_with_description_lines_from( rx, f );
        }
        catch( ... )
        {
            f( "<a non-standard exception>" );
        }
    }

    inline auto description_lines_from( const exception& x )
        -> string
    {
        string result;
        const auto add = [&]( const C_str s ) -> void
        {
            if( not is_empty( result ) )
            {
                result += '\n';
            }
            result += s;
        };
        call_with_description_lines_from( x, add );
        return result;
    }
~~~

Here `C_str` is a name for the `char const*`  type, and `rethrow_if_nested` is a function from the C++ standard library, that rethrows the directly nested exception, if any.

By the way, as the code so far has exemplified my preferred convention for where to place `const` is as **prefix `const`**. And to enable “*always prefix `const`*” coding the *cppx-core* library provides a *type builder* called **`P_`** so that e.g. backwards `char const* const s` (the directly expressed formal parameter of the `add` lambda above) can be specified as forward reading direction `const P_<const char> s`. This type builder works fine with template argument deduction; e.g. in a formal parameter type `P_<Some_type>` where `Some_type` is a template parameter, the `Some_type` can be deduced.

For some time I experimented with a ditto notation for references, but in the end I found that it didn't really provide any advantage. But `P_` does, in particular because, unlike references, it makes sense to declare a pointer itself as `const`. And also because one can have pointers to pointers with possible `const`-ness at each level, and because in a `for` loop one may want to declare two or more pointers in the loop head.

Both the above functions are provided by *cppx-core/failure-handling/exception-unwrapping.hpp*. The `monospaced_bullet_block` function is provided by *cppx-core/io/monospaced_bullet_block.hpp*. The `P_` type builder and others that also are sufficiently basic to support template argument deduction, are provided by *cppx-core-language/syntax/type-builders.hpp*.
