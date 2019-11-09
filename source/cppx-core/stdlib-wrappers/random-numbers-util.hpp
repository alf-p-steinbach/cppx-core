#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/syntax/macro-use.hpp>          // CPPX_USE_...

#ifndef CPPX_NO_WARNING_ABOUT_RANDOM_DEVICE
#   ifdef __GNUC__
#       ifndef  _GLIBCXX_USE_RANDOM_TR1
#           pragma GCC warning \
                "_GLIBCXX_USE_RANDOM_TR1 not defined:" \
                " std::random_device may use a fixed pseudo-random sequence."
#       endif
#   endif
#endif

#include <random>

namespace cppx::rnd
{
    CPPX_USE_STD(
        invoke,
        default_random_engine, random_device, uniform_real_distribution
        );

    using Generator     = std::mt19937_64;
    using Bits_value    = Generator::result_type;
    
    static_assert( std::is_unsigned_v<Bits_value> );
    static_assert( std::is_same_v<random_device::result_type, unsigned> );

    struct Seed{ Bits_value value; };

    inline auto hardware_entropy()
        -> unsigned
    {
        static random_device the_entropy_source;

        return the_entropy_source();
    }

}  // namespace cppx::rnd
