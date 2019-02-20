# Cppx Core

The core of the not yet published *C++ Band Aid* library.

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

*Cppx Core* provides the following:

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
