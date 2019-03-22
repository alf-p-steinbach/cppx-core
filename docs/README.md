# *cppx-core* – C++ Core Functionality

<img align="right" width="380" style="padding-left: 1em" src="images/folder-dependencies.png">

![This library is under construction](images/under-construction.25-pct.png)

The main purpose of the *cppx-core* C++17 header library is to provide basic Unicode functionality, e.g. UTF-8 ↔ UTF-16 conversion, plus other basic C++ coding functionality, to an as yet unpublished library called *C++ Band Aid*.

But *cppx-core* is eminently usable on its own.

*cppx-core* reduces the code needed to do some simple common things, for example including standard library headers, `using`-declaring a larger number of identifiers from a namespace, or throwing an exception with the throwing function's name in the message.

This code reduction will hopefully support Good Programming Practices&trade; in examples on the net, where brevity is often very important.

Dependency: the [*C header wrappers*](https://github.com/alf-p-steinbach/C-header-wrappers) nano-library that provides headers like *\<c/stdlib.hpp\>*.

---

A ~minimal example of *cppx-core* usage:

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

A larger (but still small) example is also available:
 
 * Basic *language* folder facilities, mostly *language/syntax*:  
  the [KWIC-like greeting example](example-kwic.md).


<div></div>

---

*cppx-core* provides the following headers:

~~~ txt
•
│   all-ascii.hpp
│   all-calc.hpp
│   all-except-io.hpp
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
├───data
│       ascii-character-names.hpp
│       named-numbers.hpp
│       Symbol_strings.hpp
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
│           C_str_.hpp
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
    │   pointers-from-string_view.hpp
    │   string-util.hpp
    │   
    ├───ascii
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
