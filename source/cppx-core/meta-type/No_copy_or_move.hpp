#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

namespace cppx
{
    class No_copy_or_move
    {
        auto operator=( const No_copy_or_move& ) -> No_copy_or_move& = delete;
        No_copy_or_move( const No_copy_or_move& ) = delete;

        auto operator=( No_copy_or_move&& ) -> No_copy_or_move& = delete;
        No_copy_or_move( No_copy_or_move&& ) = delete;

    public:
        No_copy_or_move() {}
    };

}  // namespace cppx
