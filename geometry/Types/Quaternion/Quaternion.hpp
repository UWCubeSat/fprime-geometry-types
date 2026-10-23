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

#ifndef GEOMETRY_TYPES_GEO_QUATERNION_QUATERNION_HPP_
#define GEOMETRY_TYPES_GEO_QUATERNION_QUATERNION_HPP_

#include <array>
#include <cmath>
#include <initializer_list>

#include "geo/Types/geometry/QuaternionBaseArrayAc.hpp"

#include "../Matrix/Matrix.hpp"
#include "../Vector/Vector.hpp"

namespace geo {

/**
 * This represents a Quaternion object and contains associated mathmatical operations. It is integrated with F' to
 * simple passing of the Quaternion between F' components. Users are intended to only interact with the Quaternion
 * class, not QuaternionBase to avoid the problem of scalar first versus last confusion and instead treat the order of
 * the components as an implementation detail. This concern isn't just academic and this mistake has been made on HS2
 * code (check the SDD it's wrong).
 */
class Quaternion : public QuaternionBase {
    static_assert(std::is_floating_point<QuaternionBase::ElementType>::value,
                  "it looks like you've changed the type of QuaternionBase"
                  "to a non-floating point type in the .fpp file. don't do that.");

  public:
    // default ctor's
    Quaternion() = delete;  // i cannot think of a reason to let someone create an empty quat, seems like its
                            // asking for a bad time.
    /**
     * Copy ctor.
     * @param other the copied Quaternion
     */
    Quaternion(const Quaternion& other) = default;
    /**
     * Move ctor.
     * @param other the moved-from Quaternion
     */
    Quaternion(Quaternion&& other) = default;
    /**
     * Copy ctor.
     * @param other the copied Quaternion
     * @returns Quaternion copy
     */
    Quaternion& operator=(const Quaternion& other) = default;
    /**
     * Move ctor.
     * @param other the moved-from Quaternion
     * @returns Quaternion copy
     */
    Quaternion& operator=(Quaternion&& other) = default;

    /**
     * Creates Quaternion from real scalar and imaginary vector as c array.
     * @param real the real component
     * @param imaginary the imaginary component in order i,j,k
     */
    Quaternion(const QuaternionBase::ElementType real, const QuaternionBase::ElementType (&imaginary)[3]) noexcept;
    /**
     * Creates quat from real scalar and imaginary vector as std::array.
     * @param real the real component
     * @param imaginary the imaginary component in order i,j,k
     */
    Quaternion(const QuaternionBase::ElementType real,
               const std::array<QuaternionBase::ElementType, 3>& imaginary) noexcept;
    /**
     * Creates quat from real scalar and imaginary vector as Fw::Array.
     * @param real the real component
     * @param imaginary the imaginary component in order i,j,k
     */
    Quaternion(const QuaternionBase::ElementType real,
               const Fw::Array<QuaternionBase::ElementType, 3>& imaginary) noexcept;
    /**
     * Creates Quaternion from real scalar and imaginary vector as a 3D vector.
     * @param real the real component
     * @param imaginary the imaginary component in order i,j,k
     * @tparam VECTOR_CONT the container type the vector uses
     */
    template <typename VECTOR_CONT>
    Quaternion(const QuaternionBase::ElementType real,
               Vector<3, QuaternionBase::ElementType, VECTOR_CONT> imaginary) noexcept
        : Quaternion(real, {imaginary.x(), imaginary.y(), imaginary.z()}) {}
    template <typename VECTOR_FLOAT, typename VECTOR_CONT>
    /**
     * Creates Quaternion from real scalar and imaginary vector as a 3D vector.
     * @param real the real component
     * @param imaginary the imaginary component in order i,j,k
     * @tparam VECTOR_CONT the container type the vector uses
     * @tparam VECTOR_FLOAT the floating type the vector uses
     */
    Quaternion(const QuaternionBase::ElementType real, Vector<3, VECTOR_FLOAT, VECTOR_CONT> imaginary) noexcept
        : Quaternion(real,
                     {static_cast<QuaternionBase::ElementType>(imaginary.x()),
                      static_cast<QuaternionBase::ElementType>(imaginary.y()),
                      static_cast<QuaternionBase::ElementType>(imaginary.z())}) {}

    /**
     * Creates Quaternion from the Fw auto-generated base array.
     * @param other the Fw QuaternionBase
     */
    explicit Quaternion(const QuaternionBase& other) noexcept : QuaternionBase(other) {}

    // comparisons
    /**
     * Compares this and the other Quaternion and returns true iff all values are the same.
     * @param other the quaternion to compare
     * @returns true if both quaternions are identical
     */
    bool operator==(const Quaternion& other) const;
    /**
     * Compares this and the other QuaternionBase and returns true iff all values are the same.
     * @param other the quaternion to compare
     * @returns true if both quaternions are identical
     */
    inline bool operator==(const QuaternionBase& other) const { return (*this == Quaternion(other)); }

    /**
     * Compares this and the other Quaternion and returns false iff all values are the same.
     * @param other the quaternion to compare
     * @returns false if both quaternions are identical
     */
    bool operator!=(const Quaternion& other) const { return !(this->operator==(other)); }
    /**
     * Compares this and the other QuaternionBase and returns true iff all values are the same.
     * @param other the quaternion to compare
     * @returns false if both quaternions are identical
     */
    inline bool operator!=(const QuaternionBase& other) const { return !(this->operator==(other)); }

    /**
     * Explicitly casts to const Fw auto-generated base.
     * @returns const QuaternionBase containing same quat value
     */
    QuaternionBase to_base() const noexcept { return *dynamic_cast<const QuaternionBase*>(this); }
    /**
     * Explicitly casts to  Fw auto-generated base.
     * @returns QuaternionBase containing same quat value
     */
    QuaternionBase to_base() noexcept { return *dynamic_cast<QuaternionBase*>(this); }

    // elements
    /**
     * Accesses scalar component.
     * @returns scalar value
     */
    inline QuaternionBase::ElementType& w() { return QuaternionBase::operator[](0); }
    /**
     * Accesses first imaginary component.
     * @returns i value
     */
    inline QuaternionBase::ElementType& x() { return QuaternionBase::operator[](1); }
    /**
     * Accesses second imaginary component.
     * @returns j value
     */
    inline QuaternionBase::ElementType& y() { return QuaternionBase::operator[](2); }
    /**
     * Accesses third imaginary component.
     * @returns k value
     */
    inline QuaternionBase::ElementType& z() { return QuaternionBase::operator[](3); }

    /**
     * Accesses const scalar component.
     * @returns w value
     */
    inline QuaternionBase::ElementType w() const { return QuaternionBase::operator[](0); }
    /**
     * Accesses const first imaginary component.
     * @returns i value
     */
    inline QuaternionBase::ElementType x() const { return QuaternionBase::operator[](1); }
    /**
     * Accesses const second imaginary component.
     * @returns j value
     */
    inline QuaternionBase::ElementType y() const { return QuaternionBase::operator[](2); }
    /**
     * Accesses const first imaginary component.
     * @returns k value
     */
    inline QuaternionBase::ElementType z() const { return QuaternionBase::operator[](3); }

    // scaling operations
    /**
     * Returns the magnitude of the quat. For a valid quat, this should always be 1.
     * @returns magnitude
     */
    QuaternionBase::ElementType magnitude() const;
    /**
     * Returns a value of the quat scaled by the desired amount. For a valid quat with magnitude 1, scaling by
     * any number other than 1 will produce an invalid quat. This is identical to the * operator.
     * @param scalar the value to scale the quat by
     * @returns the scaled quat
     */
    Quaternion scale(QuaternionBase::ElementType scalar) const;
    /**
     * Scales this Quaternion so that its magnitude is 1.0.
     */
    void normalize();

    /**
     * Returns the quat conjugate of this Quaternion.
     * @returns quat conjugate.
     */
    Quaternion conjugate() const;

    // from geometry
    /**
     * Creates a quaternion from a vector and a rotation
     * @param axis the axis to rotate around
     * @param theta the angle to rotate around the axis
    j
    template <typename VECTOR_T, typename VECTOR_CONT>
    void from_axis_angle(const Vector<3, VECTOR_T, VECTOR_CONT>& axis, QuaternionBase::ElementType theta) {
        this->w() = std::cos(theta / 2);
        // only need to calculate sine of half theta once
        QuaternionBase::ElementType sht = std::sin(theta / 2);
        this->x() = axis.x() * sht;
        this->y() = axis.y() * sht;
        this->z() = axis.z() * sht;
    }

    //void from_matrix(const Matrix<3>& m);

    // to geometry
    template <typename VECTOR_T, typename VECTOR_CONT>
    void to_axis_angle(Vector<3, VECTOR_T, VECTOR_CONT>& axis, QuaternionBase::ElementType& angle) const {
        QuaternionBase::ElementType sqw = sqrt(1 - std::pow(this->w(), 2));
        if (sqw == 0)  // it's a singularity and divide by zero, avoid
            return;

        angle = 2 * std::acos(this->w());
        axis.x() = this->x() / sqw;
        axis.y() = this->y() / sqw;
        axis.z() = this->z() / sqw;
    }
    Matrix<3> to_matrix() const;
    // Returns euler angles that represent the quaternion.  Angles are
    // returned in rotation order and right-handed about the specified
    // axes:
    //
    //   v[0] is applied 1st about z (ie, roll)
    //   v[1] is applied 2nd about y (ie, pitch)
    //   v[2] is applied 3rd about x (ie, yaw)
    //
    // Note that this means result.x() is not a rotation about x;
    // similarly for result.z().
    //
    template <typename VECTOR_T, typename VECTOR_CONT>
    Vector<3, VECTOR_T, VECTOR_CONT> euler() const {
        const QuaternionBase::ElementType sqw = std::pow(this->w(), 2);
        const QuaternionBase::ElementType sqx = std::pow(this->x(), 2);
        const QuaternionBase::ElementType sqy = std::pow(this->y(), 2);
        const QuaternionBase::ElementType sqz = std::pow(this->z(), 2);

        return Vector<3, VECTOR_T, VECTOR_CONT>(
            {std::atan2(2.0 * (this->x() * this->y() + this->z() * this->w()), (sqx - sqy - sqz + sqw)),
             std::asin(-2.0 * (this->x() * this->z() - this->y() * this->w()) / (sqx + sqy + sqz + sqw)),
             std::atan2(2.0 * (this->y() * this->z() + this->x() * this->w()), (-sqx - sqy + sqz + sqw))});
    }
    template <typename VECTOR_T = Vector3DBase::ElementType, typename VECTOR_CONT = Vector3DBase>
    Vector<3, VECTOR_T, VECTOR_CONT> angular_velocity(const QuaternionBase::ElementType dt) const {
        Quaternion one({1, 0, 0, 0});
        Quaternion delta = one - *this;
        Quaternion r = (delta / dt);
        r = r * 2;
        r = r * one;

        return Vector<3, VECTOR_T, VECTOR_CONT>({r.x(), r.y(), r.z()});
    }

    template <typename VECTOR_T, typename VECTOR_CONT>
    Vector<3, VECTOR_T, VECTOR_CONT> rotate_vector(const Vector<3, VECTOR_T, VECTOR_CONT>& v) const {
        const Vector<3, VECTOR_T, VECTOR_CONT> qv({this->x(), this->y(), this->z()});
        const Vector<3, VECTOR_T, VECTOR_CONT> t = qv.cross(v) * 2.0;
        return v + t * this->w() + qv.cross(t);
    }
    template <typename VECTOR_2_T,
              typename VECTOR_2_CONT,
              typename VECTOR_3_T = Vector3DBase::ElementType,
              typename VECTOR_3_CONT = Vector3DBase>
    Vector<3, VECTOR_3_T, VECTOR_3_CONT> rotate_vector(const Vector<2, VECTOR_2_T, VECTOR_2_CONT>& v) const {
        return this->rotate_vector(Vector<3, VECTOR_3_T, VECTOR_3_CONT>({v.x(), v.y(), 0}));
    }
    */
    /**
     * Multiplies this and the other Quaternion.
     * @param other the Quaternion to multiply by
     * @returns the Quaternion product
     */
    Quaternion operator*(const Quaternion& other) const;
    /**
     * Multiplies this Quaternion by a scalar value.
     * @param scalar the value to multiply by
     * @return the Quaternion product
     */
    Quaternion operator*(const QuaternionBase::ElementType scalar) const;

    /**
     * Divides this Quaternion by a scalar value.
     * @param scalar the value to divide by
     * @return the Quaternion divident
     */
    Quaternion operator/(const QuaternionBase::ElementType scalar) const;

    /**
     * Adds this and the other Quaternion.
     * @param other the Quaternion to add
     * @returns the Quaternion sum
     */
    Quaternion operator+(const Quaternion& other) const;
    /**
     * Subtracts this and the other Quaternion.
     * @param other the Quaternion to subtract by
     * @returns the Quaternion difference
     */
    Quaternion operator-(const Quaternion& other) const;
};
}  // namespace geo
#endif  // GEOMETRY_TYPES_GEO_QUATERNION_QUATERNION_HPP_
