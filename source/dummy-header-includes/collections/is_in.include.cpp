#include <cppx-core/collections/is_in.hpp>

namespace
{
    const bool  v1 = cppx::is_in( std::string_view( "Baluba" ), 'x' );
    const bool  v2 = cppx::is_in( {1, 2, 3}, 5 );
    const bool  v3 = cppx::is_in( std::bitset<32>(), 7 );
}  // namespace <anon>
