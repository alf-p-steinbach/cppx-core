# *cppx-core* – C++ Core Functionality

The *cppx-core* C++17 header library reduces the code needed to do some simple common things, e.g. including standard library headers, `using`-declaring a larger number of identifiers from a namespace, or throwing an exception with the throwing function's name in the message.

This code reduction will hopefully support Good Programming Practices&trade; in examples on the net, where brevity is often very important.

Example *cppx-core* usage (a larger example is [also available](example-kwic.md)):

~~~cpp
// → examples/hello.cpp
#include <cppx-core/_all_.hpp>
$use_cppx( up_to, spaces );
$use_std( cout, endl );

auto main() -> int
{
    for( const int i: up_to( 7 ) )
    {
        cout << spaces( 36 - i*i ) << "Cppx Core is great, yay!" << endl;
    }
}
~~~

~~~txt
                                    Cppx Core is great, yay!
                                   Cppx Core is great, yay!
                                Cppx Core is great, yay!
                           Cppx Core is great, yay!
                    Cppx Core is great, yay!
           Cppx Core is great, yay!
Cppx Core is great, yay!
~~~
<div></div>

---

Some things such as `using`-declaring a list of identifiers from some namespace, is necessarily done via macros. For example, `CPPX_USE_STD(cout, endl);`. By default the library defines corresponding lowercase macro names with just a `$` as prefix. For example, `$use_std(cout, endl);`, and systematically ditto for all other macros. The `$` is non-standard but is still supported by most every compiler. However, there is a chance that there exists some compiler that doesn't support the `$`, and consequently those more readable names are not used in the library code itself, and the `$`-name definitions can be removed by defining `CPPX_NO_DOLLARS_PLEASE` globally in the build.

The library also provides safe and concise ways to do some things that *would be* common except that they involve too much DIY coding in bare standard C++. For example, a counting loop can be expressed like `for(const int i: up_to(42))`; unwrapping the messages of nested exceptions like `cout << description_lines_from(ex) << endl;`; and providing a pair of iterators to a function,  like (using the lowercase macro name) `sort($items(v));`. The last one isn't *entirely* safe: the macro only excludes function value results and other rvalue expressions as arguments, so an lvalue expression with side effects can wreak some havoc, as with any macro, but I feel it's worth it.

Third, the library provides a *unified readable notation* for some common tasks. For example, consider checking whether a C string is empty, `!*s`, versus checking whether a `std::vector<int>` is empty, `v.empty()`, versus checking whether a `std::valarray<int>` is empty, `va.size() == 0`. You can write the same *cppx-core* expression in all cases, namely `is_empty(s)`, `is_empty(v)` and `is_empty(va)`. The implemention for the last case is not a specialization for `std::valarray` that calls `va.size()`, but the general default when the container lacks an `empty`-method, namely the check `std::begin(va) == std::end(va)`. Unified notation like `is_empty` gives more readable and clear code and supports template code that treats different types in the same way.

---

Dependency: the [*C header wrappers*](https://github.com/alf-p-steinbach/C-header-wrappers) nano-library, that provides headers like *\<c/stdlib.hpp\>*.

The *cppx-core* functionality emerged by repeatedly paring down an as yet unpublished library that I call *C++ Band Aid*. Well, also a adding a few things to make it more useful on its own. Still it's a bit like the prime numbers emerging via a sieve process: *apparently* it's arbitrary with inexplicable large holes here & there, but it hangs together and makes sense at a higher level. The intent is for the *cppx core* micro-library to serve as the core of the refactored *C++ Band Aid* library. The *C++ Band Aid* library adds more high level and more system specific things such as transparent UTF-8 support for Windows console i/o and command line arguments, and a common opt-in startup function with exception reporting, much like my now archived *Wrapped Stdlib* library but in a Better Way&trade;.

*cppx-core* provides the following headers:

~~~ txt
•
│   config.hpp
│   
├───collections
│       Enumerated_.hpp
│       is_empty.hpp
│       is_in.hpp
│       Map_.hpp
│       Range_.hpp
│       Set_.hpp
│       size-checking.hpp
│       Sorted_map_.hpp
│       Sorted_set_.hpp
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
│   │       number-type-properties.hpp
│   │       std-calc.hpp
│   │       
│   ├───syntax
│   │       lvalue_ref_to.hpp
│   │       macro-define_tag.hpp
│   │       macro-items.hpp
│   │       macro-noreturn.hpp
│   │       macro-use.hpp
│   │       macro-with.hpp
│   │       type-assemblers.hpp
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
├───misc
├───parameters
│       In_out_ref_.hpp
│       
├───stdlib-includes
│       basic-general.hpp
│       basic-io.hpp
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

In addition there's an ***\_all\_.hpp*** header in every folder. Including the top level <i>\_all\_.hpp</i> header includes everything except a testing framework. Alternatively you can include the top-level ***all-except-io.hpp*** header, also not shown above, which includes the same as *\_all\_.hpp* except the *io* folder and the standard library's i/o headers.
