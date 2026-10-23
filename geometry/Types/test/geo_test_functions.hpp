#ifndef GEOMETRY_TYPES_GEO_GEO_TEST_FUNCTIONS_HPP_
#define GEOMETRY_TYPES_GEO_GEO_TEST_FUNCTIONS_HPP_

#include <random>

namespace geo {

/**
 * @brief Produces a uniform random value between -radius and +radius.
 * @param[in] radius max magnitude of random val
 * @return random val
 */
static float rand_val(const double radius) {
    // default see so always has same output
    //  static std::random_device rd;
    static std::mt19937 gen;
    return radius * (static_cast<float>(gen()) / static_cast<float>(gen.max() / 2) - 1.0);
}

}  // namespace geo

#endif  // GEOMETRY_TYPES_GEO_GEO_TEST_FUNCTIONS_HPP_
