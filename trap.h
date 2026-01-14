#pragma once

#include <exception>
#include <cassert>

#include "yield.h"

namespace thaumaturgy {
    template <typename F>
    yield contain(yield& out, F&& fn) noexcept {
        try {
            fn();
        } catch (...) {
            out.set_state(yield_state::trap);
        }
        return out;
    }

    constexpr inline bool warded(const yield& y) noexcept {
        return !y.is_failure();
    }

} // namespace thaumaturgy
