#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

// This header is conditionally included from the top level "_all_.hpp" header. To avoid
// that, to use a non-UTF-8 execution character set, you can either just not use
// `_all_.hpp_`, or define `CPPX_NO_CHARSET_ASSERTION_PLEASE` before including it.

#if not defined( __GNUC__ ) or CPPX_CHECK_CHARSET_PLEASE
    // g++ 8.2.x always emits a warning for the multibyte constant, only suppressable via
    // command line option, not via pragma. But g++ is UTF-8 by default. So, ignoring g++.
    static_assert( sizeof( 'ø' ) > 1,
        "The execution character set must be UTF-8 (e.g. MSVC option \"/utf-8\")."
        );
#endif
