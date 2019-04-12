#include <cppx-core/collections/is_in.hpp>

namespace
{
    const cppx::Truth   v1 = cppx::is_in( std::string_view( "Baluba" ), 'x' );
    const cppx::Truth   v2 = cppx::is_in( {1, 2, 3}, 5 );
    const cppx::Truth   v3 = cppx::is_in( std::bitset<32>(), 7 );
}  // namespace <anon>
