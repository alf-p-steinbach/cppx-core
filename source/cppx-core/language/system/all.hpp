#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/system/Byte.hpp>
#include <cppx-core/language/system/Endian.hpp>
#include <cppx-core/language/system/size-types.hpp>

namespace cppx{
    /// \brief Provides
    /// \make_name_ref{cppx,Byte},
    /// \make_name_ref{cppx,Signed_byte},
    /// \make_name_ref{cppx,bytes_per_},
    /// \make_name_ref{cppx,as_byte_ptr},
    /// \make_name_ref{cppx,as_signedbyte_ptr},
    /// \make_name_ref{cppx,as_char_ptr} and
    /// \make_name_ref{cppx,bits_per_byte}, + `std::byte` support definitions
    /// \make_name_ref{cppx,as_number} and
    /// \make_name_ref{cppx,as_std_byte};
    /// \make_name_ref{cppx,Size} and
    /// \make_name_ref{cppx,Index}, plus unsigned equivalents
    /// \make_name_ref{cppx,Unsigned_size} and
    /// \make_name_ref{cppx,Unsigned_index};
    /// \make_name_ref{cppx,Endian},
    /// \make_name_ref{cppx,is_little_endian},
    /// \make_name_ref{cppx,is_big_endian} and
    /// \make_name_ref{cppx,is_mixed_endian}.
    namespace system {}
}
