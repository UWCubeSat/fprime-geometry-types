
#ifndef GEOMETRY_TYPES_GEO_TEST_VECTOR_TESTVECTOR_HPP_
#define GEOMETRY_TYPES_GEO_TEST_VECTOR_TESTVECTOR_HPP_

#include <array>
#include <cstdint>
#include <random>

#include "default/config/FwSizeTypeAliasAc.hpp"  // FwSizeType
#include "gtest/gtest.h"

#include "../../Vector/Vector.hpp"
#include "../geo_test_functions.hpp"

namespace geo {

#define SETUP_VECTOR_TEST(_placeholder, test, N) \
    {                                            \
        static_assert(N >= 2);                   \
        geo::Vector<N> curr_test_vec;            \
        std::array<float, N> rand_dat;           \
        for (FwSizeType i = 0; i < N; i++) {     \
            rand_dat.at(i) = rand_val(200);         \
            curr_test_vec[i] = rand_dat.at(i);      \
        }                                        \
        test(N);                                 \
    }

}  // namespace geo

#endif  // GEOMETRY_TYPES_GEO_TEST_VECTOR_TESTVECTOR_HPP_
