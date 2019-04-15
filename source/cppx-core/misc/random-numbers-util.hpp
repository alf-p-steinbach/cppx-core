#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/syntax/macro-use.hpp>          // CPPX_USE_...

#ifndef CPPX_NO_FIX_OF_RANDOM_DEVICE
#   ifdef __GNUC__
#       undef   _GLIBCXX_USE_RANDOM_TR1
#       define  _GLIBCXX_USE_RANDOM_TR1
#   endif
#endif

#include <random>

namespace cppx::rnd
{
    CPPX_USE_STD(
        invoke,
        default_random_engine, random_device, uniform_real_distribution
        );

    inline auto hardware_entropy()
        -> unsigned
    {
        static random_device the_entropy_source;
        return the_entropy_source();
    }

    template< unsigned value >
    struct Seed
    {
        auto operator()() const
            -> unsigned
        { return value; }
    };

    struct Random_seed
    {
        auto operator()() const
            -> unsigned
        { return hardware_entropy(); }
    };

    template< class Seeding >
    class Seq_
    {
    public:
        static inline auto bits_generator()
            -> default_random_engine&
        {
            static default_random_engine    the_generator( invoke( []() -> unsigned
            {
                const Seeding the_seeder;
                return the_seeder();
            } ) );

            return the_generator;
        }

        static inline auto next()
            -> double
        {
            static uniform_real_distribution the_distribution;
            return the_distribution( bits_generator() );
        }
    };

    using Seq = Seq_<Random_seed>;

}  // namespace cppx::rnd
