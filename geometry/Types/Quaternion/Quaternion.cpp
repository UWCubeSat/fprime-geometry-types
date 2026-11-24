#include "Quaternion.hpp"

#include <algorithm>

namespace geo {

Quaternion::Quaternion() : QuaternionBase({1, 0, 0, 0}) {}

Quaternion::Quaternion(const QuaternionBase::ElementType real,
                       const QuaternionBase::ElementType (&imaginary)[3]) noexcept
    : QuaternionBase({real, imaginary[0], imaginary[1], imaginary[2]}) {}

Quaternion::Quaternion(const QuaternionBase::ElementType real,
                       const std::array<QuaternionBase::ElementType, 3>& imaginary) noexcept
    : QuaternionBase({real, imaginary[0], imaginary[1], imaginary[2]}) {}

Quaternion::Quaternion(const QuaternionBase::ElementType real,
                       const Fw::Array<QuaternionBase::ElementType, 3>& imaginary) noexcept
    : QuaternionBase({real, imaginary[0], imaginary[1], imaginary[2]}) {}

bool Quaternion::operator==(const Quaternion& other) const {
    return ((this->w() == other.w()) && (this->x() == other.x()) && (this->y() == other.y()) &&
            (this->z() == other.z()));
}

QuaternionBase::ElementType Quaternion::magnitude() const {
    return std::sqrt(
        std::pow(this->w(), QuaternionBase::ElementType(2)) + std::pow(this->x(), QuaternionBase::ElementType(2)) +
        std::pow(this->y(), QuaternionBase::ElementType(2)) + std::pow(this->z(), QuaternionBase::ElementType(2)));
}
Quaternion Quaternion::scale(QuaternionBase::ElementType scalar) const {
    return Quaternion({this->w() * scalar, this->x() * scalar, this->y() * scalar, this->z() * scalar});
}

void Quaternion::normalize() {
    *this = this->scale(QuaternionBase::ElementType(1) / this->magnitude());
}

Quaternion Quaternion::conjugate() const {
    return Quaternion({this->w(), -this->x(), -this->y(), -this->z()});
}

/*
void Quaternion::from_matrix(const Matrix<3>& m) {
    const QuaternionBase::ElementType tr = m.trace();

    QuaternionBase::ElementType S;
    if (tr > 0) {
        S = std::sqrt(tr + 1.0) * 2;
        this->w() = 0.25 * S;
        this->x() = (m(2, 1) - m(1, 2)) / S;
        this->y() = (m(0, 2) - m(2, 0)) / S;
        this->z() = (m(1, 0) - m(0, 1)) / S;
    } else if (m(0, 0) > m(1, 1) && m(0, 0) > m(2, 2)) {
        S = std::sqrt(1.0 + m(0, 0) - m(1, 1) - m(2, 2)) * 2;
        this->w() = (m(2, 1) - m(1, 2)) / S;
        this->x() = 0.25 * S;
        this->y() = (m(0, 1) + m(1, 0)) / S;
        this->z() = (m(0, 2) + m(2, 0)) / S;
    } else if (m(1, 1) > m(2, 2)) {
        S = std::sqrt(1.0 + m(1, 1) - m(0, 0) - m(2, 2)) * 2;
        this->w() = (m(0, 2) - m(2, 0)) / S;
        this->x() = (m(0, 1) + m(1, 0)) / S;
        this->y() = 0.25 * S;
        this->z() = (m(1, 2) + m(2, 1)) / S;
    } else {
        S = std::sqrt(1.0 + m(2, 2) - m(0, 0) - m(1, 1)) * 2;
        this->w() = (m(1, 0) - m(0, 1)) / S;
        this->x() = (m(0, 2) + m(2, 0)) / S;
        this->y() = (m(1, 2) + m(2, 1)) / S;
        this->z() = 0.25 * S;
    }
}

Matrix<3> Quaternion::to_matrix() const {
    Matrix<3> ret;
    ret.cell(0, 0) = 1 - 2 * std::pow(this->y(), 2) - 2 * std::pow(this->z(), 2);
    ret.cell(0, 1) = 2 * this->x() * this->y() - 2 * this->w() * this->z();
    ret.cell(0, 2) = 2 * this->x() * this->z() + 2 * this->w() * this->y();

    ret.cell(1, 0) = 2 * this->x() * this->y() + 2 * this->w() * this->z();
    ret.cell(1, 1) = 1 - 2 * this->x() * this->x() - 2 * this->z() * this->z();
    ret.cell(1, 2) = 2 * this->y() * this->z() - 2 * this->w() * this->x();

    ret.cell(2, 0) = 2 * this->x() * this->z() - 2 * this->w() * this->y();
    ret.cell(2, 1) = 2 * this->y() * this->z() + 2 * this->w() * this->x();
    ret.cell(2, 2) = 1 - 2 * this->x() * this->x() - 2 * this->y() * this->y();
    return ret;
}
*/

Quaternion Quaternion::operator*(const Quaternion& q) const {
    return Quaternion({this->w() * q.w() - this->x() * q.x() - this->y() * q.y() - this->z() * q.z(),
                       this->w() * q.x() + this->x() * q.w() + this->y() * q.z() - this->z() * q.y(),
                       this->w() * q.y() - this->x() * q.z() + this->y() * q.w() + this->z() * q.x(),
                       this->w() * q.z() + this->x() * q.y() - this->y() * q.x() + this->z() * q.w()});
}
Quaternion Quaternion::operator*(const QuaternionBase::ElementType scalar) const {
    return this->scale(scalar);
}
Quaternion Quaternion::operator+(const Quaternion& q) const {
    return Quaternion({this->w() + q.w(), this->x() + q.x(), this->y() + q.y(), this->z() + q.z()});
}
Quaternion Quaternion::operator-(const Quaternion& q) const {
    return Quaternion({this->w() - q.w(), this->x() - q.x(), this->y() - q.y(), this->z() - q.z()});
}
Quaternion Quaternion::operator/(const QuaternionBase::ElementType scalar) const {
    return Quaternion({this->w() / scalar, this->x() / scalar, this->y() / scalar, this->z() / scalar});
}

}  // namespace geo
