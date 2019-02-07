﻿#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

// In the comments below <@/whatever> means <cppx-core/whatever>.
#include <c/assert.hpp>     // assert
#include <c/ctype.hpp>      // - Narrow text classifiers
#include <c/math.hpp>       // - As-if it also includes <c/stdlib.hpp>.
#include <c/stdint.hpp>     // - E.g. uintptr_t, uint32_t, int64_t
#include <c/stdlib.hpp>     // EXIT_...
#include <c/string.hpp>     // strlen, ++
#include <c/wchar.hpp>      // wcslen, ++
#include <c/wctype.hpp>     // - Wide text classifiers.
#include <algorithm>        // std::(min, max, ...)
#include <array>            // std::(array)
#include <chrono>           // std::chrono::*
#include <deque>            // std::deque (e.g. default container for std::stack)
#include <functional>       // std::(function)
#include <iosfwd>           // - Forward declarations of stream types etc.
#include <iterator>         // std::(begin, end, size)
#include <queue>            // std::queue
#include <random>           // std::(...)
#include <stack>            // std::stack
#include <stdexcept>        // std::(...). But see <@/failure-handling/macro_fail.hpp>.
#include <string>           // std::string
#include <string_view>      // - But see <@/text/String_view_.hpp>.
#include <atomic>           // - atomic operations support for threading
#include <thread>           // std::thread, std::this_thread::sleep_for
#include <unordered_map>    // - But see <@/collections/Map_.hpp>
#include <unordered_set>    // - But see <@/collections/Set_.hpp>
#include <utility>          // std::(forward, move), std::rel_ops::*
#include <vector>           // std::vector
