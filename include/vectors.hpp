//
// Created by nate on 1/8/25.
//


#pragma once

#include <array>
#include <cmath>
#include <cstdint>
#include <stdexcept>
#include <tuple>

// maybe someday ill implement simd to make this more efficient
namespace Nate {
    template<unsigned int t_size, typename t_type>
    struct vec_base {
        std::array<t_type, t_size> data;

        template<typename... Args>
            requires(sizeof...(Args) == t_size && sizeof...(Args) > 1)
        constexpr vec_base(Args... args) : data{static_cast<t_type>(args)...} {
        }

        constexpr vec_base(){
            data.fill(t_type(0));
        }

        constexpr vec_base(t_type scalar){
            data.fill(scalar);
        }

        constexpr t_type &operator[](unsigned int index){
            if (index >= t_size)
                throw std::out_of_range("Index out of bounds");

            return data[index];
        }

        constexpr const t_type &operator[](unsigned int index) const {
            if (index >= t_size)
                throw std::out_of_range("Index out of bounds");

            return data[index];
        }

        // Aliases
        constexpr t_type &x() requires(t_size > 0) { return data[0]; }
        constexpr const t_type &x() const requires(t_size > 0) { return data[0]; }

        constexpr t_type &y() requires(t_size > 1) { return data[1]; }
        constexpr const t_type &y() const requires(t_size > 1) { return data[1]; }

        constexpr t_type &z() requires(t_size > 2) { return data[2]; }
        constexpr const t_type &z() const requires(t_size > 2) { return data[2]; }

        constexpr t_type &w() requires(t_size > 3) { return data[3]; }
        constexpr const t_type &w() const requires(t_size > 3) { return data[3]; }


        constexpr auto xy() const requires(t_size > 1) {
            return std::make_tuple(data[0], data[1]);
        }

        constexpr auto xyz() const requires(t_size > 2) {
            return std::make_tuple(data[0], data[1], data[2]);
        }

        constexpr auto xyzw() const requires(t_size > 3) {
            return std::make_tuple(data[0], data[1], data[2], data[3]);
        }

        // Assignments
        template<typename T>
        constexpr vec_base operator=(T val) {
            static_assert(std::is_arithmetic<T>::value, "Type must be a number");
            for (int i = 0; i < t_size; i++)
                data[i] = val;

            return *this;
        }

        constexpr vec_base operator=(const vec_base &vec) {
            if (this == &vec)
                return *this;
            for (int i = 0; i < t_size; i++)
                data[i] = vec.data[i];

            return *this;
        }

        constexpr bool operator==(const vec_base &vec) const {
            bool out = true;
            for (int i = 0; i < t_size; i++)
                if (data[i] != vec.data[i]) {
                    out = false;
                    break;
                }
            return out;
        }

        // Negate
        constexpr vec_base operator-() {
            for (int i = 0; i < t_size; i++)
                data[i] = -data[i];

            return *this;
        }

        // Arithmetics
        constexpr vec_base operator+(const vec_base &vec) const {
            vec_base result;

            for (int i = 0; i < t_size; i++)
                result.data[i] = data[i] + vec.data[i];

            return result;
        }

        constexpr vec_base operator-(const vec_base &vec) const {
            vec_base result;

            for (int i = 0; i < t_size; i++)
                result.data[i] = data[i] - vec.data[i];

            return result;
        }

        constexpr vec_base operator*(const vec_base &vec) const {
            vec_base result;

            for (int i = 0; i < t_size; i++)
                result.data[i] = data[i] * vec.data[i];

            return result;
        }

        constexpr vec_base operator/(const vec_base &vec) const {
            vec_base result;

            for (int i = 0; i < t_size; i++)
                result.data[i] = data[i] / vec.data[i];

            return result;
        }

        // Scalar arithmetics
        template<typename T>
        constexpr vec_base operator+(T val) const {
            static_assert(std::is_arithmetic<T>::value, "Type must be a number");
            vec_base result;

            for (int i = 0; i < t_size; i++)
                result.data[i] = data[i] + val;

            return result;
        }

        template<typename T>
        constexpr vec_base operator-(T val) const {
            static_assert(std::is_arithmetic<T>::value, "Type must be a number");
            vec_base result;

            for (int i = 0; i < t_size; i++)
                result.data[i] = data[i] - val;

            return result;
        }

        template<typename T>
        constexpr vec_base operator*(T val) const {
            static_assert(std::is_arithmetic<T>::value, "Type must be a number");
            vec_base result;

            for (int i = 0; i < t_size; i++)
                result.data[i] = data[i] * val;

            return result;
        }

        template<typename T>
        constexpr vec_base operator/(T val) const {
            static_assert(std::is_arithmetic<T>::value, "Type must be a number");
            vec_base result;

            for (int i = 0; i < t_size; i++)
                result.data[i] = data[i] / val;

            return result;
        }

        // Compound assignment
        constexpr vec_base operator+=(const vec_base &vec) {
            for (int i = 0; i < t_size; i++)
                data[i] += vec.data[i];
            return *this;
        }

        constexpr vec_base operator-=(const vec_base &vec) {
            for (int i = 0; i < t_size; i++)
                data[i] -= vec.data[i];
            return *this;
        }

        constexpr vec_base operator*=(const vec_base &vec) {
            for (int i = 0; i < t_size; i++)
                data[i] *= vec.data[i];
            return *this;
        }

        constexpr vec_base operator/=(const vec_base &vec) {
            for (int i = 0; i < t_size; i++)
                data[i] /= vec.data[i];
            return *this;
        }
    };

    typedef vec_base<1, float> vec;
    typedef vec_base<1, int> vec_i;
    typedef vec_base<1, double> vec_d;

    typedef vec_base<2, float> vec2;
    typedef vec_base<2, int> vec2_i;
    typedef vec_base<2, double> vec2_d;

    typedef vec_base<3, float> vec3;
    typedef vec_base<3, int> vec3_i;
    typedef vec_base<3, double> vec3_d;

    typedef vec_base<4, float> vec4;
    typedef vec_base<4, int> vec4_i;
    typedef vec_base<4, double> vec4_d;

    typedef vec_base<4, uint8_t> rgba;

    template<unsigned int t_size, typename t_type>
    static float length(const vec_base<t_size, t_type> &vec){
        t_type sum = 0;
        for (int i = 0; i < t_size; i++)
            sum += vec.data[i] * vec.data[i];
        return std::sqrt(sum);
    }

    template<unsigned int t_size, typename t_type>
    static vec_base<t_size, t_type> max(const vec_base<t_size, t_type> &vec, float max_) {
        vec_base<t_size, t_type> result(0);
        for (int i = 0; i < t_size; i++)
            result.data[i] = max(vec.data[i], max_);
        return result;
    }

    template<unsigned int t_size, typename t_type>
    static vec_base<t_size, t_type> max(const vec_base<t_size, t_type> &a, const vec_base<t_size, t_type> &b) {
        vec_base<t_size, t_type> result;
        for (int i = 0; i < t_size; i++)
            result.data[i] = max(a.data[i], b.data[i]);
        return result;
    }

    template<unsigned int t_size, typename t_type>
    static vec_base<t_size, t_type> min(const vec_base<t_size, t_type> &vec, float min_) {
        vec_base<t_size, t_type> result;
        for (int i = 0; i < t_size; i++)
            result.data[i] = min(vec.data[i], min_);
        return result;
    }

    template<unsigned int t_size, typename t_type>
    static vec_base<t_size, t_type> min(const vec_base<t_size, t_type> &a, const vec_base<t_size, t_type> &b) {
        vec_base<t_size, t_type> result;
        for (int i = 0; i < t_size; i++)
            result.data[i] = min(a.data[i], b.data[i]);
        return result;
    }

    template<unsigned int t_size, typename t_type>
    static vec_base<t_size, t_type> normalize(vec_base<t_size, t_type> &vec) {
        return vec / length(vec);
    }

    template<unsigned int t_size, typename t_type>
    static t_type distance(const vec_base<t_size, t_type> &a, const vec_base<t_size, t_type> &b) {
        t_type sum = 0;
        for (int i = 0; i < t_size; i++)
            sum += square(b.data[i] - a.data[i]);
        return std::sqrt(sum);
    }

    template<unsigned int t_size, typename t_type>
    static t_type dot(const vec_base<t_size, t_type> &a, const vec_base<t_size, t_type> &b) {
        t_type res = 0;
        for (int i = 0; i < t_size; i++)
            res += a.data[i] * b.data[i];
        return res;
    }
}
