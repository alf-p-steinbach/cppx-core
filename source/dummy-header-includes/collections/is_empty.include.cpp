#include <cppx-core-language/syntax/collection-util.hpp>

#include <string>

namespace
{
    const bool  v1  = !!cppx::is_empty( std::string( "bah" ) );
    const bool  v2  = !!cppx::is_empty( "C string" );
}  // namespace <anon>
