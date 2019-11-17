#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core-language/syntax/macro-use.hpp>              // CPPX_USE_STD
#include <cppx-core-language/syntax/macro-with.hpp>             // CPPX_WITH
#include <cppx-core-language/tmp/type-traits.hpp>               // cppx::is_same_type_

#include <filesystem>       // std::filesystem
#include <string>           // std::(string, wstring)
#include <vector>           // std::vector

namespace cppx
{
    namespace fs = std::filesystem;
    CPPX_USE_STD( string );

    namespace fs_util {
        namespace impl {
            template< bool utf8_is_sabotaged_for_windows >
            struct Workaround_;

            template<>
            struct Workaround_<false>
            {
                static auto utf8_from( const fs::path& path )
                    -> string
                { return path.u8string(); }
            };

            template<>
            struct Workaround_<true>
            {
                static auto utf8_from( const fs::path& path )
                    -> string
                { CPPX_WITH( path.u8string() ) { return string( _.begin(), _.end() ); } }
            };
        }  // namespace impl
            
        inline auto utf8_from( const fs::path& path )
            -> string
        {
            using Result_type = decltype( path.u8string() );
            constexpr bool is_sabotaged = not is_same_type_<string, Result_type>;
            return impl::Workaround_<is_sabotaged>::utf8_from( path );
        }
    }  // namespace fs_util

    using fs_util::utf8_from;
}  // cppx
