#pragma once

#include <exception>
#include <cassert>

#include "yield.h"

namespace thaumaturgy {
    template <typename Fn>
    inline yield contain(Fn&& fn) noexcept {
        yield y;
        try {
            if constexpr (std::is_same_v<decltype(fn()), yield>) {
                y |= fn();
            } else {
                fn();
            }
        }
        catch (const std::exception&) {
            y.set_state(yield_state::trap)
             .set_origin(yield_origin::process)
             .set_code(1);
        }
        catch (...) {
            y.set_state(yield_state::trap)
             .set_origin(yield_origin::process)
             .set_code(2);
        }
        return y;
    }

    constexpr inline bool warded(const yield& y) noexcept {
        return !y.is_failure();
    }

} // namespace thaumaturgy
