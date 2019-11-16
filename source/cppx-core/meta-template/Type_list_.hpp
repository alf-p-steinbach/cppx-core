#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/language/tmp/type-traits.hpp>                   // cppx::is_same_type_
#include <cppx-core/language/types/Truth.hpp>                       // cppx::Truth

namespace cppx
{
    //------------------------------------------------ Type_list_

    template< class... Types >
    struct Type_list_ {};

    //------------------------------------------------ Head_

    template< class A_type_list >
    struct Head_t_;

    template< class A_type, class... More_types >
    struct Head_t_<Type_list_<A_type, More_types... >> { using T = A_type; };

    template< class A_type_list >
    using Head_ = typename Head_t_<A_type_list>::T;

    //------------------------------------------------ Tail_

    template< class A_type_list >
    struct Tail_t_;

    template< class A_type, class... More_types >
    struct Tail_t_<Type_list_<A_type, More_types...>> { using T = Type_list_<More_types...>; };

    template< class A_type_list >
    using Tail_ = typename Tail_t_<A_type_list>::T;


    //------------------------------------------------ Joined_

    template< class Type_list_1, class Type_list_2 >
    struct Joined_t_;

    template< class... Pack_1, class... Pack_2 >
    struct Joined_t_< Type_list_<Pack_1...>, Type_list_<Pack_2...> >
    {
        using T = Type_list_< Pack_1..., Pack_2... >;
    };

    template< class Type_list_1, class Type_list_2 >
    using Joined_ = typename Joined_t_<Type_list_1, Type_list_2>::T;


    //------------------------------------------------ contains_*

    /// @cond DOXY_SHOW_IMPL_DETAILS
    namespace impl
    {
        template< class A_type, class Type_list >
        struct Contains_
        {
            static constexpr Truth value =
                is_same_type_< A_type, Head_<Type_list > > or
                Contains_< A_type, Tail_<Type_list> >::value;
        };

        template< class A_type >
        struct Contains_< A_type, Type_list_<> >
        {
            static constexpr Truth value = false;
        };

        template< class Possible_subset, class Main_type_list >
        struct Has_subset_
        {
            static constexpr Truth value =
                Contains_< Head_<Possible_subset>, Main_type_list >::value and
                Has_subset_< Tail_<Possible_subset>, Main_type_list >::value;
        };

        template< class Main_type_list >
        struct Has_subset_<Type_list_<>, Main_type_list>
        {
            static constexpr Truth value = true;
        };

    }  // namespace impl
    /// @endcond

    template< class Some_type, class Type_list >
    constexpr bool contains_type_ =
        impl::Contains_<Some_type, Type_list>::value;

    template< class Possible_subset, class Main_set >
    constexpr bool contains_type_subset_ =
        impl::Has_subset_<Possible_subset, Main_set>::value;
}  // namespace cppx
