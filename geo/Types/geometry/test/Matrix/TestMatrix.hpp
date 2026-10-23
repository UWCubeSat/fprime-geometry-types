#ifndef GEOMETRY_TYPES_GEO_TEST_MATRIX_TESTMATRIX_HPP_
#define GEOMETRY_TYPES_GEO_TEST_MATRIX_TESTMATRIX_HPP_

#include "default/config/FwSizeTypeAliasAc.hpp"  // FwSizeType
#include "gtest/gtest.h"

#include "../../Matrix/Matrix.hpp"
#include "../geo_test_functions.hpp"

namespace geo {

template <std::size_t N>
std::array<std::array<float, N>, N> rand_matrix() noexcept {
    std::array<std::array<float, N>, N> out;
    for (std::size_t i = 0; i < N; i++) {
        for (std::size_t j = 0; j < N; j++) {
            out[i][j] = rand_val(200);
        }
    }
    return out;
}

#define MATRIX_ARR_COMP(mat, arr)                                                                                   \
    static_assert(std::pow(mat.n(), 2) == sizeof(arr) / sizeof(arr[0][0]));                                         \
    for (FwSizeType i = 0; i < mat.n(); i++) {                                                                      \
        for (FwSizeType j = 0; j < mat.n(); j++) {                                                                  \
            EXPECT_FLOAT_EQ(arr[i][j], mat.cell(i, j))                                                              \
                << "matrix dimension: " << static_cast<int>(mat.n()) << ", index: (" << static_cast<int>(i) << ", " \
                << static_cast<int>(j) << ")";                                                                      \
        }                                                                                                           \
    }

}  // namespace geo

#endif  // GEOMETRY_TYPES_GEO_TEST_MATRIX_TESTMATRIX_HPP_
