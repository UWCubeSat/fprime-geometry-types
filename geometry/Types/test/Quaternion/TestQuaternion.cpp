#include "TestQuaternion.hpp"

#include <algorithm>
#include <array>
#include <cmath>

namespace geo {

// NOTE: default generators copy, move, copy=, and move= ctor's are not tested because these tests are effectively
// testing the compiler
// ctor's
TEST(Quaternion_tests, defualt_ctor) {
    const Quaternion q_default;

    EXPECT_FLOAT_EQ(1.0, q_default.w());
    EXPECT_FLOAT_EQ(0, q_default.x());
    EXPECT_FLOAT_EQ(0, q_default.y());
    EXPECT_FLOAT_EQ(0, q_default.z());

}
TEST(Quaternion_tests, ctor_c_arr) {
    const auto quat_dat = generate_quat();
    float imaginary[3];
    std::copy(quat_dat.second.begin(), quat_dat.second.end(), &imaginary[0]);

    const Quaternion c_arr(quat_dat.first, quat_dat.second);

    TEST_QUAT_COMPS(c_arr, quat_dat.first, quat_dat.second);
}
TEST(Quaternion_tests, ctor_init_list) {
    const auto quat_dat = generate_quat();

    const Quaternion init_list_q(quat_dat.first, {quat_dat.second[0], quat_dat.second[1], quat_dat.second[2]});

    TEST_QUAT_COMPS(init_list_q, quat_dat.first, quat_dat.second);
}
TEST(Quaternion_tests, ctor_cpp_arr) {
    const auto quat_dat = generate_quat();

    const Quaternion cpp_arr(quat_dat.first, quat_dat.second);

    TEST_QUAT_COMPS(cpp_arr, quat_dat.first, quat_dat.second);
}
TEST(Quaternion_tests, ctor_Fw_arr) {
    const auto quat_dat = generate_quat();
    Fw::Array<float, 3> Fw_imag;
    std::copy(quat_dat.second.begin(), quat_dat.second.end(), &Fw_imag[0]);

    const Quaternion Fw_arr_q(quat_dat.first, Fw_imag);

    TEST_QUAT_COMPS(Fw_arr_q, quat_dat.first, quat_dat.second);
}
TEST(Quaternion_tests, ctor_Vector3D) {
    const auto quat_dat = generate_quat();
    Vector3D imaginary(quat_dat.second);

    const Quaternion vector_list_q(quat_dat.first, quat_dat.second);

    TEST_QUAT_COMPS(vector_list_q, quat_dat.first, quat_dat.second);
}
TEST(Quaternion_tests, ctor_generic_Vector3_ctor) {
    const auto quat_dat = generate_quat();

    Vector3D v3d(quat_dat.second);
    Vector<3, float> v3float(quat_dat.second);
    /*   Vector<3, double> v3double({
           static_cast<double>(quat_dat.second[0]),
           static_cast<double>(quat_dat.second[1]),
           static_cast<double>(quat_dat.second[2]),
       });
       Vector<3, float, MyCustomArr<3>> v3weird(quat_dat.second);*/

    const Quaternion q_v3d(quat_dat.first, v3d),
        q_v3float(quat_dat.first,
                  v3float) /*,q_v3double(quat_dat.first, v3double), q_v3weird(quat_dat.first, v3weird)*/;

    EXPECT_FLOAT_EQ(q_v3d.w(), q_v3float.w());
    EXPECT_FLOAT_EQ(q_v3d.x(), q_v3float.x());
    EXPECT_FLOAT_EQ(q_v3d.y(), q_v3float.y());
    EXPECT_FLOAT_EQ(q_v3d.z(), q_v3float.z());

    /*
    EXPECT_FLOAT_EQ(q_v3d.w(), q_v3double.w());
    EXPECT_FLOAT_EQ(q_v3d.x(), q_v3double.x());
    EXPECT_FLOAT_EQ(q_v3d.y(), q_v3double.y());
    EXPECT_FLOAT_EQ(q_v3d.z(), q_v3double.z());

    EXPECT_FLOAT_EQ(q_v3d.w(), q_v3weird.w());
    EXPECT_FLOAT_EQ(q_v3d.x(), q_v3weird.x());
    EXPECT_FLOAT_EQ(q_v3d.y(), q_v3weird.y());
    EXPECT_FLOAT_EQ(q_v3d.z(), q_v3weird.z());
    */
}
TEST(Quaternion_tests, ctor_QuaternionBase) {
    const auto quat_dat = generate_quat();
    const QuaternionBase quat_base({quat_dat.first, quat_dat.second[0], quat_dat.second[1], quat_dat.second[2]});

    // vals -> base
    EXPECT_FLOAT_EQ(quat_dat.first, quat_base[0]);
    EXPECT_FLOAT_EQ(quat_dat.second[0], quat_base[1]);
    EXPECT_FLOAT_EQ(quat_dat.second[1], quat_base[2]);
    EXPECT_FLOAT_EQ(quat_dat.second[2], quat_base[3]);

    // base -> quat
    const Quaternion test_base(quat_base);

    TEST_QUAT_COMPS(test_base, quat_dat.first, quat_dat.second);
}

// comparisons
// note comparison tests have every permutation of testing for Quaternion and QuaternionBase, == and !=, and the
// true or false case
TEST(Quaternion_tests, comparison_q_q_equals_true) {
    const auto quat_dat = generate_quat();

    const Quaternion q1(quat_dat.first, quat_dat.second), q2(quat_dat.first, quat_dat.second);

    EXPECT_FLOAT_EQ(q1.w(), q2.w());
    EXPECT_FLOAT_EQ(q1.x(), q2.x());
    EXPECT_FLOAT_EQ(q1.y(), q2.y());
    EXPECT_FLOAT_EQ(q1.z(), q2.z());

    EXPECT_TRUE(q1 == q2);
}
TEST(Quaternion_tests, comparison_q_q_equals_false) {
    const auto quat_dat_1 = generate_quat(), quat_dat_2 = generate_quat();

    EXPECT_FALSE((quat_dat_1.first == quat_dat_2.first) && (quat_dat_1.second == quat_dat_2.second));

    const Quaternion q1(quat_dat_1.first, quat_dat_1.second), q2(quat_dat_2.first, quat_dat_2.second);

    EXPECT_NE(q1.w(), q2.w());
    EXPECT_NE(q1.x(), q2.x());
    EXPECT_NE(q1.y(), q2.y());
    EXPECT_NE(q1.z(), q2.z());

    EXPECT_FALSE(q1 == q2);
}
TEST(Quaternion_tests, comparison_q_qb_equals_true) {
    const auto quat_dat = generate_quat();

    const Quaternion q(quat_dat.first, quat_dat.second);
    const QuaternionBase qb({quat_dat.first, quat_dat.second[0], quat_dat.second[1], quat_dat.second[2]});

    EXPECT_FLOAT_EQ(q.w(), qb[0]);
    EXPECT_FLOAT_EQ(q.x(), qb[1]);
    EXPECT_FLOAT_EQ(q.y(), qb[2]);
    EXPECT_FLOAT_EQ(q.z(), qb[3]);

    EXPECT_TRUE(q == qb);
}
TEST(Quaternion_tests, comparison_q_qb_equals_false) {
    const auto quat_dat_1 = generate_quat(), quat_dat_2 = generate_quat();

    EXPECT_FALSE((quat_dat_1.first == quat_dat_2.first) && (quat_dat_1.second == quat_dat_2.second));

    const Quaternion q(quat_dat_1.first, quat_dat_1.second);
    const QuaternionBase qb({quat_dat_2.first, quat_dat_2.second[0], quat_dat_2.second[1], quat_dat_2.second[2]});

    EXPECT_NE(q.w(), qb[0]);
    EXPECT_NE(q.x(), qb[1]);
    EXPECT_NE(q.y(), qb[2]);
    EXPECT_NE(q.z(), qb[3]);

    EXPECT_FALSE(q == qb);
}
TEST(Quaternion_tests, comparison_q_q_nequals_true) {
    const auto quat_dat_1 = generate_quat(), quat_dat_2 = generate_quat();

    EXPECT_FALSE((quat_dat_1.first == quat_dat_2.first) && (quat_dat_1.second == quat_dat_2.second));

    const Quaternion q1(quat_dat_1.first, quat_dat_1.second), q2(quat_dat_2.first, quat_dat_2.second);

    EXPECT_NE(q1.w(), q2.w());
    EXPECT_NE(q1.x(), q2.x());
    EXPECT_NE(q1.y(), q2.y());
    EXPECT_NE(q1.z(), q2.z());

    EXPECT_TRUE(q1 != q2);
}
TEST(Quaternion_tests, comparison_q_q_nequals_false) {
    const auto quat_dat = generate_quat();

    Quaternion q1(quat_dat.first, quat_dat.second), q2(quat_dat.first, quat_dat.second);

    EXPECT_FLOAT_EQ(q1.w(), q2.w());
    EXPECT_FLOAT_EQ(q1.x(), q2.x());
    EXPECT_FLOAT_EQ(q1.y(), q2.y());
    EXPECT_FLOAT_EQ(q1.z(), q2.z());

    EXPECT_FALSE(q1 != q2);
}
TEST(Quaternion_tests, comparison_q_qb_nequals_true) {
    const auto quat_dat_1 = generate_quat(), quat_dat_2 = generate_quat();

    EXPECT_FALSE((quat_dat_1.first == quat_dat_2.first) && (quat_dat_1.second == quat_dat_2.second));

    const Quaternion q(quat_dat_1.first, quat_dat_1.second);
    const QuaternionBase qb({quat_dat_2.first, quat_dat_2.second[0], quat_dat_2.second[1], quat_dat_2.second[2]});
    EXPECT_NE(q.w(), qb[0]);
    EXPECT_NE(q.x(), qb[1]);
    EXPECT_NE(q.y(), qb[2]);
    EXPECT_NE(q.z(), qb[3]);

    EXPECT_TRUE(q != qb);
}
TEST(Quaternion_tests, comparison_q_qb_nequals_false) {
    const auto quat_dat = generate_quat();

    const Quaternion q(quat_dat.first, quat_dat.second);
    const QuaternionBase qb({quat_dat.first, quat_dat.second[0], quat_dat.second[1], quat_dat.second[2]});
    EXPECT_FLOAT_EQ(q.w(), qb[0]);
    EXPECT_FLOAT_EQ(q.x(), qb[1]);
    EXPECT_FLOAT_EQ(q.y(), qb[2]);
    EXPECT_FLOAT_EQ(q.z(), qb[3]);

    EXPECT_FALSE(q != qb);
}

// to base
TEST(Quaternion_tests, to_base_mut) {
    const auto quat_dat = generate_quat();

    Quaternion test_base(quat_dat.first, quat_dat.second);

    QuaternionBase from_base = test_base.to_base();

    EXPECT_FLOAT_EQ(quat_dat.first, from_base[0]);
    EXPECT_FLOAT_EQ(quat_dat.second[0], from_base[1]);
    EXPECT_FLOAT_EQ(quat_dat.second[1], from_base[2]);
    EXPECT_FLOAT_EQ(quat_dat.second[2], from_base[3]);

    from_base[0] = 1;
    EXPECT_FLOAT_EQ(1, from_base[0]);  // to ensure var is actually mut
}
TEST(Quaternion_tests, to_base_const) {
    const auto quat_dat = generate_quat();

    const Quaternion test_base(quat_dat.first, quat_dat.second);

    const QuaternionBase from_base = test_base.to_base();

    EXPECT_FLOAT_EQ(quat_dat.first, from_base[0]);
    EXPECT_FLOAT_EQ(quat_dat.second[0], from_base[1]);
    EXPECT_FLOAT_EQ(quat_dat.second[1], from_base[2]);
    EXPECT_FLOAT_EQ(quat_dat.second[2], from_base[3]);
}

// element access
TEST(Quaternion_tests, mut_element_access) {
    const auto quat_dat = generate_quat();

    Quaternion mut_q(quat_dat.first, quat_dat.second);

    TEST_QUAT_COMPS(mut_q, quat_dat.first, quat_dat.second);
}
TEST(Quaternion_tests, const_element_access) {
    const auto quat_dat = generate_quat();

    const Quaternion const_q(quat_dat.first, quat_dat.second);

    EXPECT_FLOAT_EQ(quat_dat.first, const_q.w());
    EXPECT_FLOAT_EQ(quat_dat.second[0], const_q.x());
    EXPECT_FLOAT_EQ(quat_dat.second[1], const_q.y());
    EXPECT_FLOAT_EQ(quat_dat.second[2], const_q.z());
}
TEST(Quaternion_tests, mut_element_assignment) {
    const auto quat_dat = generate_quat();

    Quaternion non_const_q(1, {0, 0, 0});
    EXPECT_NE(quat_dat.first, non_const_q.w());
    EXPECT_NE(quat_dat.second[0], non_const_q.x());
    EXPECT_NE(quat_dat.second[1], non_const_q.y());
    EXPECT_NE(quat_dat.second[2], non_const_q.z());

    non_const_q.w() = quat_dat.first;
    non_const_q.x() = quat_dat.second[0];
    non_const_q.y() = quat_dat.second[1];
    non_const_q.z() = quat_dat.second[2];

    TEST_QUAT_COMPS(non_const_q, quat_dat.first, quat_dat.second);
}

// scaling operations
TEST(Quaternion_tests, pos_magnitude) {
    const auto quat_dat = generate_quat();

    const Quaternion test_q(quat_dat.first, quat_dat.second);

    const auto exp_mag = std::sqrt(std::pow(quat_dat.first, 2) + std::pow(quat_dat.second[0], 2) +
                                   std::pow(quat_dat.second[1], 2) + std::pow(quat_dat.second[2], 2));

    EXPECT_GT(test_q.magnitude(), 0);
    EXPECT_FLOAT_EQ(exp_mag, test_q.magnitude());
}
TEST(Quaternion_tests, neg_magnitude) {
    const auto quat_dat = generate_quat();

    const Quaternion test_q(quat_dat.first, quat_dat.second);

    const auto exp_mag = std::sqrt(std::pow(quat_dat.first, 2) + std::pow(quat_dat.second[0], 2) +
                                   std::pow(quat_dat.second[1], 2) + std::pow(quat_dat.second[2], 2));

    EXPECT_GT(test_q.magnitude(), 0);
    EXPECT_FLOAT_EQ(exp_mag, test_q.magnitude());
}

TEST(Quaternion_tests, scaling_scales_all_elem) {
    const float scale_factor = rand_val(10);
    const auto quat_dat = generate_quat();

    const Quaternion test_q(quat_dat.first, quat_dat.second);
    const auto original_mag = test_q.magnitude();

    const auto test_q_scaled = test_q.scale(scale_factor);
    EXPECT_FLOAT_EQ(std::abs(original_mag * scale_factor), test_q_scaled.magnitude());
    EXPECT_FLOAT_EQ(quat_dat.first * scale_factor, test_q_scaled.w());
    EXPECT_FLOAT_EQ(quat_dat.second[0] * scale_factor, test_q_scaled.x());
    EXPECT_FLOAT_EQ(quat_dat.second[1] * scale_factor, test_q_scaled.y());
    EXPECT_FLOAT_EQ(quat_dat.second[2] * scale_factor, test_q_scaled.z());
}

TEST(Quaternion_tests, norm_makes_mag_1_pos) {
    const float scale_factor = std::abs(rand_val(10));  // note the positive scale factor
    const auto quat_dat = generate_quat();
    const Quaternion norm_1_q(quat_dat.first, quat_dat.second);
    EXPECT_FLOAT_EQ(1.0, norm_1_q.magnitude());

    Quaternion scaled_pos_q = norm_1_q.scale(scale_factor);
    EXPECT_FLOAT_EQ(std::abs(scale_factor), scaled_pos_q.magnitude());

    scaled_pos_q.normalize();
    EXPECT_FLOAT_EQ(1.0, scaled_pos_q.magnitude());

    // note that the values are the same in magnitude and sign
    EXPECT_FLOAT_EQ(norm_1_q.w(), scaled_pos_q.w());
    EXPECT_FLOAT_EQ(norm_1_q.x(), scaled_pos_q.x());
    EXPECT_FLOAT_EQ(norm_1_q.y(), scaled_pos_q.y());
    EXPECT_FLOAT_EQ(norm_1_q.z(), scaled_pos_q.z());
}
TEST(Quaternion_tests, norm_makes_mag_1_neg) {
    const float scale_factor = -1.0 * std::abs(rand_val(10));  // note the negative scale factor
    const auto quat_dat = generate_quat();

    const Quaternion norm_1_q(quat_dat.first, quat_dat.second);
    EXPECT_FLOAT_EQ(1.0, norm_1_q.magnitude());

    Quaternion scaled_neg_q = norm_1_q.scale(scale_factor);
    EXPECT_FLOAT_EQ(std::abs(scale_factor), scaled_neg_q.magnitude());

    scaled_neg_q.normalize();
    EXPECT_FLOAT_EQ(1.0, scaled_neg_q.magnitude());

    // note that the values are the same in sign but opposite in magnitude due to scaling
    EXPECT_FLOAT_EQ(-1.0 * norm_1_q.w(), scaled_neg_q.w());
    EXPECT_FLOAT_EQ(-1.0 * norm_1_q.x(), scaled_neg_q.x());
    EXPECT_FLOAT_EQ(-1.0 * norm_1_q.y(), scaled_neg_q.y());
    EXPECT_FLOAT_EQ(-1.0 * norm_1_q.z(), scaled_neg_q.z());
}
TEST(Quaternion_tests, norm_doesnt_change_mag_of_1) {
    const auto quat_dat = generate_quat();

    Quaternion norm_q(quat_dat.first, quat_dat.second);
    EXPECT_FLOAT_EQ(1.0, norm_q.magnitude());

    norm_q.normalize();
    EXPECT_FLOAT_EQ(1.0, norm_q.magnitude());

    TEST_QUAT_COMPS(norm_q, quat_dat.first, quat_dat.second);
}

// geometry operations
TEST(Quaternion_tests, conjugate) {
    // equation from this random picture:
    // https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fimage3.slideserve.com%2F5450169%2Fquaternions1-l.jpg&f=1&nofb=1&ipt=22fd49084450ffd1cb9a809cbcd29e87ccb64df77eaefa059506542465461c28

    const auto quat_dat = generate_quat();

    const Quaternion test_q(quat_dat.first, quat_dat.second);

    const Quaternion expected_conj(quat_dat.first, {-quat_dat.second[0], -quat_dat.second[1], -quat_dat.second[2]}),
        test_conj = test_q.conjugate();

    EXPECT_FLOAT_EQ(expected_conj.w(), test_conj.w());
    EXPECT_FLOAT_EQ(expected_conj.x(), test_conj.x());
    EXPECT_FLOAT_EQ(expected_conj.y(), test_conj.y());
    EXPECT_FLOAT_EQ(expected_conj.z(), test_conj.z());
}

TEST(Quaternion_tests, from_axis_angle_Vector3D) {
    // TODO
    EXPECT_EQ(1, 1);
}
TEST(Quaternion_tests, from_matrix) {
    // TODO
    EXPECT_EQ(1, 1);
}

TEST(Quaternion_tests, to_axis_angle_Vector3D) {
    // TODO
    EXPECT_EQ(1, 1);
}
// TEST(to_axis_angle_generic_Vector3) {}
TEST(Quaternion_tests, to_matrix) {
    // TODO
    EXPECT_EQ(1, 1);
}

TEST(Quaternion_tests, to_euler_Vector3D) {
    // TODO
    EXPECT_EQ(1, 1);
}
// TEST(Quaternion_tests, to_euler_generic_Vector3){}
TEST(Quaternion_tests, angular_velocity_Vector3D) {
    // TODO
    EXPECT_EQ(1, 1);
}
// TEST(Quaternion_tests, angular_velocity_generic_Vector3){}

TEST(Quaternion_tests, rotate_vector_Vector3D) {
    // TODO
    EXPECT_EQ(1, 1);
}
// TEST(Quaternion_tests, rotate_vector_generic_Vector3){}
TEST(Quaternion_tests, rotate_vector_generic_Vector2) {
    // TODO
    EXPECT_EQ(1, 1);
}

// math operations
TEST(Quaternion_tests, quat_multiplication) {
    const auto quat_dat_1 = generate_quat(), quat_dat_2 = generate_quat();

    const Quaternion q1(quat_dat_1.first, quat_dat_1.second), q2(quat_dat_2.first, quat_dat_2.second);

    const Quaternion expected_q_product(
        (q1.w() * q2.w()) - (q1.x() * q2.x()) - (q1.y() * q2.y()) - (q1.z() * q2.z()),
        {(q1.w() * q2.x()) + (q1.x() * q2.w()) + (q1.y() * q2.z()) - (q1.z() * q2.y()),
         (q1.w() * q2.y()) + (q1.y() * q2.w()) + (q1.z() * q2.x()) - (q1.x() * q2.z()),
         (q1.w() * q2.z()) + (q1.z() * q2.w()) + (q1.x() * q2.y()) - (q1.y() * q2.x())}),
        test_q_product = q1 * q2;
    EXPECT_FLOAT_EQ(expected_q_product.w(), test_q_product.w());
    EXPECT_FLOAT_EQ(expected_q_product.x(), test_q_product.x());
    EXPECT_FLOAT_EQ(expected_q_product.y(), test_q_product.y());
    EXPECT_FLOAT_EQ(expected_q_product.z(), test_q_product.z());
}
TEST(Quaternion_tests, scalar_multiplication) {
    const float scale_factor = rand_val(10);
    const auto quat_dat_1 = generate_quat(), quat_dat_2 = generate_quat();

    const Quaternion q1(quat_dat_1.first, quat_dat_1.second), q2(quat_dat_2.first, quat_dat_2.second);

    const Quaternion scalar_product = q1 * scale_factor;
    EXPECT_FLOAT_EQ(std::abs(q1.magnitude() * scale_factor), scalar_product.magnitude());
    EXPECT_FLOAT_EQ(quat_dat_1.first * scale_factor, scalar_product.w());
    EXPECT_FLOAT_EQ(quat_dat_1.second[0] * scale_factor, scalar_product.x());
    EXPECT_FLOAT_EQ(quat_dat_1.second[1] * scale_factor, scalar_product.y());
    EXPECT_FLOAT_EQ(quat_dat_1.second[2] * scale_factor, scalar_product.z());
}
TEST(Quaternion_tests, scalar_division) {
    const float scale_factor = rand_val(10);
    const auto quat_dat = generate_quat();
    const Quaternion original_q(quat_dat.first, quat_dat.second);

    const Quaternion quotient = original_q / scale_factor;
    EXPECT_FLOAT_EQ(std::abs(original_q.magnitude() / scale_factor), quotient.magnitude());
    EXPECT_FLOAT_EQ(quat_dat.first / scale_factor, quotient.w());
    EXPECT_FLOAT_EQ(quat_dat.second[0] / scale_factor, quotient.x());
    EXPECT_FLOAT_EQ(quat_dat.second[1] / scale_factor, quotient.y());
    EXPECT_FLOAT_EQ(quat_dat.second[2] / scale_factor, quotient.z());
}
TEST(Quaternion_tests, quat_addition) {
    const auto quat_dat_1 = generate_quat(), quat_dat_2 = generate_quat();

    const Quaternion q1(quat_dat_1.first, quat_dat_1.second), q2(quat_dat_2.first, quat_dat_2.second);

    // addition
    const Quaternion sum = q1 + q2;

    EXPECT_FLOAT_EQ(quat_dat_1.first + quat_dat_2.first, sum.w());
    EXPECT_FLOAT_EQ(quat_dat_1.second[0] + quat_dat_2.second[0], sum.x());
    EXPECT_FLOAT_EQ(quat_dat_1.second[1] + quat_dat_2.second[1], sum.y());
    EXPECT_FLOAT_EQ(quat_dat_1.second[2] + quat_dat_2.second[2], sum.z());
}
TEST(Quaternion_tests, quat_subtraction) {
    const auto quat_dat_1 = generate_quat(), quat_dat_2 = generate_quat();

    const Quaternion q1(quat_dat_1.first, quat_dat_1.second), q2(quat_dat_2.first, quat_dat_2.second);

    const Quaternion difference = q1 - q2;
    EXPECT_FLOAT_EQ(quat_dat_1.first - quat_dat_2.first, difference.w());
    EXPECT_FLOAT_EQ(quat_dat_1.second[0] - quat_dat_2.second[0], difference.x());
    EXPECT_FLOAT_EQ(quat_dat_1.second[1] - quat_dat_2.second[1], difference.y());
    EXPECT_FLOAT_EQ(quat_dat_1.second[2] - quat_dat_2.second[2], difference.z());
}
}  // namespace geo
