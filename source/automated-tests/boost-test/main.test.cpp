#define BOOST_TEST_MODULE cppx-core unit tests
#include <_/test-framework.hpp>

#ifdef _WIN32
#   include <c/stdlib.hpp>     // system
    const bool dummy = []()
    {
        return EXIT_SUCCESS == system( "chcp 65001 >nul" );
    }();
#endif
