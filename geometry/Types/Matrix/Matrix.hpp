//  Inertial Measurement Unit Maths Library
//
//  Copyright 2013-2021 Sam Cowen <samuel.cowen@camelsoftware.com>
//  Bug fixes and cleanups by Gé Vissers (gvissers@gmail.com)
//
//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.

#ifndef GEOMETRY_TYPES_GEO_MATRIX_MATRIX_HPP_
#define GEOMETRY_TYPES_GEO_MATRIX_MATRIX_HPP_

#include <algorithm>
#include <array>

#include "Fw/DataStructures/Array.hpp"
#include "Fw/FPrimeBasicTypes.hpp"

#include "../Vector/Vector.hpp"

namespace geo {

/**
 * This class represents a square N by N matrix, including associated mathmatical methods.
 * @tparam N the dimension of the matrix
 * @tparam MATRIX_FLOAT the floating point type to use for the matrix value
 * @tparam MATRIX_CONTAINER the container type to use for storing the matrix's values
 */
template <U8 N, typename MATRIX_FLOAT = F32, typename MATRIX_CONTAINER = std::array<MATRIX_FLOAT, N * N>>
class Matrix : public MATRIX_CONTAINER {
    static_assert(N > 1, "matrix must be at least 2x2");
    static_assert(std::is_floating_point<MATRIX_FLOAT>::value, "the Matrix datatype must be floating point");

    static_assert(
        (N == 3 || N == 9) && (std::is_same<MATRIX_FLOAT, F32>::value || std::is_same<MATRIX_FLOAT, F64>::value) &&
            (std::is_same<MATRIX_CONTAINER, std::array<MATRIX_FLOAT, N * N>>::value),
        "Only allow instantiations of Matrix<...> that already have unit tests written. If you need a new type of "
        "Matrix (new dimension, new floating_t, new container_t), ensure that type has appropriate test coverage.");

  public:
    /**
     * Allows access to the MATRIX_FLOAT type.
     */
    using MATRIX_FLOAT_T = MATRIX_FLOAT;
    /**
     * Allows access to the MATRIX_CONTAINER type.
     */
    using MATRIX_CONTAINER_T = MATRIX_CONTAINER;

    // ctor/dtor

    /**
     * Default ctor.
     */
    Matrix() = default;
    /**
     * Copy ctor.
     * @param other the copied matrix
     */
    Matrix(const Matrix& other) = default;
    /**
     * Move ctor.
     * @param other the moved-from matrix
     */
    Matrix(Matrix&& other) = default;
    /**
     * Copy ctor.
     * @param other the copied matrix
     * @returns new matrix
     */
    Matrix& operator=(const Matrix& other) = default;
    /**
     * Move ctor.
     * @param other the moved-from matrix
     * @returns new matrix
     */
    Matrix& operator=(Matrix&& other) = default;

    /**
     * Creates a square Matrix from a 2D c-style array formatted as [row][column].
     * @param rows the array of rows, containing an array of columns
     */
    explicit Matrix(const MATRIX_FLOAT (&rows)[N][N]) noexcept {
        std::copy(&rows[0][0], &rows[0][0] + (this->n() * this->n()), &MATRIX_CONTAINER::operator[](0));
    }
    /**
     * Creates a square Matrix from a 2D std::array array formatted as [row][column].
     * @param rows the array of rows, containing an array of columns
     */
    explicit Matrix(const std::array<std::array<MATRIX_FLOAT, N>, N> rows) noexcept {
        std::copy(rows[0].begin(), rows[0].begin() + (this->n() * this->n()), &MATRIX_CONTAINER::operator[](0));
    }
    /**
     * Creates a square Matrix from a 2D Fw::Array array formatted as [row][column].
     * @param rows the array of rows, containing an array of columns
     */
    explicit Matrix(const Fw::Array<Fw::Array<MATRIX_FLOAT, N>, N> rows) noexcept {
        std::copy(&rows[0][0], &rows[0][0] + (this->n() * this->n()), &MATRIX_CONTAINER::operator[](0));
    }
    /**
     * Creates a square Matrix from the base container that the matrix uses.
     * @param rows the array of rows, containing an array of columns
     */
    template <typename = std::enable_if<!std::is_same<MATRIX_CONTAINER, std::array<MATRIX_FLOAT, N * N>>::value &&
                                        !std::is_same<MATRIX_CONTAINER, Fw::Array<MATRIX_FLOAT, N * N>>::value>>
    explicit Matrix(const MATRIX_CONTAINER rows) noexcept {
        std::copy(&rows[0], &rows[0] + (this->n() * this->n()), &MATRIX_CONTAINER::operator[](0));
    }

    ~Matrix() = default;

    // characteristics
    /**
     * Returns the dimension of the matrix. An N dimensional matrix has N rows and N columns.
     * @returns matrix dimension
     */
    constexpr U8 n() const noexcept { return N; }

    /**
     * Ensures all elements of the matrix are finite
     * @returns if elements are finit
     */
    bool all_finite() const noexcept {
        for (U8 i = 0; i < this->n(); i++) {
            for (U8 j = 0; j < this->n(); j++) {
                if (!std::isfinite(this->cell(i, j)))
                    return false;
            }
        }
        return true;
    }

    // comparisons
    /**
     * Compares this and other matrix. Returns true iff the value at every index of both matrices is the same, false
     * otherwise.
     * @param other the matrix to compare
     * @returns true if both matrices are identical
     */
    template <typename OTHER_MATRIX_CONT>
    bool operator==(const Matrix<N, MATRIX_FLOAT, OTHER_MATRIX_CONT>& other) const noexcept {
        for (U8 i = 0; i < this->n(); i++) {
            for (U8 j = 0; j < this->n(); j++) {
                if (MATRIX_CONTAINER::operator[](i* this->n() + j) != other[i, j]) {
                    return false;
                }
            }
        }
        return true;
    }
    /**
     * Compares this and other matrix. Returns false iff the value at every index of both matrices is the same, true
     * otherwise.
     * @param other the matrix to compare.
     * @returns true if both matrices are not identical
     */
    template <typename OTHER_MATRIX_CONT>
    bool operator!=(const Matrix<N, MATRIX_FLOAT, OTHER_MATRIX_CONT>& other) const noexcept {
        return !(this->operator==(other));
    }

    // element access
    /**
     * Allows read access to the element at row i and column j of the matrix with bounds checking.
     * @param i the row index
     * @param j the column index
     * @returns element at (i,j)
     */
    MATRIX_FLOAT operator()(const U8 i, const U8 j) const {
        // Fw::Array has bound checking already
        if constexpr (!std::is_same<MATRIX_CONTAINER, Fw::Array<MATRIX_FLOAT, N * N>>::value) {
            FW_ASSERT(i < this->n());
            FW_ASSERT(j < this->n());
        }
        return this->cell(i, j);
    }
    /**
     * Allows read/write access to the element at row i and column j of the matrix with bounds checking.
     * @param i the row index
     * @param j the column index
     * @returns element at (i,j)
     */
    MATRIX_FLOAT& operator()(const U8 i, const U8 j) {
        // Fw::Array has bound checking already
        if constexpr (!std::is_same<MATRIX_CONTAINER, Fw::Array<MATRIX_FLOAT, N * N>>::value) {
            FW_ASSERT(i < this->n());
            FW_ASSERT(j < this->n());
        }
        return this->cell(i, j);
    }

    /**
     * Allows read/write access to the element at row i and column j of the matrix without bounds checking.
     * @param row the row index
     * @param col the column index
     * @returns element at (i,j)
     */
    MATRIX_FLOAT& cell(const U8 row, const U8 col) { return MATRIX_CONTAINER::operator[](row * N + col); }
    /**
     * Allows read access to the element at row i and column j of the matrix without bounds checking.
     * @param row the row index
     * @param col    the column index
     * @returns element at (i,j)
     */
    const MATRIX_FLOAT& cell(const U8 row, const U8 col) const { return MATRIX_CONTAINER::operator[](row * N + col); }

    // vector operations
    /**
     * Returns the specified row of the matrix to a vector with dimension N.
     * @param i the desired row
     * @return a vector of the values of that row
     */
    template <typename VECTOR_CONT = std::array<MATRIX_FLOAT, N>>
    Vector<N, MATRIX_FLOAT, VECTOR_CONT> row_to_vector(const U8 i) const noexcept {
        // Fw::Array has bound checking already
        if constexpr (!std::is_same<MATRIX_CONTAINER, Fw::Array<MATRIX_FLOAT, N * N>>::value) {
            FW_ASSERT(i < this->n());
        }
        Vector<N, MATRIX_FLOAT, VECTOR_CONT> out;
        std::copy(&this->cell(i, 0), &this->cell(i, 0) + this->n(), &out[0]);
        return out;
    }
    /**
     * Returns the specified column of the matrix to a vector with dimension N.
     * @param j the desired column
     * @return a vector of the values of that column
     */
    template <typename VECTOR_CONT = std::array<MATRIX_FLOAT, N>>
    Vector<N, MATRIX_FLOAT, VECTOR_CONT> col_to_vector(const U8 j) const noexcept {
        Vector<N, MATRIX_FLOAT, VECTOR_CONT> out;
        for (U8 i = 0; i < this->n(); i++) {
            out[i] = this->cell(i, j);
        }
        return out;
    }

    /**
     * Overwrites all of the values of the specified row with new values from the provided vector.
     * @param v the vector of new row values
     * @param i the desired row
     */
    template <typename VECTOR_CONT>
    void vector_to_row(const Vector<N, MATRIX_FLOAT, VECTOR_CONT>& v, const U8 i) noexcept {
        // bounds checking from cell(...)
        std::copy(reinterpret_cast<const MATRIX_FLOAT*>(&v), reinterpret_cast<const MATRIX_FLOAT*>(&v) + this->n(),
                  &this->cell(i, 0));
    }

    /**
     * Overwrites all of the values of the specified column with new values from the provided vector.
     * @param v the vector of new row values
     * @param j the desired row
     */
    template <typename VECTOR_CONT>
    void vector_to_col(const Vector<N, MATRIX_FLOAT, VECTOR_CONT>& v, const U8 j) noexcept {
        // bounds checking from cell(...)
        for (U8 i = 0; i < this->n(); i++) {
            this->cell(i, j) = v[i];
        }
    }

    // geometry operations
    /**
     * Creates a matrix which is the transposed (rows and columns swapped) version of this matrix
     * @returns the transposed matrix
     */
    Matrix transpose() const noexcept {
        Matrix ret;
        for (U8 i = 0; i < this->n(); i++) {
            for (U8 j = 0; j < this->n(); j++) {
                ret(j, i) = this->cell(i, j);
            }
        }
        return ret;
    }
    /**
     * Creates a symmetrized matrix. ???
     * @returns the symmetrized matrix
     */
    Matrix symmetrize() const noexcept { return (*this + this->transpose()) * 0.5; }

    /**
     * Returns a matrix with the specified row and column removed, without affecting any other values. The new Matrix
     * wil be of dimension N-1.
     * @param row the row to remove
     * @param col the column to remove
     * @returns the smaller matrix
     */
    Matrix<N - 1> minor_matrix(const U8 row, const U8 col) const noexcept {
        // Fw::Array has bound checking already
        if constexpr (!std::is_same<MATRIX_CONTAINER, Fw::Array<MATRIX_FLOAT, N * N>>::value) {
            FW_ASSERT(row < this->n());
            FW_ASSERT(col < this->n());
        }
        Matrix<N - 1> ret;
        for (U8 i = 0, im = 0; i < this->n(); i++) {
            if (i == row)
                continue;

            for (U8 j = 0, jm = 0; j < this->n(); j++) {
                if (j != col) {
                    ret(im, jm++) = this->cell(i, j);
                }
            }
            im++;
        }
        return ret;
    }
    /**
     * Computes the determinate of this matrix.
     * @returns determinate
     */
    MATRIX_FLOAT determinant() const noexcept {
        if (N == 1) {
            return this->cell(0, 0);
        }
        F64 det = 0.0, sign = 1.0;
        for (U8 i = 0; i < this->n(); ++i, sign = -sign) {
            det += sign * this->cell(0, i) * this->minor_matrix(0, i).determinant();
        }
        return static_cast<MATRIX_FLOAT>(det);
    }
    /**
     * Returns an inverted copy of this matrix.
     * @returns the inverted matrix.
     */
    Matrix invert() const noexcept {
        Matrix out;
        const auto det = this->determinant();

        for (U8 i = 0; i < this->n(); i++) {
            for (U8 j = 0; j < this->n(); j++) {
                out(i, j) = this->minor_matrix(j, i).determinant() / det;
                if ((i + j) % 2 == 1) {
                    out(i, j) = -out(i, j);
                }
            }
        }
        return out;
    }
    /**
     * Computes the trace of this matrix. The trace is the sum of diagonal elements.
     * @returns trace
     */
    MATRIX_FLOAT trace() const {
        F64 tr = 0.0;
        for (U8 i = 0; i < N; ++i)
            tr += this->cell(i, i);
        return static_cast<MATRIX_FLOAT>(tr);
    }

    // math operations
    /**
     * Adds this and the other matrix by adding their elements at each index.
     * @param other the matrix to add
     * @returns the matrix sum
     */
    template <typename OTHER_MATRIX_CONT>
    Matrix operator+(const Matrix<N, MATRIX_FLOAT, OTHER_MATRIX_CONT>& other) const noexcept {
        Matrix<N, MATRIX_FLOAT, OTHER_MATRIX_CONT> out;
        for (U8 ij = 0; ij < this->n() * this->n(); ++ij) {
            out[ij] = MATRIX_CONTAINER::operator[](ij) + other[ij];
        }
        return out;
    }
    /**
     * Subtracts this and the other matrix by adding their elements at each index.
     * @param other the matrix to subtract
     * @returns the matrix difference
     */
    template <typename OTHER_MATRIX_CONT>
    Matrix operator-(const Matrix<N, MATRIX_FLOAT, OTHER_MATRIX_CONT>& other) const noexcept {
        Matrix<N, MATRIX_FLOAT, OTHER_MATRIX_CONT> ret;
        for (U8 ij = 0; ij < this->n() * this->n(); ++ij) {
            ret[ij] = MATRIX_CONTAINER::operator[](ij) - other[ij];
        }
        return ret;
    }
    /**
     * Multiplies this and the other matrix via the standard matrix multiplication formula. Matrix must be at least
     * dimension 2.
     * @param other the matrix to multiply by
     * @returns the matrix product
     */
    template <typename OTHER_MATRIX_CONT>
    Matrix operator*(const Matrix<N, MATRIX_FLOAT, OTHER_MATRIX_CONT>& other) const noexcept {
        static_assert(N > 1);

        Matrix<N, MATRIX_FLOAT, OTHER_MATRIX_CONT> ret;

        for (U8 i = 0; i < this->n(); i++) {
            auto row = this->row_to_vector(i);
            for (U8 j = 0; j < N; j++) {
                ret(i, j) = row.dot(other.col_to_vector(j));
            }
        }

        return ret;
    }
    /**
     * Multiplies matrix by vector v via the standard formula.
     * @param v the vector to multiply by
     * @returns the output vector
     */
    template <typename OTHER_VECTOR_CONT>
    geo::Vector<N, MATRIX_FLOAT, OTHER_VECTOR_CONT> operator*(
        const geo::Vector<N, MATRIX_FLOAT, OTHER_VECTOR_CONT>& v) const noexcept {
        geo::Vector<N, MATRIX_FLOAT, OTHER_VECTOR_CONT> out{};
        for (U8 i = 0; i < N; i++) {
            for (U8 j = 0; j < 3; j++) {
                v[i] += this->cell(i, j);
            }
        }
        return v;
        /*
        return geo::Vector<N, F64>({this->cell(0, 0) * v.x() + this->(0, 1) * v.y() + this->cell(0, 2) * v.z(),
                                    this->cell(1, 0) * v.x() + this->(1, 1) * v.y() + this->cell(1, 2) * v.z(),
                                    this->cell(2, 0) * v.x() + this->(2, 1) * v.y() + this->cell(2, 2) * v.z()});
                                    */
    }
};

/**
 * Returns a copy of this matrix uniformly scaled by the input.
 * @param mat the input matrix
 * @param scalar the value to scale by
 * @returns the scaled matrix
 */
template <U8 N, typename FLOAT_T, typename MATRIX_CONT>
Matrix<N, FLOAT_T, MATRIX_CONT> operator*(const Matrix<N, FLOAT_T, MATRIX_CONT> mat, const FLOAT_T scalar) noexcept {
    Matrix<N, FLOAT_T, MATRIX_CONT> out;
    for (U8 i = 0; i < N; i++) {
        for (U8 j = 0; j < N; j++) {
            out.cell(i, j) = mat.cell(i, j) * scalar;
        }
    }
    return out;
}

/**
 * Cross-product matrix: skew(a) * b := a.cross(b).
 *
 */
template <typename FLOAT_T, typename VECTOR_CONT>
inline Matrix<3, FLOAT_T> skew(const geo::Vector<3, FLOAT_T, VECTOR_CONT>& a) noexcept {
    Matrix<3, FLOAT_T> out{};
    out.cell(0, 1) = -a.z();
    out.cell(0, 2) = a.y();
    out.cell(1, 0) = a.z();
    out.cell(1, 2) = -a.x();
    out.cell(2, 0) = -a.y();
    out.cell(2, 1) = a.x();
    return out;
}

/**
 * Creates an identity matrix of the provided type. Call eye<Matrix<3>>() for a 3D identity matrix.
 * @returns identity matrix
 */
template <typename MATRIX_T>
constexpr MATRIX_T eye() noexcept {
    MATRIX_T out{};
    for (U8 i = 0; i < out.n(); i++) {
        out.cell(i, i) = 1;
    }
    return out;
}
/**
 * Creates a matrix that is zeros except for the diagonals, which are the supplied value.
 * @param d the value of the diagonal of the matrix
 * @returns the matrix
 */
template <typename MATRIX_T, typename FLOAT_T>
constexpr MATRIX_T diag(const FLOAT_T d) noexcept {
    return eye<MATRIX_T>() * d;
}

}  // namespace geo

#endif  // GEOMETRY_TYPES_GEO_MATRIX_MATRIX_HPP_
