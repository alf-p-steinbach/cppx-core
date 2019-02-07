#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

namespace cppx
{
    class No_copy
    {
        auto operator=( const No_copy& ) -> No_copy& = delete;
        No_copy( const No_copy& ) = delete;

        auto operator=( No_copy&& ) -> No_copy& = default;
        No_copy( No_copy&& ) = default;

    public:
        No_copy() {}
    };

}  // namespace cppx
