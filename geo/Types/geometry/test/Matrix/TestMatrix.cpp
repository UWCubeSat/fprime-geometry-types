#include "TestMatrix.hpp"

#include <algorithm>
#include <array>

#include "Fw/DataStructures/Array.hpp"

namespace geo {
// ctors
TEST(MatrixTests, ctor_default) {
    geo::Matrix<3> test_mat_3{};
    geo::Matrix<9> test_mat_9{};

    // make sure matrices are zerod out
    for (FwSizeType row = 0; row < 9; row++) {
        for (FwSizeType col = 0; col < 9; col++) {
            if (row < 3 && col < 3) {
                EXPECT_EQ(0, test_mat_3.cell(row, col)) << "Matrix<3> index: (" << row << ", " << col << ")";
            }
            EXPECT_EQ(0, test_mat_9.cell(row, col)) << "Matrix<9> index: (" << row << ", " << col << ")";
        }
    }
}
TEST(MatrixTests, ctor_c_arr) {
    const auto rand_mat = rand_matrix<9>();
    float c_dat_3[3][3];
    float c_dat_9[9][9];

    std::copy(rand_mat[0].begin(), rand_mat[0].begin() + 9, &c_dat_3[0][0]);
    std::copy(rand_mat[0].begin(), rand_mat[0].begin() + 9 * 9, &c_dat_9[0][0]);

    const geo::Matrix<3> test_mat_3(c_dat_3);
    const geo::Matrix<9> test_mat_9(c_dat_9);

    MATRIX_ARR_COMP(test_mat_3, c_dat_3);
    MATRIX_ARR_COMP(test_mat_9, c_dat_9);
}
TEST(MatrixTests, ctor_cpp_arr) {
    const auto cpp_arr_9 = rand_matrix<9>();
    std::array<std::array<float, 3>, 3> cpp_arr_3;
    std::copy(cpp_arr_9[0].begin(), cpp_arr_9[0].begin() + 9, cpp_arr_3[0].begin());

    const geo::Matrix<3> test_mat_3(cpp_arr_3);
    const geo::Matrix<9> test_mat_9(cpp_arr_9);

    MATRIX_ARR_COMP(test_mat_3, cpp_arr_3);
    MATRIX_ARR_COMP(test_mat_9, cpp_arr_9);
}
TEST(MatrixTests, ctor_Fw_arr) {
    const auto rand_mat = rand_matrix<9>();
    Fw::Array<Fw::Array<float, 3>, 3> Fw_arr_3;
    Fw::Array<Fw::Array<float, 9>, 9> Fw_arr_9;
    std::copy(rand_mat[0].begin(), rand_mat[0].begin() + 3 * 3, &Fw_arr_3[0][0]);
    std::copy(rand_mat[0].begin(), rand_mat[0].begin() + 9 * 9, &Fw_arr_9[0][0]);

    const geo::Matrix<3> test_mat_3(Fw_arr_3);
    const geo::Matrix<9> test_mat_9(Fw_arr_9);

    MATRIX_ARR_COMP(test_mat_3, Fw_arr_3);
    MATRIX_ARR_COMP(test_mat_9, Fw_arr_9);
}

// characteristics
TEST(MatrixTests, characteristic_n) {
    const geo::Matrix<3> test_mat_3{};
    const geo::Matrix<9> test_mat_9{};

    EXPECT_EQ(test_mat_3.n(), 3);
    EXPECT_EQ(test_mat_9.n(), 9);
}

// element access
TEST(MatrixTests, mut_element_access) {
    const auto cpp_arr_9 = rand_matrix<9>();
    std::array<std::array<float, 3>, 3> cpp_arr_3;
    std::copy(cpp_arr_9[0].begin(), cpp_arr_9[0].begin() + 9, cpp_arr_3[0].begin());

    geo::Matrix<3> test_mat_3(cpp_arr_3);
    geo::Matrix<9> test_mat_9(cpp_arr_9);

    for (FwSizeType row = 0; row < 9; row++) {
        for (FwSizeType col = 0; col < 9; col++) {
            if (row < 3 && col < 3) {
                EXPECT_FLOAT_EQ(test_mat_3.cell(row, col), cpp_arr_9[0][3 * row + col])
                    << "Matrix<3> index: (" << row << ", " << col << ")";
                EXPECT_FLOAT_EQ(test_mat_3.cell(row, col), test_mat_3(row, col));
            }
            EXPECT_FLOAT_EQ(test_mat_9.cell(row, col), cpp_arr_9[row][col])
                << "Matrix<9> index: (" << row << ", " << col << ")";
            EXPECT_FLOAT_EQ(test_mat_9(row, col), cpp_arr_9[row][col])
                << "Matrix<9> index: (" << row << ", " << col << ")";
        }
    }
}
TEST(MatrixTests, const_element_access) {
    const auto cpp_arr_9 = rand_matrix<9>();
    std::array<std::array<float, 3>, 3> cpp_arr_3;
    std::copy(cpp_arr_9[0].begin(), cpp_arr_9[0].begin() + 9, cpp_arr_3[0].begin());

    const geo::Matrix<3> test_mat_3(cpp_arr_3);
    const geo::Matrix<9> test_mat_9(cpp_arr_9);

    for (FwSizeType row = 0; row < 9; row++) {
        for (FwSizeType col = 0; col < 9; col++) {
            if (row < 3 && col < 3) {
                EXPECT_FLOAT_EQ(test_mat_3.cell(row, col), cpp_arr_9[0][3 * row + col])
                    << "Matrix<3> index: (" << row << ", " << col << ")";
                // EXPECT_FLOAT_EQ(test_mat_3.cell(row, col), test_mat_3(row, col));
            }
            EXPECT_FLOAT_EQ(test_mat_9.cell(row, col), cpp_arr_9[row][col])
                << "Matrix<9> index: (" << row << ", " << col << ")";
            /* EXPECT_FLOAT_EQ(test_mat_9(row, col), cpp_arr_9[row][col])
                << "Matrix<9> index: (" << row << ", " << col << ")"; */
        }
    }
}
TEST(MatrixTests, mut_element_assignment) {
    const auto cpp_arr_9 = rand_matrix<9>();
    std::array<std::array<float, 3>, 3> cpp_arr_3;
    std::copy(cpp_arr_9[0].begin(), cpp_arr_9[0].begin() + 9, cpp_arr_3[0].begin());

    geo::Matrix<3> test_mat_3(cpp_arr_3);
    geo::Matrix<9> test_mat_9(cpp_arr_9);

    const auto new_arr_9 = rand_matrix<9>();

    for (FwSizeType row = 0; row < 9; row++) {
        for (FwSizeType col = 0; col < 9; col++) {
            if (row < 3 && col < 3) {
                test_mat_3.cell(row, col) = new_arr_9[0][3 * row + col];
            }
            test_mat_9.cell(row, col) = new_arr_9[row][col];
        }
    }

    for (FwSizeType row = 0; row < 9; row++) {
        for (FwSizeType col = 0; col < 9; col++) {
            if (row < 3 && col < 3) {
                EXPECT_FLOAT_EQ(test_mat_3.cell(row, col), new_arr_9[0][3 * row + col])
                    << "Matrix<3> index: (" << row << ", " << col << ")";
            }
            EXPECT_FLOAT_EQ(test_mat_9.cell(row, col), new_arr_9[row][col])
                << "Matrix<9> index: (" << row << ", " << col << ")";
        }
    }
}

// vector
TEST(MatrixTests, row_to_vector) {
    const auto cpp_arr_9 = rand_matrix<9>();
    std::array<std::array<float, 3>, 3> cpp_arr_3;
    std::copy(cpp_arr_9[0].begin(), cpp_arr_9[0].begin() + 9, cpp_arr_3[0].begin());

    const geo::Matrix<3> test_mat_3(cpp_arr_3);
    const geo::Matrix<9> test_mat_9(cpp_arr_9);

    std::array<Vector<3>, 3> rows_3;
    std::array<Vector<9>, 9> rows_9;

    for (FwSizeType row = 0; row < 9; row++) {
        for (FwSizeType col = 0; col < 9; col++) {
            if (row < 3 && col < 3) {
                rows_3[row][col] = cpp_arr_9[0][row * 3 + col];
            }
            rows_9[row][col] = cpp_arr_9[row][col];
        }
    }

    for (FwSizeType i = 0; i < 9; i++) {
        if (i < 3) {
            EXPECT_EQ(rows_3[i], test_mat_3.row_to_vector(i)) << "Matrix<3> row index: " << i;
        }
        EXPECT_EQ(rows_9[i], test_mat_9.row_to_vector(i)) << "Matrix<9> row index: " << i;
    }
}
TEST(MatrixTests, col_to_vector) {
    const auto cpp_arr_9 = rand_matrix<9>();
    std::array<std::array<float, 3>, 3> cpp_arr_3;
    std::copy(cpp_arr_9[0].begin(), cpp_arr_9[0].begin() + 9, cpp_arr_3[0].begin());

    const geo::Matrix<3> test_mat_3(cpp_arr_3);
    const geo::Matrix<9> test_mat_9(cpp_arr_9);

    std::array<Vector<3>, 3> cols_3;
    std::array<Vector<9>, 9> cols_9;

    for (FwSizeType row = 0; row < 9; row++) {
        for (FwSizeType col = 0; col < 9; col++) {
            if (row < 3 && col < 3) {
                cols_3[col][row] = cpp_arr_9[0][row * 3 + col];
            }
            cols_9[col][row] = cpp_arr_9[row][col];
        }
    }

    for (FwSizeType i = 0; i < 9; i++) {
        if (i < 3) {
            EXPECT_EQ(cols_3[i], test_mat_3.col_to_vector(i)) << "Matrix<3> col index: " << i;
        }
        EXPECT_EQ(cols_9[i], test_mat_9.col_to_vector(i)) << "Matrix<9> col index: " << i;
    }
}

TEST(MatrixTests, vector_to_row) {
    const auto cpp_arr_9 = rand_matrix<9>();

    std::array<Vector<3>, 3> rows_3;
    std::array<Vector<9>, 9> rows_9;
    for (FwSizeType row = 0; row < 9; row++) {
        for (FwSizeType col = 0; col < 9; col++) {
            if (row < 3 && col < 3) {
                rows_3[row][col] = cpp_arr_9[0][row * 3 + col];
            }
            rows_9[row][col] = cpp_arr_9[row][col];
        }
    }

    for (FwSizeType row = 0; row < 9; row++) {
        // 0'd matrices
        geo::Matrix<3> test_mat_3{};
        geo::Matrix<9> test_mat_9{};

        // apply
        if (row < 3) {
            test_mat_3.vector_to_row(rows_3[row], row);
        }
        test_mat_9.vector_to_row(rows_9[row], row);

        // ensure function only touches the specific row and leaves the rest 0'd out
        for (FwSizeType i = 0; i < 9; i++) {
            for (FwSizeType j = 0; j < 9; j++) {
                // 3x3
                if (row < 3 && i < 3 && j < 3) {
                    if (i == row) {
                        EXPECT_EQ(rows_9[0][3 * i + j], test_mat_3.cell(i, j))
                            << "Matrix<3> row index: " << row << "; (r, c): (" << i << ", " << j << ")";

                    } else {
                        EXPECT_EQ(0, test_mat_3.cell(i, j))
                            << "Matrix<3> row index: " << row << "; (r, c): (" << i << ", " << j << ")";
                    }
                }

                // 9x9
                if (i == row) {
                    EXPECT_EQ(rows_9[i][j], test_mat_9.cell(i, j))
                        << "Matrix<j> row index: " << row << "; (r, c): (" << i << ", " << j << ")";

                } else {
                    EXPECT_EQ(0, test_mat_9.cell(i, j))
                        << "Matrix<9> row index: " << row << "; (r, c): (" << i << ", " << j << ")";
                }
            }
        }
    }
}

TEST(MatrixTests, vector_to_col) {
    const auto cpp_arr_9 = rand_matrix<9>();
    /*
    for (FwSizeType row = 0; row < 3; row++) {
        for (FwSizeType col = 0; col < 3; col++) {
            std::cout << "(" << row << ", " << col << ") = " << cpp_arr_9[row][col] << ", ";
        }
        std::cout << "\n";
    }
    */

    std::array<Vector<3>, 3> cols_3;
    std::array<Vector<9>, 9> cols_9;
    for (FwSizeType col = 0; col < 9; col++) {
        for (FwSizeType row = 0; row < 9; row++) {
            if (row < 3 && col < 3) {
                cols_3[col][row] = cpp_arr_9[row][col];
            }
            cols_9[col][row] = cpp_arr_9[row][col];
        }
    }

    for (FwSizeType col = 0; col < 9; col++) {
        // 0'd matrices
        geo::Matrix<3> test_mat_3{};
        geo::Matrix<9> test_mat_9{};

        // apply
        if (col < 3) {
            test_mat_3.vector_to_col(cols_3[col], col);
        }
        test_mat_9.vector_to_col(cols_9[col], col);

        // ensure function only touches the specific col and leaves the rest 0'd out
        for (FwSizeType i = 0; i < 9; i++) {
            for (FwSizeType j = 0; j < 9; j++) {
                // 3x3
                if (col < 3 && i < 3 && j < 3) {
                    if (j == col) {
                        EXPECT_EQ(cols_9[j][i], test_mat_3.cell(i, j))
                            << "Matrix<3> col index: " << col << "; (r, c): (" << i << ", " << j << ")";
                    } else {
                        EXPECT_EQ(0, test_mat_3.cell(i, j))
                            << "Matrix<3> col index: " << col << "; (r, c): (" << i << ", " << j << ")";
                    }
                }

                // 9x9
                if (j == col) {
                    EXPECT_EQ(cols_9[j][i], test_mat_9.cell(i, j))
                        << "Matrix<9> col index: " << col << ", (r, c): (" << i << ", " << j << ")";
                } else {
                    EXPECT_EQ(0, test_mat_9.cell(i, j))
                        << "Matrix<9> col index: " << col << "; (r, c): (" << i << ", " << j << ")";
                }
            }
        }
    }
}

// geometry
TEST(MatrixTests, transpose) {
    const auto cpp_arr_9 = rand_matrix<9>();
    std::array<std::array<float, 3>, 3> cpp_arr_3;
    std::copy(cpp_arr_9[0].begin(), cpp_arr_9[0].begin() + 9, cpp_arr_3[0].begin());

    const geo::Matrix<3> test_mat_3(cpp_arr_3);
    const geo::Matrix<9> test_mat_9(cpp_arr_9);

    const auto transp_3 = test_mat_3.transpose();
    const auto transp_9 = test_mat_9.transpose();

    for (FwSizeType col = 0; col < 9; col++) {
        for (FwSizeType row = 0; row < 9; row++) {
            if (row < 3 && col < 3) {
                EXPECT_FLOAT_EQ(cpp_arr_9[0][row * 3 + col], transp_3.cell(col, row))
                    << "Matrix<3> (r, c): (" << row << ", " << col << ")";
            }
            EXPECT_FLOAT_EQ(cpp_arr_9[row][col], transp_9.cell(col, row))
                << "Matrix<3> (r, c): (" << row << ", " << col << ")";
        }
    }
}
TEST(MatrixTests, minor_matrix) {}
TEST(MatrixTests, determinant) {}
TEST(MatrixTests, invert) {}
TEST(MatrixTests, trace) {
    const auto cpp_arr_9 = rand_matrix<9>();
    std::array<std::array<float, 3>, 3> cpp_arr_3;
    std::copy(cpp_arr_9[0].begin(), cpp_arr_9[0].begin() + 9, cpp_arr_3[0].begin());

    const geo::Matrix<3> test_mat_3(cpp_arr_3);
    const geo::Matrix<9> test_mat_9(cpp_arr_9);

    float test_tr_3{}, test_tr_9{};

    // trace is apparently just sum of diagonals sooo..
    for (FwSizeType i = 0; i < 9; i++) {
        if (i < 3) {
            test_tr_3 += cpp_arr_9[0][i * 3 + i];
        }
        test_tr_9 += cpp_arr_9[i][i];
    }

    EXPECT_FLOAT_EQ(test_tr_3, test_mat_3.trace());
    EXPECT_FLOAT_EQ(test_tr_9, test_mat_9.trace());
}

// math
TEST(MatrixTests, matrix_addition) {}
TEST(MatrixTests, matrix_subtraction) {}
TEST(MatrixTests, matrix_multiplication) {}
TEST(MatrixTests, scalar_multiplication) {}

// identity
TEST(MatrixTests, matrix_eye) {
    const auto eye_3 = eye<Matrix<3>>();
    const auto eye_9 = eye<Matrix<9>>();

    for (FwSizeType row = 0; row < 9; row++) {
        for (FwSizeType col = 0; col < 9; col++) {
            if (row < 3 && col < 3) {
                if (row == col) {
                    EXPECT_FLOAT_EQ(1, eye_3.cell(row, col));
                } else {
                    EXPECT_FLOAT_EQ(0, eye_3.cell(row, col));
                }
            }
            if (row == col) {
                EXPECT_FLOAT_EQ(1, eye_9.cell(row, col));
            } else {
                EXPECT_FLOAT_EQ(0, eye_9.cell(row, col));
            }
        }
    }
}
}  // namespace geo
