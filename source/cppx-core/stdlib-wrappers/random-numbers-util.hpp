#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/bit-level/bits_per_.hpp>               // cppx::(bits_per_, system_bitness)
#include <cppx-core/language/calc/integer-operations.hpp>           // cppx::div_up
#include <cppx-core/language/syntax/macro-use.hpp>                  // CPPX_USE_...
#include <cppx-core/language/tmp-support/basic-type-traits.hpp>     // cppx:(is_same_type_, is_unsigned_, is_integral_)
#include <cppx-core/language/tmp-support/basic-Enable_if_.hpp>      // cppx::Enable_if_
#include <cppx-core/language/types/type-makers.hpp>                 // cppx::Type_choice_

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

namespace cppx::random
{
    CPPX_USE_STD(
        invoke,
        default_random_engine, random_device,
        independent_bits_engine, uniform_int_distribution, uniform_real_distribution
        );

    using Fast_generator    = Type_choice_<(system_bitness >= 64), std::mt19937_64, std::mt19937>;
    using Good_generator    = std::mt19937_64;

    using Generator     = Good_generator;
    using Bits_value    = Generator::result_type;
    
    static_assert( is_unsigned_<Bits_value> );
    static_assert( is_same_type_<random_device::result_type, unsigned> );
    static_assert( sizeof( Bits_value ) >= sizeof( unsigned ) );

    inline auto hardware_entropy()
        -> unsigned
    {
        static random_device the_entropy_source;

        return the_entropy_source();
    }

    class Seed
    {
        Bits_value  m_value;

    public:
        auto value() const -> Bits_value { return m_value; }

        Seed(): m_value( 0 ) {}
        explicit Seed( const Bits_value value = 0 ): m_value( value ) {}
    };

    inline auto random_seed()
        -> Seed
    {
        // Not using std::independent_bits_engine because it copies the underlying engine.
        Bits_value value = 0;
        constexpr int n_shifts = div_up( sizeof( Bits_value ), sizeof( unsigned ) );
        for( int i = 0; i < n_shifts; ++i ) {
            value = (value << bits_per_<unsigned>) | hardware_entropy();
        }
        return Seed( value );
    }

    template< class Unsigned, class = Enable_if_<is_unsigned_<Unsigned>> >
    class Bits_
    {
        using Bits_generator = independent_bits_engine<Generator, bits_per_<Unsigned>, Unsigned>;

        Bits_generator  m_bits_generator;

    public:
        auto generator()
            -> Bits_generator&
        { return m_bits_generator; }

        auto next()
            -> Unsigned
        { return m_bits_generator(); }

        Bits_( const Seed seed = {} ):
            m_bits_generator( seed.value() )
        {}
    };

    template<>
    class Bits_<Bits_value>
    {
        Generator       m_bits_generator;

    public:
        auto generator()
            -> Generator&       // Not the same type as for the general case. Same meta-type.
        { return m_bits_generator; }

        auto next()
            -> Bits_value
        { return m_bits_generator(); }

        Bits_( const Seed seed = {} ):
            m_bits_generator( seed.value() )
        {}
    };

    using Bits = Bits_<Bits_value>;

    template< class Integer, class = Enable_if_<is_integral_<Integer>> >
    class Integers_
    {
        using Adapter = uniform_int_distribution<Integer>;

        Generator       m_bits_generator;
        Adapter         m_adapt;

    public:
        auto generator()
            -> Generator&
        { return m_bits_generator; }

        auto next()
            -> Integer
        { return m_adapt( m_bits_generator ); }

        Integers_( const Integer n_unique_values, const Seed seed = {} ):
            m_bits_generator( seed.value() ),
            m_adapt( 0, n_unique_values - 1 )
        {}
    };

    using Integers = Integers_<int>;

    template< class Number, class = Enable_if_<is_floating_point_<Number>> >
    class Numbers_
    {
        using Adapter = std::uniform_real_distribution<Number>;

        Generator       m_bits_generator;
        Adapter         m_adapt;

    public:
        auto generator()
            -> Generator&
        { return m_bits_generator; }

        auto next()
            -> Number
        { return m_adapt( m_bits_generator ); }

        Numbers_( const Seed seed = {} ):
            m_bits_generator( seed.value() )
        {}
    };

    using Numbers = Numbers_<double>;
}  // namespace cppx::random
