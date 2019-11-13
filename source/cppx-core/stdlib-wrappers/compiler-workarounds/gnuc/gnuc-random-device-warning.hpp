#pragma once

#ifndef __GNUC__
#   error "This file is specific to the g++ compiler"
#   include <this_file_is_specific_to_the_gplusplus_compiler>       // Fatal error
#endif

#ifndef CPPX_NO_WARNING_ABOUT_RANDOM_DEVICE
#   ifndef  _GLIBCXX_USE_RANDOM_TR1
#           pragma GCC warning \
                "_GLIBCXX_USE_RANDOM_TR1 not defined: std::random_device may use a fixed pseudo-random sequence."
#   endif
#endif
