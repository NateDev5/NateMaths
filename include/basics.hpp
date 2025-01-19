//
// Created by nate on 1/19/25.
//

#pragma once

#include <algorithm>

namespace Nate {
    template<typename t_type>
    static t_type max(t_type a, t_type b) {
        static_assert(std::is_arithmetic<t_type>::value, "Type must be a number");
        return (a > b) ? a : b;
    }

    template<typename t_type>
    static t_type min(t_type a, t_type b) {
        static_assert(std::is_arithmetic<t_type>::value, "Type must be a number");
        return (a < b) ? a : b;
    }

    template<typename t_type>
    static t_type sign(t_type val) {
        static_assert(std::is_arithmetic<t_type>::value, "Type must be a number");
        return (t_type(0) < val) - (val < t_type(0));
    }

    template<typename t_type>
    static t_type square(t_type val) {
        static_assert(std::is_arithmetic<t_type>::value, "Type must be a number");
        return val * val;
    }
}