#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <_/test-framework.hpp>
#include <cppx-core/meta-template/Type_list_.hpp>

#include <cppx-core-language/syntax/declarations.hpp>   // $use_cppx
#include <cppx-core-language/tmp/type-traits.hpp>       // cppx::is_same_type_

$use_cppx( is_same_type_ );

$begin_test_suite( cppx_core, meta_template, HEADER, Type_list_ );

    using L_empty   = cppx::Type_list_<>;
    using L_c       = cppx::Type_list_<char>;
    using L_d       = cppx::Type_list_<double>;
    using L_dd      = cppx::Type_list_<double, double>;
    using L_i       = cppx::Type_list_<int>;
    using L_cd      = cppx::Type_list_<char, double>;
    using L_dc      = cppx::Type_list_<double, char>;
    using L_di      = cppx::Type_list_<double, int>;
    using L_ic      = cppx::Type_list_<int, char>;
    using L_dic     = cppx::Type_list_<double, int, char>;

    $test_case( contains_type_, GENERAL )
    {
        $expect( (not cppx::contains_type_<double, L_empty>) );
        $expect( (not cppx::contains_type_<double, L_c>) );
        $expect( (cppx::contains_type_<double, L_d>) );
        $expect( (cppx::contains_type_<double, L_cd>) );
        $expect( (cppx::contains_type_<double, L_dc>) );
    }

    $test_case( contains_type_subset_, GENERAL )
    {
        $expect( (cppx::contains_type_subset_<L_empty, L_empty>) );
        $expect( (cppx::contains_type_subset_<L_empty, L_d>) );
        $expect( (not cppx::contains_type_subset_<L_d, L_empty>) );
        $expect( (cppx::contains_type_subset_<L_d, L_d>) );
        $expect( (cppx::contains_type_subset_<L_d, L_dc>) );
        $expect( (cppx::contains_type_subset_<L_d, L_cd>) );
        $expect( (cppx::contains_type_subset_<L_cd, L_cd>) );
        $expect( (cppx::contains_type_subset_<L_cd, L_dc>) );
        $expect( (cppx::contains_type_subset_<L_cd, L_dic>) );
        $expect( (not cppx::contains_type_subset_<L_dic, L_cd>) );
    }

    $test_case( Joined_, GENERAL )
    {
        $expect( (is_same_type_< L_empty, cppx::Joined_<L_empty, L_empty> >) );
        $expect( (is_same_type_< L_d, cppx::Joined_<L_d, L_empty> > ) );
        $expect( (is_same_type_< L_d, cppx::Joined_<L_empty, L_d> > ) );
        $expect( (is_same_type_< L_dd, cppx::Joined_<L_d, L_d> > ) );
        $expect( (is_same_type_< L_di, cppx::Joined_<L_d, L_i> > ) );
        $expect( (is_same_type_< L_dic, cppx::Joined_<L_d, L_ic> > ) );
        $expect( (is_same_type_< L_dic, cppx::Joined_<L_di, L_c> > ) );
    }

$end_test_suite( 4 );
