#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
/// \file
/// \brief `$unused` expands to C++17 `[[maybe_unused]]`.

#ifndef CPPX_NO_DOLLARS_PLEASE
#   define  $unused     CPPX_UNUSED                 ///< \dollarname{unused}
#endif

#ifndef CPPX_UNUSED
/// \brief Expands to C++17 `[[maybe_unused]]`.
#   define  CPPX_UNUSED     [[maybe_unused]]        // C++17 wordy/misleading attribute.
#endif
