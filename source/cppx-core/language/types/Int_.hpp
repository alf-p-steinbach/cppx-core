#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <c/stdint.hpp>     // ::intN_t
#include <type_traits>      // std::make_unsigned_t

namespace cppx
{
    namespace impl
    {
        template< int n_bits >  struct Int_t_;

        template<> struct Int_t_<8>{   using T = int8_t;   };
        template<> struct Int_t_<16>{  using T = int16_t;  };
        template<> struct Int_t_<32>{  using T = int32_t;  };
        template<> struct Int_t_<64>{  using T = int64_t;  };
    }  // namespace impl

    template< int n_bits >  using Int_          = typename impl::Int_t_<n_bits>::T;
    template< int n_bits >  using Unsigned_int_ = std::make_unsigned_t<Int_<n_bits>>;

}  // namespace cppx
