# *cppx-core* – C++ Core Functionality

The *cppx-core* library primarily reduces the code needed to do some simple common things, e.g.

* including standard library headers  
  via e.g. just `#include <cppx-core/_all_.hpp>`, or more specifically via e.g. `#include <cppx-core/stdlib-includes/_all_.hpp>`, which avoids dragging in any *cppx-core* stuff;  

* `using` a larger number of identifiers  
  via e.g. `CPPX_USE_STD( cout, cerr, endl, exception );`, or  

* throwing an exception with the throwing function's name  
  via e.g. `CPPX_FAIL( "Oops!" );`, which also embeds the file name and line number in the exception message.

This code reduction will hopefully support Good Programming Practices&trade; in examples on the net, where brevity is often very important.

For those, including in particular the author himself, who abhor shouting uppercase identifiers peppered throughout the code, the library by default defines lowercase macro names with a non-standard but still supported by most every compiler `$` in front. For the two macros mentioned above those names are `$use_std` and `$fail`, and systematically ditto for all other macros. Since there is a chance that there exists some obscure compiler that doesn't support the `$`, those names are not used in the library code itself, and the definitions can be removed by defining `CPPX_NO_DOLLARS` globally in the build.

The library also provides safe and concise ways to do some common things, or things that *should be* common except that they involve too much DIY coding in bare standard C++, e.g.

* counting loops expressed with range based `for`  
  like `for( const int i: up_to( 42 ) )`;  

* unwrapping of nested exceptions  
  e.g. just `cout << description_lines_from( ex ) << endl;` to output the set of messages one per line; or  

* providing a pair of iterators to a function,  
  e.g. `sort( CPPX_ITEMS( v ) );` (with the lowercase macro name just `sort( $items( v ) );`).

The provided functionality may seem a bit arbitrary, or, well, very arbitrary: a little of X, a little of Y, none of Z that the reader is especially interested in, with little or no obvious relationship between X and Y and other things in the library. It emerged by repeatedly paring down an as yet unpublished library that I call *C++ Band Aid*, so it's a bit like the prime numbers emerging via a sieve process, *apparently* arbitrary but hanging together at a higher level. The intent of the *cppx core* micro-library is to serve as the core of the *C++ Band Aid* library, which adds more high level and more system specific things such as transparent UTF-8 support for Windows console i/o, much like my now archived *Wrapped Stdlib* library but in a Better Way&trade;.

---

Example usage:

~~~cpp
#include <cppx-core/_all_.hpp>

auto main() -> int
{
    $use_std( cout, endl );

    for( const int i : cppx::up_to( 7 ) )
    {
        cout << "Cppx Core is great, yay!" << endl;
    }
}
~~~

---

*cppx-core* provides the following headers:

~~~ txt
•
│   config.hpp
│
├───collections
│       is_empty.hpp
│       is_in.hpp
│       Range_.hpp
│       size-checking.hpp
│       Span_.hpp
│
├───failure-handling
│       Abstract_source_location.hpp
│       exception-propagation.hpp
│       exception-unwrapping.hpp
│       hopefully_and_fail.hpp
│       macro-dbginfo.hpp
│       macro-fail.hpp
│       macro-source_location.hpp
│       Source_location.hpp
│
├───io
│       debugging-output.hpp
│       monospaced_bullet_block.hpp
│
├───iterators
│       Count_iterator_.hpp
│       Forward_iterator_impl_.hpp
│
├───language
│   │
│   ├───bit-level
│   │       bits_per_.hpp
│   │       sum_of_bits.hpp
│   │
│   ├───calc
│   │       integer-operations.hpp
│   │       named-numbers.hpp
│   │       number-properties.hpp
│   │       std-calc.hpp
│   │
│   ├───parameters
│   │       In_out_ref_.hpp
│   │
│   ├───tmp
│   │       basic-Enable_if_.hpp
│   │       basic-type-traits.hpp
│   │
│   └───types
│           basic-size-checking.hpp
│           byte-types.hpp
│           signed-size-types.hpp
│           type-producers.hpp
│
├───meta-macro
│       macro-apply.hpp
│       macro-apply_with_fixed_arg.hpp
│       macro-invoke_macro.hpp
│       macro-joined.hpp
│       macro-n_arguments.hpp
│       macro-repeat.hpp
│
├───meta-template
│       Enable_if_.hpp
│       Type_list_.hpp
│
├───meta-type
│       downcasted_to_.hpp
│       is_of_derived_class_.hpp
│       No_copy.hpp
│       No_copy_or_move.hpp
│       type-traits.hpp
│
├───stdlib-includes
│       basic-general.hpp
│       basic-io.hpp
│
├───syntax
│       lvalue_ref_to.hpp
│       macro-define_tag.hpp
│       macro-items.hpp
│       macro-noreturn.hpp
│       macro-use.hpp
│       macro-with.hpp
│       type-assemblers.hpp
│
├───testing
│       boost-test-framework-with-wide-string-fix.hpp
│       boost-test-framework.hpp
│       google-test-framework.hpp
│
└───text
    │   C_str_.hpp
    │   pointers-from-string_view.hpp
    │   string-util.hpp
    │
    ├───ascii
    │       ascii-character-names.hpp
    │       ascii-fallback-symbols.hpp
    │       ascii-util.hpp
    │
    └───unicode
            assert-utf8-execution-character-set.hpp
            unicode-Code_point_generator.hpp
            utf16-from.hpp
            utf16-Generator.hpp
            utf16-n_units_for.hpp
            utf16-surrogate-pairs.hpp
            utf32-Generator.hpp
            utf8-from.hpp
            utf8-Generator.hpp
            utf8-is_the_execution_character_set.hpp
            utf8-iteration.hpp
            utf8-n_bytes_for.hpp
~~~

In addition there's an ***\_all\_.hpp*** header in every folder. Including the top level <i>\_all\_.hpp</i> header includes everything. Alternatively you can include the top-level ***all-except-io.hpp*** header, also not shown above, which includes everything except the *io* folder and the standard library's i/o headers.
