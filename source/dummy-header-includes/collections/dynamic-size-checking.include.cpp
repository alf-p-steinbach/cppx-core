#include <cppx-core/collections/dynamic-size-checking.hpp>

// Introduces template specializations that satisfy the linker that there's something here.
namespace
{
    constexpr auto  v1 = cppx::array_size_of( "alfa" );
    constexpr auto  v2 = cppx::n_items_of( "gosh" );
    const auto      v3 = cppx::n_items_of( std::bitset<32>() );
    const auto      v4 = cppx::length_of( std::string( "blah") );
    const auto      v5 = cppx::length_of( std::string_view( "view") );
    const auto      v6 = cppx::length_of( "C string" );
}  // namespace <anon>
