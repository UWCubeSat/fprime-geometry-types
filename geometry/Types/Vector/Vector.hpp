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

#ifndef GEOMETRY_TYPES_GEO_VECTOR_VECTOR_HPP_
#define GEOMETRY_TYPES_GEO_VECTOR_VECTOR_HPP_

#include <algorithm>
#include <cmath>

#include "Fw/DataStructures/Array.hpp"

#include "lib/fprime-geometry-types/geometry/Types/Vector3DBaseAc.hpp"

namespace geo {

/**
 * This class represents a geometrical vector and its associated mathmatical functions. Its design allows easy
 * integration with F'.
 * @tparam N the vector dimension
 * @tparam VECTOR_FLOAT the floating point type to use for each vector value
 * @tparam VECTOR_CONTAINER the container used to store the vector values
 */
template <uint8_t N, typename VECTOR_FLOAT = F32, typename VECTOR_CONTAINER = std::array<VECTOR_FLOAT, N>>
class Vector : public VECTOR_CONTAINER {
    static_assert(N > 1, "cannot create 1-dimensional Vector");
    static_assert(std::is_floating_point<VECTOR_FLOAT>::value, "the Vector datatype must be floating point");

    static_assert(
        (N == 3 || N == 9) && (std::is_same<VECTOR_FLOAT, float>::value) &&
            (std::is_same<VECTOR_CONTAINER, std::array<VECTOR_FLOAT, N>>::value ||
             std::is_same<VECTOR_CONTAINER, Vector3DBase>::value),
        "Only allow instantiations of Vector<...> that already have unit tests written. If you need a new type of "
        "vector (new dimension, new floating_t, new container_t), ensure that type has appropriate test coverage.");

  public:
    // ctor / dtor
    /**
     * Default ctor.
     */
    Vector() = default;
    /**
     * Copy ctor.
     * @param other the copied vector
     */
    Vector(const Vector& other) = default;
    /**
     * Move ctor.
     * @param other the moved-from vector
     */
    Vector(Vector&& other) = default;
    /**
     * Copy ctor.
     * @param other the copied vector
     * @returns new vector
     */
    Vector& operator=(const Vector& other) = default;
    /**
     * Move ctor.
     * @param other the moved-from vector
     * @returns new vector
     */
    Vector& operator=(Vector&& other) = default;

    /**
     * Creates vector from a c array.
     * @param vals the array of values
     */
    explicit Vector(const VECTOR_FLOAT (&vals)[N]) noexcept {
        std::copy(&vals[0], &vals[0] + N, &this->VECTOR_CONTAINER::operator[](0));
    }
    /**
     * Creates vector from a c++ array.
     * @param vals the array of values
     */
    explicit Vector(const std::array<VECTOR_FLOAT, N>& vals) noexcept {
        std::copy(vals.begin(), vals.end(), &this->VECTOR_CONTAINER::operator[](0));
    }
    /**
     * Creates vector from am Fw array.
     * @param vals the array of values
     */
    explicit Vector(const Fw::Array<VECTOR_FLOAT, N>& vals) noexcept {
        std::copy(&vals[0], &vals[0] + N, &this->VECTOR_CONTAINER::operator[](0));
    }
    /**
     * Creates vector from the vector base container.
     * @param vals the array of values
     */
    template <typename = std::enable_if<!std::is_same<VECTOR_CONTAINER, std::array<VECTOR_FLOAT, N>>::value &&
                                        !std::is_same<VECTOR_CONTAINER, Fw::Array<VECTOR_FLOAT, N>>::value>>
    explicit Vector(const VECTOR_CONTAINER vals) noexcept {
        // allow base ctor i.f.f. base ctor is not also std array ctor
        std::copy(&vals[0], &vals[0] + N, &this->VECTOR_CONTAINER::operator[](0));
    }

    ~Vector() = default;

    // characteristics
    /**
     * Returns the number of elements in the vector.
     * @returns num elements.
     */
    constexpr uint8_t n() const noexcept { return N; }

    // comparisons
    /**
     * Compares this and the other vector and returns true iff all values are the same.
     * @param other the vector to compare
     * @returns true if both vector are identical
     */
    template <typename OTHER_VECTOR_CONT>
    bool operator==(const Vector<N, VECTOR_FLOAT, OTHER_VECTOR_CONT>& other) const noexcept {
        for (uint8_t i = 0; i < this->n(); i++) {
            if (this->operator[](i) != other[i]) {
                return false;
            }
        }
        return true;
    }
    /**
     * Compares this and the other vector and returns false iff all values are the same.
     * @param other the vector to compare
     * @returns false if both vector are identical
     */
    bool operator!=(const Vector& other) const noexcept { return !(this->operator==(other)); }

    // indexed access
    /**
     * Allows read/write access to the element at index i of the vector with bounds checking.
     * @param i the vector index
     * @return element at index
     */
    VECTOR_FLOAT& operator[](const uint8_t i) {
        if constexpr (!std::is_same<VECTOR_CONTAINER,
                                    Fw::Array<VECTOR_FLOAT, N>>::value) {  // Fw::Array has bound checking already
            FW_ASSERT(i < this->n());
        }
        return VECTOR_CONTAINER::operator[](i);
    }
    /**
     * Allows read access to the element at index i of the vector with bounds checking.
     * @param i the vector index
     * @return element at index
     * 
     */
    VECTOR_FLOAT operator[](const uint8_t i) const {
        if constexpr (!std::is_same<VECTOR_CONTAINER,
                                    Fw::Array<VECTOR_FLOAT, N>>::value) {  // Fw::Array has bound checking already
            FW_ASSERT(i < this->n());
        }
        return VECTOR_CONTAINER::operator[](i);
    }

    // named access
    /**
     * Allows read/write access to the first element of the vector.
     * @returns the first vector element
     */
    VECTOR_FLOAT& x() noexcept { return this->operator[](0); }
    /**
     * Allows read/write access to the second element of the vector. Vector.n() must be at least 2.
     * @returns the second vector element
     */
    VECTOR_FLOAT& y() noexcept {
        static_assert(N >= 2, "vector must be at least degree 2 to have a y()");
        return this->operator[](1);
    }
    /**
     * Allows read/write access to the third element of the vector. Vector.n() must be at least 3.
     * @returns the third vector element
     */
    VECTOR_FLOAT& z() noexcept {
        static_assert(N >= 3, "vector must be at least degree 3 to have a z()");
        return this->operator[](2);
    }

    /**
     * Allows read access to the first element of the vector.
     * @returns the first vector element
     */
    VECTOR_FLOAT x() const noexcept { return this->operator[](0); }
    /**
     * Allows read access to the second element of the vector. Vector.n() must be at least 2.
     * @returns the second vector element
     */
    VECTOR_FLOAT y() const noexcept {
        static_assert(N >= 2, "vector must be at least degree 2 to have a y()");
        return this->operator[](1);
    }
    /**
     * Allows read access to the third element of the vector. Vector.n() must be at least 3.
     * @returns the third vector element
     */
    VECTOR_FLOAT z() const noexcept {
        static_assert(N >= 3, "vector must be at least degree 3 to have an z()");
        return this->operator[](2);
    }

    // geometry operations
    /**
     * Calculates the scalar magnitude of the vector.
     * @returns magnitude e
     */
    VECTOR_FLOAT magnitude() const noexcept {
        double res = 0;
        for (uint8_t i = 0; i < this->n(); i++)
            res += std::pow(static_cast<double>(this->VECTOR_CONTAINER::operator[](i)), 2.0);
        return static_cast<VECTOR_FLOAT>(std::sqrt(res));
    }
    /**
     * Uniformly scales the vector so that its magnitude is 1.
     */
    void normalize() noexcept {
        const VECTOR_FLOAT mag = this->magnitude();
        //    if (mag == VECTOR_FLOAT(1)) {
        //      return;
        // }
        for (uint8_t i = 0; i < this->n(); i++) {
            this->VECTOR_CONTAINER::operator[](i) /= mag;
        }
    }
    /**
     * Uniformly scales the vector by the provided scalar.
     * @param scalar the value to scale the vector by
     * @tparam OTHER_VECTOR_CONT the container type of the arg vector
     * @returns the scaled vector
     */
    template <typename OTHER_VECTOR_CONT = VECTOR_CONTAINER>
    Vector<N, VECTOR_FLOAT, OTHER_VECTOR_CONT> scale(const VECTOR_FLOAT scalar) const noexcept {
        Vector<N, VECTOR_FLOAT, OTHER_VECTOR_CONT> ret;
        for (uint8_t i = 0; i < this->n(); i++)
            ret[i] = this->VECTOR_CONTAINER::operator[](i) * scalar;
        return ret;
    }
    /**
     * Flips the sign of all values in the vector without affecting their magnitude. Equivalent to scaling by -1.
     * @return the inverted vector.
     */
    Vector invert() const noexcept { return this->scale(-1); }
    /**
     * Computes the dot (scalar) product of this and the other vector.
     * @param other the vector to dot.
     * @returns the resultant product
     */
    VECTOR_FLOAT dot(const Vector& other) const noexcept {
        VECTOR_FLOAT out = 0;
        for (uint8_t i = 0; i < this->n(); i++)
            out += this->VECTOR_CONTAINER::operator[](i) * other[i];
        return out;
    }
    /**
     * Computes the cross (vector) product of this and the other vector. Only available for vectors of dimension 3.
     * @param other the vector to cross.
     * @returns the resultant vector
     */
    template <typename OTHER_VECTOR_CONT>
    Vector<N, VECTOR_FLOAT, OTHER_VECTOR_CONT> cross(
        const Vector<N, VECTOR_FLOAT, OTHER_VECTOR_CONT>& other) const noexcept {
        static_assert(N == 3, "cross product only defined for 3D Vector");  // sorry R7
        return Vector<N, VECTOR_FLOAT, OTHER_VECTOR_CONT>(
            {this->operator[](1) * other[2] - this->operator[](2) * other[1],
             this->operator[](2) * other[0] - this->operator[](0) * other[2],
             this->operator[](0) * other[1] - this->operator[](1) * other[0]});
    }

    // math operations
    template <typename OTHER_VECTOR_CONT>
    /**
     * Adds this and the other vector.
     * @param other the vector to add
     * @returns the resultant vector
     */
    Vector<N, VECTOR_FLOAT, OTHER_VECTOR_CONT> operator+(
        const Vector<N, VECTOR_FLOAT, OTHER_VECTOR_CONT>& other) const noexcept {
        Vector<N, VECTOR_FLOAT, OTHER_VECTOR_CONT> out;
        for (uint8_t i = 0; i < this->n(); i++) {
            out[i] = VECTOR_CONTAINER::operator[](i) + other[i];
        }
        return out;
    }
    /**
     * Subtracts this and the other vector.
     * @param other the vector to add
     * @returns the resultant vector
     */
    template <typename OTHER_VECTOR_CONT>
    Vector<N, VECTOR_FLOAT, OTHER_VECTOR_CONT> operator-(
        const Vector<N, VECTOR_FLOAT, OTHER_VECTOR_CONT>& other) const noexcept {
        Vector<N, VECTOR_FLOAT, OTHER_VECTOR_CONT> out;
        for (uint8_t i = 0; i < this->n(); i++) {
            out[i] = VECTOR_CONTAINER::operator[](i) - other[i];
        }
        return out;
    }

    /**
     * Multiplies this vector by a scalar. Equivalent to scaling.
     * @param scalar the value to scale by
     * @returns the resultant vector
     */
    Vector operator*(const VECTOR_FLOAT scalar) const noexcept { return this->scale(scalar); }
    /**
     * Divides this vector by a scalar. Equivalent to scaling by 1/scalar.
     * @param scalar the value to divide by
     * @returns the resultant vector
     */
    Vector operator/(const VECTOR_FLOAT scalar) const noexcept { return this->scale(VECTOR_FLOAT(1.0) / scalar); }
};

using Vector3D = Vector<3, Vector3DBase::ElementType, Vector3DBase>;

}  // namespace geo
#endif  // GEOMETRY_TYPES_GEO_VECTOR_VECTOR_HPP_
