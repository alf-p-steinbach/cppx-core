#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

// In the comments below <@/whatever> means <cppx-core/whatever>.
#include <c/assert.hpp>         // assert
#include <c/ctype.hpp>          // - Narrow text classifiers
#include <c/math.hpp>           // - As-if it also includes <c/stdlib.hpp>.
#include <c/stdint.hpp>         // - E.g. uintptr_t, uint32_t, int64_t
#include <c/stdlib.hpp>         // EXIT_...
#include <c/string.hpp>         // strlen, ++
#include <c/wchar.hpp>          // wcslen, ++
#include <c/wctype.hpp>         // - Wide text classifiers.

#include <algorithm>            // std::(min, max, ...)
#include <array>                // std::(array)
#include <atomic>               // - atomic operations support for threading
#include <chrono>               // std::chrono::*
#include <condition_variable>   // std::condition_variable
#include <deque>                // std::deque (e.g. default container for std::stack)
#include <functional>           // std::(function)
#include <initializer_list>     // std::initializer_list
#include <iosfwd>               // - Forward declarations of stream types etc.
#include <iterator>             // std::(begin, end, size)
#include <map>                  // std::map
#include <memory>               // std::(unique_ptr, shared_ptr, ...)
#include <mutex>                // std::(mutex, lock_guard) etc.
#include <numeric>              // std::accumulate etc.
#include <optional>             // std::optional
#include <queue>                // std::queue
#include <random>               // std::(...)
#include <set>                  // std::set
#include <stack>                // std::stack
#include <stdexcept>            // std::(...). But see <@/failure-handling/macro-fail.hpp>.
#include <string>               // std::string
#include <string_view>          // - But see <@/text/String_view_.hpp>.
#include <thread>               // std::thread, std::this_thread::sleep_for
#include <unordered_map>        // - But see <@/collections/Map_.hpp>
#include <unordered_set>        // - But see <@/collections/Set_.hpp>
#include <utility>              // std::(forward, move), std::rel_ops::*
#include <vector>               // std::vector
