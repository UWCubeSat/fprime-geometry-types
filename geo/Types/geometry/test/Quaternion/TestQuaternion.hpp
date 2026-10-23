#ifndef GEOMETRY_TYPES_GEO_TEST_QUATERNION_TESTQUATERNION_HPP_
#define GEOMETRY_TYPES_GEO_TEST_QUATERNION_TESTQUATERNION_HPP_

#include <array>
#include <cmath>
#include <utility>

#include "gtest/gtest.h"

#include "../../Quaternion/Quaternion.hpp"
#include "../geo_test_functions.hpp"

namespace geo {

/**
 * @brief Generates a random quaternion with real and imaginary values in std::pair
 * @returns real, imaginary quaternion values
 */
std::pair<float, std::array<float, 3>> generate_quat() {
    std::array<float, 3> imag;
    float real = 0;
    for (auto& val : imag) {
        val = rand_val(1.0);
        real += std::pow(val, 2);
    }
    if (real > 1.0) {
        // std::cout << "recurse" << std::endl;
        return generate_quat();
    }
    real = 1 - real;
    real = std::sqrt(real);
    if (rand_val(1.0) < 0.0) {
        real = -real;
    }

    // std::cout << "real: " << real << ", imag: " << imag[0] << ", " << imag[1] << ", " << imag[2] << std::endl;
    return std::make_pair(real, imag);
}

#define TEST_QUAT_COMPS(q, real, imag)   \
    do {                                 \
        EXPECT_FLOAT_EQ(q.w(), real);    \
        EXPECT_FLOAT_EQ(q.x(), imag[0]); \
        EXPECT_FLOAT_EQ(q.y(), imag[1]); \
        EXPECT_FLOAT_EQ(q.z(), imag[2]); \
    } while (0)

/*
template <std::size_t N>
struct MyCustomArr {
float _dat[N];

float& operator[](const std::size_t i) const { return this->_dat[i]; }
float& operator[](const std::size_t i) { return this->_dat[i]; }
};*/

}  // namespace geo

#endif  // GEOMETRY_TYPES_GEO_TEST_QUATERNION_TESTQUATERNION_HPP_
