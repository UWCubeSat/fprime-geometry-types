#include "TestVector.hpp"

#include <cmath>

#include "Fw/DataStructures/Array.hpp"

namespace geo {

// ctor's
TEST(Vector_tests, ctor_c_arr) {
    const float c_dat[3] = {rand_val(200), rand_val(200), rand_val(200)};
    const F64 c_dat_F64[3] = {rand_val(200), rand_val(200), rand_val(200)};
    const geo::Vector<3> test_vec_3(c_dat);
    const geo::Vector<3, F64> test_vec_3F64(c_dat_F64);
    const geo::Vector3D test_vec_3D(c_dat);

    for (FwSizeType i = 0; i < 3; i++) {
        EXPECT_FLOAT_EQ(c_dat[i], test_vec_3[i]) << "Vector<3> index: " << static_cast<int>(i);
        EXPECT_FLOAT_EQ(c_dat_F64[i], test_vec_3F64[i]) << "Vector<3, F64> index: " << static_cast<int>(i);
        EXPECT_FLOAT_EQ(c_dat[i], test_vec_3D[i]) << "Vector3D index: " << static_cast<int>(i);
    }
}  // namespace geo

// std::array macro and test
TEST(Vector_tests, ctor_cpp_arr) {
    const std::array<float, 3> cpp_dat = {rand_val(200), rand_val(200), rand_val(200)};
    const std::array<F64, 3> cpp_dat_F64 = {rand_val(200), rand_val(200), rand_val(200)};

    const geo::Vector<3> test_vec_3(cpp_dat);
    const geo::Vector<3, F64> test_vec_3F64(cpp_dat_F64);
    const geo::Vector3D test_vec_3D(cpp_dat);

    for (FwSizeType i = 0; i < 3; i++) {
        EXPECT_FLOAT_EQ(cpp_dat[i], test_vec_3[i]) << "Vector<3> index: " << static_cast<int>(i);
        EXPECT_FLOAT_EQ(cpp_dat_F64[i], test_vec_3F64[i]) << "Vector<3, F64> index: " << static_cast<int>(i);
        EXPECT_FLOAT_EQ(cpp_dat[i], test_vec_3D[i]) << "Vector3D index: " << static_cast<int>(i);
    }
}

// Fw::Array macro and test
TEST(Vector_tests, ctor_Fw_arr) {
    Fw::Array<float, 3> Fw_dat = {rand_val(200), rand_val(200), rand_val(200)};
    Fw::Array<F64, 3> Fw_dat_F64 = {rand_val(200), rand_val(200), rand_val(200)};

    const geo::Vector<3> test_vec_3(Fw_dat);
    const geo::Vector<3, F64> test_vec_3F64(Fw_dat_F64);
    const geo::Vector3D test_vec_3D(Fw_dat);

    for (FwSizeType i = 0; i < 3; i++) {
        EXPECT_FLOAT_EQ(Fw_dat[i], test_vec_3[i]) << "Vector<3> vector index: " << static_cast<int>(i);
        EXPECT_FLOAT_EQ(Fw_dat_F64[i], test_vec_3F64[i]) << "Vector<3, F64> index: " << static_cast<int>(i);
        EXPECT_FLOAT_EQ(Fw_dat[i], test_vec_3D[i]) << "Vector3D index: " << static_cast<int>(i);
    }
}

// Vector3DBase Test
TEST(Vector_tests, ctor_Vector3D_base) {
    const Vector3DBase base(
        {static_cast<float>(rand_val(200)), static_cast<float>(rand_val(200)), static_cast<float>(rand_val(200))});

    const geo::Vector3D test_vec(base);

    for (FwSizeType i = 0; i < test_vec.n(); i++) {
        EXPECT_FLOAT_EQ(base[i], test_vec[i]) << "Vector3D index: " << static_cast<int>(i);
    }
}

// characteristics
TEST(Vector_tests, n_value) {
    const geo::Vector<3> test_vec_3({0, 0, 0});
    const geo::Vector<3, F64> test_vec_3F64({0, 0, 0});
    const geo::Vector3D test_vec_3D({0, 0, 0});

    EXPECT_FLOAT_EQ(3, test_vec_3.n()) << "Vector<3>";
    EXPECT_FLOAT_EQ(3, test_vec_3F64.n()) << "Vector<3, F64>";
    EXPECT_FLOAT_EQ(3, test_vec_3D.n()) << "Vector3D";
}

// comparisons
TEST(Vector_tests, comparison_equals_true) {
    const std::array<float, 3> rand_dat = {rand_val(200), rand_val(200), rand_val(200)};
    const std::array<F64, 3> rand_dat_F64 = {rand_val(200), rand_val(200), rand_val(200)};

    const geo::Vector<3> test_vec_3(rand_dat), comp_vec_3(rand_dat);
    const geo::Vector<3, F64> test_vec_3F64(rand_dat_F64), comp_vec_3F64(rand_dat_F64);
    const geo::Vector3D test_vec_3D(rand_dat), comp_vec_3D(rand_dat);

    for (FwSizeType i = 0; i < 3; i++) {
        EXPECT_FLOAT_EQ(rand_dat[i], test_vec_3[i]) << "test Vector<3> index: " << static_cast<int>(i);
        EXPECT_FLOAT_EQ(rand_dat_F64[i], test_vec_3F64[i]) << "Vector<3, F64> index: " << static_cast<int>(i);
        EXPECT_FLOAT_EQ(rand_dat[i], test_vec_3D[i]) << "test Vector3D index: " << static_cast<int>(i);

        EXPECT_FLOAT_EQ(rand_dat[i], comp_vec_3[i]) << "comparison Vector<3> index: " << static_cast<int>(i);
        EXPECT_FLOAT_EQ(rand_dat_F64[i], comp_vec_3F64[i]) << "Vector<3, F64> index: " << static_cast<int>(i);
        EXPECT_FLOAT_EQ(rand_dat[i], comp_vec_3D[i]) << "comparison Vector3D index: " << static_cast<int>(i);
    }
    EXPECT_TRUE(test_vec_3 == comp_vec_3);
    EXPECT_TRUE(test_vec_3F64 == comp_vec_3F64);
    EXPECT_TRUE(test_vec_3D == comp_vec_3D);

    EXPECT_FALSE(test_vec_3 != comp_vec_3);
    EXPECT_FALSE(test_vec_3F64 != comp_vec_3F64);
    EXPECT_FALSE(test_vec_3D != comp_vec_3D);
}
TEST(Vector_tests, comparison_equals_false) {
    const std::array<float, 3> rand_dat = {rand_val(200), rand_val(200), rand_val(200)};
    const std::array<F64, 3> rand_dat_F64 = {rand_val(200), rand_val(200), rand_val(200)};

    const geo::Vector<3> test_vec_3(rand_dat);
    geo::Vector<3> comp_vec_3(rand_dat);
    const geo::Vector<3, F64> test_vec_3_F64(rand_dat_F64);
    geo::Vector<3, F64> comp_vec_3_F64(rand_dat_F64);
    const geo::Vector3D test_vec_3D(rand_dat);
    geo::Vector3D comp_vec_3D(rand_dat);

    for (FwSizeType i = 0; i < 3; i++) {
        comp_vec_3[i]++;
        comp_vec_3D[i]++;

        for (FwSizeType j = 0; j < 3; j++) {
            // check to make sure test vectors are equal to original data and new vectors are not equal to new data
            EXPECT_FLOAT_EQ(rand_dat[j], test_vec_3[j]) << "test Vector<3> index: " << static_cast<int>(j);
            EXPECT_FLOAT_EQ(rand_dat_F64[j], test_vec_3_F64[j]) << "Vector<3, F64> index: " << static_cast<int>(i);
            EXPECT_FLOAT_EQ(rand_dat[j], test_vec_3D[j]) << "test Vector3D index: " << static_cast<int>(j);

            EXPECT_NE(rand_dat[i], comp_vec_3[i]) << "comp Vector<3> index: " << static_cast<int>(j);
            EXPECT_NE(rand_dat_F64[i], comp_vec_3_F64[i]) << "Vector<3, F64> index: " << static_cast<int>(i);
            EXPECT_NE(rand_dat[i], comp_vec_3D[i]) << "comp Vector3D index: " << static_cast<int>(j);
        }
        EXPECT_FALSE(test_vec_3 == comp_vec_3);
        EXPECT_FALSE(test_vec_3_F64 == comp_vec_3_F64);
        EXPECT_FALSE(test_vec_3D == comp_vec_3D);

        EXPECT_TRUE(test_vec_3 != comp_vec_3);
        EXPECT_TRUE(test_vec_3_F64 != comp_vec_3_F64);
        EXPECT_TRUE(test_vec_3D != comp_vec_3D);
    }
}

// indexed element access
TEST(Vector_tests, mut_indexed_access) {
    const std::array<float, 3> rand_dat = {rand_val(200), rand_val(200), rand_val(200)};
    const std::array<F64, 3> rand_dat_F64 = {rand_val(200), rand_val(200), rand_val(200)};

    geo::Vector<3> test_vec_3(rand_dat);
    geo::Vector<3, F64> test_vec_3_F64(rand_dat_F64);
    geo::Vector3D test_vec_3D(rand_dat);

    for (FwSizeType i = 0; i < 3; i++) {
        EXPECT_FLOAT_EQ(rand_dat[i], test_vec_3[i]) << "Vector<3> index: " << static_cast<int>(i);
        EXPECT_NE(rand_dat_F64[i], rand_dat_F64[i]) << "Vector<3, F64> index: " << static_cast<int>(i);
        EXPECT_FLOAT_EQ(rand_dat[i], test_vec_3D[i]) << "Vector3D index: " << static_cast<int>(i);
    }
}
TEST(Vector_tests, const_indexed_access) {
    const std::array<float, 3> rand_dat = {rand_val(200), rand_val(200), rand_val(200)};
    const std::array<F64, 3> rand_dat_F64 = {rand_val(200), rand_val(200), rand_val(200)};

    const geo::Vector<3> test_vec_3(rand_dat);
    const geo::Vector<3, F64> test_vec_3_F64(rand_dat_F64);
    const geo::Vector3D test_vec_3D(rand_dat);

    for (FwSizeType i = 0; i < 3; i++) {
        EXPECT_FLOAT_EQ(rand_dat[i], test_vec_3[i]) << "Vector<3> index: " << static_cast<int>(i);
        EXPECT_FLOAT_EQ(rand_dat_F64[i], test_vec_3_F64[i]) << "Vector<3, F64> index: " << static_cast<int>(i);
        EXPECT_FLOAT_EQ(rand_dat[i], test_vec_3D[i]) << "Vector3D index: " << static_cast<int>(i);
    }
}
TEST(Vector_tests, indexed_assignment) {
    const std::array<float, 3> rand_dat = {rand_val(200), rand_val(200), rand_val(200)};
    const std::array<F64, 3> rand_dat_F64 = {rand_val(200), rand_val(200), rand_val(200)};

    geo::Vector<3> test_vec_3(rand_dat);
    geo::Vector<3, F64> test_vec_3_F64(rand_dat_F64);
    geo::Vector3D test_vec_3D(rand_dat);

    for (FwSizeType i = 0; i < 3; i++) {
        test_vec_3[i] += i + 1;
        test_vec_3_F64[i] += i + 1;
        test_vec_3D[i] += i + 1;
    }
    for (FwSizeType i = 0; i < 3; i++) {
        EXPECT_FLOAT_EQ(rand_dat[i] + i + 1, test_vec_3[i]) << "Vector<3> index: " << static_cast<int>(i);
        EXPECT_FLOAT_EQ(rand_dat_F64[i] + i + 1, test_vec_3_F64[i]) << "Vector<3, F64> index: " << static_cast<int>(i);
        EXPECT_FLOAT_EQ(rand_dat[i] + i + 1, test_vec_3D[i]) << "Vector3D index: " << static_cast<int>(i);
    }
}

// named element access
TEST(Vector_tests, mut_named_access) {
    const std::array<float, 3> rand_dat = {rand_val(200), rand_val(200), rand_val(200)};
    const std::array<F64, 3> rand_dat_F64 = {rand_val(200), rand_val(200), rand_val(200)};

    geo::Vector<3> test_vec_3(rand_dat);
    geo::Vector<3, F64> test_vec_3_F64(rand_dat_F64);
    geo::Vector3D test_vec_3D(rand_dat);

    EXPECT_FLOAT_EQ(rand_dat[0], test_vec_3.x());
    EXPECT_FLOAT_EQ(rand_dat_F64[0], test_vec_3_F64.x());
    EXPECT_FLOAT_EQ(rand_dat[0], test_vec_3D.x());

    EXPECT_FLOAT_EQ(rand_dat[1], test_vec_3.y());
    EXPECT_FLOAT_EQ(rand_dat_F64[1], test_vec_3_F64.y());
    EXPECT_FLOAT_EQ(rand_dat[1], test_vec_3D.y());

    EXPECT_FLOAT_EQ(rand_dat[2], test_vec_3.z());
    EXPECT_FLOAT_EQ(rand_dat_F64[2], test_vec_3_F64.z());
    EXPECT_FLOAT_EQ(rand_dat[2], test_vec_3D.z());
}
TEST(Vector_tests, const_named_access) {
    const std::array<float, 3> rand_dat = {rand_val(200), rand_val(200), rand_val(200)};
    const std::array<F64, 3> rand_dat_F64 = {rand_val(200), rand_val(200), rand_val(200)};

    const geo::Vector<3> test_vec_3(rand_dat);
    const geo::Vector<3, F64> test_vec_3_F64(rand_dat_F64);
    const geo::Vector3D test_vec_3D(rand_dat);

    EXPECT_FLOAT_EQ(rand_dat[0], test_vec_3.x());
    EXPECT_FLOAT_EQ(rand_dat_F64[0], test_vec_3_F64.x());
    EXPECT_FLOAT_EQ(rand_dat[0], test_vec_3D.x());

    EXPECT_FLOAT_EQ(rand_dat[1], test_vec_3.y());
    EXPECT_FLOAT_EQ(rand_dat_F64[1], test_vec_3_F64.y());
    EXPECT_FLOAT_EQ(rand_dat[1], test_vec_3D.y());

    EXPECT_FLOAT_EQ(rand_dat[2], test_vec_3.z());
    EXPECT_FLOAT_EQ(rand_dat_F64[2], test_vec_3_F64.z());
    EXPECT_FLOAT_EQ(rand_dat[2], test_vec_3D.z());
}
TEST(Vector_tests, named_assignment) {
    const std::array<float, 3> rand_dat = {rand_val(200), rand_val(200), rand_val(200)},
                               diffs = {rand_val(200), rand_val(200), rand_val(200)};
    const std::array<F64, 3> rand_dat_F64 = {rand_val(200), rand_val(200), rand_val(200)},
                             diffs_F64 = {rand_val(200), rand_val(200), rand_val(200)};

    geo::Vector<3> test_vec_3(rand_dat);
    geo::Vector<3, F64> test_vec_3_F64(rand_dat_F64);
    geo::Vector3D test_vec_3D(rand_dat);

    test_vec_3.x() += diffs[0];
    test_vec_3_F64.x() += diffs[0];
    test_vec_3D.x() += diffs[0];

    test_vec_3.y() += diffs[1];
    test_vec_3_F64.y() += diffs[1];
    test_vec_3D.y() += diffs[1];

    test_vec_3.z() += diffs[2];
    test_vec_3_F64.z() += diffs[2];
    test_vec_3D.z() += diffs[2];

    EXPECT_FLOAT_EQ(rand_dat[0] + diffs[0], test_vec_3.x());  // 3
    EXPECT_FLOAT_EQ(test_vec_3[0], test_vec_3.x());
    EXPECT_FLOAT_EQ(rand_dat_F64[0] + diffs_F64[0], test_vec_3_F64.x());  // 3, F64
    EXPECT_FLOAT_EQ(test_vec_3D[0], test_vec_3_F64.x());
    EXPECT_FLOAT_EQ(rand_dat[0] + diffs[0], test_vec_3D.x());  // 3D
    EXPECT_FLOAT_EQ(test_vec_3D[0], test_vec_3D.x());

    EXPECT_FLOAT_EQ(rand_dat[1] + diffs[1], test_vec_3.y());
    EXPECT_FLOAT_EQ(test_vec_3[1], test_vec_3.y());
    EXPECT_FLOAT_EQ(rand_dat_F64[1] + diffs_F64[1], test_vec_3_F64.y());  // 3, F64
    EXPECT_FLOAT_EQ(test_vec_3D[1], test_vec_3_F64.y());
    EXPECT_FLOAT_EQ(rand_dat[1] + diffs[1], test_vec_3D.y());
    EXPECT_FLOAT_EQ(test_vec_3D[1], test_vec_3D.y());

    EXPECT_FLOAT_EQ(rand_dat[2] + diffs[2], test_vec_3.z());
    EXPECT_FLOAT_EQ(test_vec_3[2], test_vec_3.z());
    EXPECT_FLOAT_EQ(rand_dat_F64[2] + diffs_F64[2], test_vec_3_F64.z());  // 3, F64
    EXPECT_FLOAT_EQ(test_vec_3D[2], test_vec_3_F64.z());
    EXPECT_FLOAT_EQ(rand_dat[2] + diffs[2], test_vec_3D.z());
    EXPECT_FLOAT_EQ(test_vec_3D[2], test_vec_3D.z());
}

// geometry operations
TEST(Vector_tests, pos_magnitude) {
    const std::array<float, 3> rand_dat = {rand_val(200), rand_val(200), rand_val(200)};
    const std::array<F64, 3> rand_dat_F64 = {rand_val(200), rand_val(200), rand_val(200)};

    const geo::Vector<3> test_vec_3(rand_dat);
    const geo::Vector<3, F64> test_vec_3_F64(rand_dat_F64);
    const geo::Vector3D test_vec_3D(rand_dat);

    float exp_mag = 0;
    for (FwSizeType i = 0; i < 3; i++) {
        exp_mag += std::pow(rand_dat[i], 2);
    }
    exp_mag = std::sqrt(exp_mag);

    EXPECT_FLOAT_EQ(exp_mag, test_vec_3.magnitude());
    EXPECT_FLOAT_EQ(exp_mag, test_vec_3_F64.magnitude());
    EXPECT_FLOAT_EQ(exp_mag, test_vec_3D.magnitude());
}
TEST(Vector_tests, neg_magnitude) {
    const std::array<float, 3> rand_dat = {rand_val(200), rand_val(200), rand_val(200)};
    const std::array<F64, 3> rand_dat_F64 = {rand_val(200), rand_val(200), rand_val(200)};

    geo::Vector<3> test_vec_3(rand_dat);
    geo::Vector<3, F64> test_vec_3_F64(rand_dat_F64);
    geo::Vector3D test_vec_3D(rand_dat);

    for (FwSizeType i = 0; i < 3; i++) {
        test_vec_3[i] = -1.f * std::abs(test_vec_3[i]);
        test_vec_3_F64[i] = -1.f * std::abs(test_vec_3_F64[i]);
        test_vec_3D[i] = -1.f * std::abs(test_vec_3D[i]);
    }

    float exp_mag = 0;
    for (FwSizeType i = 0; i < 3; i++) {
        exp_mag += std::pow(rand_dat[i], 2);
    }
    exp_mag = std::sqrt(exp_mag);

    EXPECT_FLOAT_EQ(exp_mag, test_vec_3.magnitude());
    EXPECT_FLOAT_EQ(exp_mag, test_vec_3_F64.magnitude());
    EXPECT_FLOAT_EQ(exp_mag, test_vec_3D.magnitude());
}

TEST(Vector_tests, scaling_scales_all_elem) {
    const std::array<float, 3> rand_dat = {rand_val(200), rand_val(200), rand_val(200)};
    const std::array<F64, 3> rand_dat_F64 = {rand_val(200), rand_val(200), rand_val(200)};

    geo::Vector<3> test_vec_3(rand_dat);
    geo::Vector<3, F64> test_vec_3_F64(rand_dat_F64);
    geo::Vector3D test_vec_3D(rand_dat);

    const auto scale_factor = rand_val(10);

    test_vec_3 = test_vec_3.scale(scale_factor);
    test_vec_3_F64 = test_vec_3_F64.scale(scale_factor);
    test_vec_3D = test_vec_3D.scale(scale_factor);

    for (FwSizeType i = 0; i < 3; i++) {
        EXPECT_FLOAT_EQ(rand_dat[i] * scale_factor, test_vec_3[i]) << "Vector<3> index: " << static_cast<int>(i);
        EXPECT_FLOAT_EQ(rand_dat_F64[i], test_vec_3_F64[i]) << "Vector<3, F64> index: " << static_cast<int>(i);
        EXPECT_FLOAT_EQ(rand_dat[i] * scale_factor, test_vec_3D[i]) << "Vector3D index: " << static_cast<int>(i);
    }
}

TEST(Vector_tests, norm_makes_mag_1_pos) {
    const std::array<float, 3> rand_dat = {rand_val(200), rand_val(200), rand_val(200)};
    const std::array<F64, 3> rand_dat_F64 = {rand_val(200), rand_val(200), rand_val(200)};

    geo::Vector<3> test_vec_3(rand_dat);
    geo::Vector<3, F64> test_vec_3_F64(rand_dat_F64);
    geo::Vector3D test_vec_3D(rand_dat);

    for (FwSizeType i = 0; i < 3; i++) {
        test_vec_3[i] = std::abs(test_vec_3[i]);
        test_vec_3_F64[i] = std::abs(test_vec_3_F64[i]);
        test_vec_3D[i] = std::abs(test_vec_3D[i]);
    }

    test_vec_3.normalize();
    test_vec_3_F64.normalize();
    test_vec_3D.normalize();

    EXPECT_FLOAT_EQ(1.f, test_vec_3.magnitude());
    EXPECT_FLOAT_EQ(1.f, test_vec_3_F64.magnitude());
    EXPECT_FLOAT_EQ(1.f, test_vec_3D.magnitude());
}
TEST(Vector_tests, norm_makes_mag_1_neg) {
    const std::array<float, 3> rand_dat = {rand_val(200), rand_val(200), rand_val(200)};
    const std::array<F64, 3> rand_dat_F64 = {rand_val(200), rand_val(200), rand_val(200)};

    geo::Vector<3> test_vec_3(rand_dat);
    geo::Vector<3, F64> test_vec_3_F64(rand_dat_F64);
    geo::Vector3D test_vec_3D(rand_dat);

    for (FwSizeType i = 0; i < 3; i++) {
        test_vec_3[i] = -1.f * std::abs(test_vec_3[i]);
        test_vec_3_F64[i] = -1.f * std::abs(test_vec_3_F64[i]);
        test_vec_3D[i] = -1.f * std::abs(test_vec_3D[i]);
    }

    test_vec_3.normalize();
    test_vec_3_F64.normalize();
    test_vec_3D.normalize();

    EXPECT_FLOAT_EQ(1.f, test_vec_3.magnitude());
    EXPECT_FLOAT_EQ(1.f, test_vec_3_F64.magnitude());
    EXPECT_FLOAT_EQ(1.f, test_vec_3D.magnitude());
}
TEST(Vector_tests, norm_doesnt_change_mag_of_1) {
    const std::array<float, 3> rand_dat = {rand_val(200), rand_val(200), rand_val(200)};
    const std::array<F64, 3> rand_dat_F64 = {rand_val(200), rand_val(200), rand_val(200)};

    geo::Vector<3> test_vec_3(rand_dat);
    geo::Vector<3, F64> test_vec_3_F64(rand_dat_F64);
    geo::Vector3D test_vec_3D(rand_dat);

    EXPECT_FLOAT_EQ(test_vec_3.magnitude(), test_vec_3D.magnitude());
    EXPECT_FLOAT_EQ(static_cast<F64>(test_vec_3.magnitude()), test_vec_3_F64.magnitude());
    const auto mag = test_vec_3.magnitude();

    test_vec_3.normalize();
    test_vec_3_F64.normalize();
    test_vec_3D.normalize();
    EXPECT_FLOAT_EQ(1.f, test_vec_3.magnitude());
    EXPECT_FLOAT_EQ(1.f, test_vec_3_F64.magnitude());
    EXPECT_FLOAT_EQ(1.f, test_vec_3D.magnitude());

    test_vec_3.normalize();
    test_vec_3_F64.normalize();
    test_vec_3D.normalize();
    EXPECT_FLOAT_EQ(1.f, test_vec_3.magnitude());
    EXPECT_FLOAT_EQ(1.f, test_vec_3_F64.magnitude());
    EXPECT_FLOAT_EQ(1.f, test_vec_3D.magnitude());

    for (FwSizeType i = 0; i < 3; i++) {
        EXPECT_FLOAT_EQ(rand_dat[i] / mag, test_vec_3[i]) << "Vector<3> index: " << static_cast<int>(i);
        EXPECT_FLOAT_EQ(rand_dat_F64[i] / mag, test_vec_3_F64[i]) << "Vector<3, F64> index: " << static_cast<int>(i);
        EXPECT_FLOAT_EQ(rand_dat[i] / mag, test_vec_3D[i]) << "Vector3D index: " << static_cast<int>(i);
    }
}
TEST(Vector_tests, dot) {
    const std::array<float, 3> rand_dat = {rand_val(200), rand_val(200), rand_val(200)};
    const std::array<F64, 3> rand_dat_F64 = {rand_val(200), rand_val(200), rand_val(200)};

    const geo::Vector<3> test_vec_3(rand_dat);
    const geo::Vector<3, F64> test_vec_3_F64(rand_dat_F64);
    const geo::Vector3D test_vec_3D(rand_dat);

    auto new_rand_dat(rand_dat);
    auto new_test_vec(test_vec_3);

    for (FwSizeType i = 0; i < 3; i++) {
        new_rand_dat[i] = rand_val(200);
        new_test_vec[i] = new_rand_dat[i];
    }

    float exp_dot = 0.0;
    for (FwSizeType i = 0; i < 3; i++) {
        exp_dot += rand_dat[i] * new_rand_dat[i];
    }
    EXPECT_FLOAT_EQ(exp_dot, test_vec_3.dot(new_test_vec)) << "vector dimension: " << 3;
    EXPECT_FLOAT_EQ(exp_dot, new_test_vec.dot(test_vec_3)) << "vector dimension: " << 3;
}

TEST(Vector_tests, cross) {}

// math operations
TEST(Vector_tests, addition) {
    const std::array<float, 3> rand_dat_1 = {rand_val(200), rand_val(200), rand_val(200)},
                               rand_dat_2 = {rand_val(200), rand_val(200), rand_val(200)};
    const std::array<F64, 3> rand_dat_1_F64 = {rand_val(200), rand_val(200), rand_val(200)},
                             rand_dat_2_F64 = {rand_val(200), rand_val(200), rand_val(200)};

    const geo::Vector<3> test_vec_3_1(rand_dat_1), test_vec_3_2(rand_dat_2);
    const geo::Vector<3, F64> test_vec_3_F64_1(rand_dat_1_F64), test_vec_3_F64_2(rand_dat_2_F64);
    const geo::Vector<3> test_vec_3D_1(rand_dat_1), test_vec_3D_2(rand_dat_2);

    // testing A + B = B + A
    const auto vec_sum_3_1 = test_vec_3_1 + test_vec_3_2;
    const auto vec_sum_3_2 = test_vec_3_2 + test_vec_3_1;

    const auto vec_sum_3_F64_1 = test_vec_3_F64_1 + test_vec_3_F64_2;
    const auto vec_sum_3_F64_2 = test_vec_3_F64_2 + test_vec_3_F64_1;

    const auto vec_sum_3D_1 = test_vec_3D_1 + test_vec_3D_2;
    const auto vec_sum_3D_2 = test_vec_3D_2 + test_vec_3D_1;

    for (FwSizeType i = 0; i < 3; i++) {
        EXPECT_FLOAT_EQ(rand_dat_1[i] + rand_dat_2[i], vec_sum_3_1[i]) << "Vector<3> index: " << static_cast<int>(i);
        EXPECT_FLOAT_EQ(vec_sum_3_F64_1[i], vec_sum_3_F64_2[i]) << "Vector<3> index: " << static_cast<int>(i);
        EXPECT_FLOAT_EQ(vec_sum_3_1[i], vec_sum_3_2[i]) << "Vector<3> index: " << static_cast<int>(i);

        EXPECT_FLOAT_EQ(rand_dat_1[i] + rand_dat_2[i], vec_sum_3D_1[i]) << "Vector3D index: " << static_cast<int>(i);
        EXPECT_FLOAT_EQ(vec_sum_3_F64_1[i], vec_sum_3_F64_2[i]) << "Vector<3> index: " << static_cast<int>(i);
        EXPECT_FLOAT_EQ(vec_sum_3D_1[i], vec_sum_3D_2[i]) << "Vector3D index: " << static_cast<int>(i);
    }
}
TEST(Vector_tests, subtraction) {
    const std::array<float, 3> rand_dat_1 = {rand_val(200), rand_val(200), rand_val(200)},
                               rand_dat_2 = {rand_val(200), rand_val(200), rand_val(200)};
    const std::array<F64, 3> rand_dat_F64_1 = {rand_val(200), rand_val(200), rand_val(200)},
                             rand_dat_F64_2 = {rand_val(200), rand_val(200), rand_val(200)};

    const geo::Vector<3> test_vec_3_1(rand_dat_1), test_vec_3_2(rand_dat_2);
    const geo::Vector<3, F64> test_vec_3_F64_1(rand_dat_F64_1), test_vec_3_F64_2(rand_dat_F64_2);
    const geo::Vector<3> test_vec_3D_1(rand_dat_1), test_vec_3D_2(rand_dat_2);

    // testing A + B = B + A
    const auto vec_difference_3_1 = test_vec_3_1 - test_vec_3_2;
    const auto vec_difference_3_2 = test_vec_3_2 - test_vec_3_1;

    const auto vec_difference_3_F64_1 = test_vec_3_F64_1 - test_vec_3_F64_2;
    const auto vec_difference_3_F64_2 = test_vec_3_F64_2 - test_vec_3_F64_1;

    const auto vec_difference_3D_1 = test_vec_3D_1 - test_vec_3D_2;
    const auto vec_difference_3D_2 = test_vec_3D_2 - test_vec_3D_1;

    for (FwSizeType i = 0; i < 3; i++) {
        EXPECT_FLOAT_EQ(rand_dat_1[i] - rand_dat_2[i], vec_difference_3_1[i])
            << "Vector<3> index: " << static_cast<int>(i);
        EXPECT_FLOAT_EQ(rand_dat_2[i] - rand_dat_1[i], vec_difference_3_2[i])
            << "Vector<3> index: " << static_cast<int>(i);

        EXPECT_FLOAT_EQ(rand_dat_F64_1[i] - rand_dat_F64_2[i], vec_difference_3_F64_1[i])
            << "Vector<3> index: " << static_cast<int>(i);
        EXPECT_FLOAT_EQ(rand_dat_F64_2[i] - rand_dat_F64_1[i], vec_difference_3_F64_2[i])
            << "Vector<3> index: " << static_cast<int>(i);

        EXPECT_FLOAT_EQ(rand_dat_1[i] - rand_dat_2[i], vec_difference_3D_1[i])
            << "Vector<3> index: " << static_cast<int>(i);
        EXPECT_FLOAT_EQ(rand_dat_2[i] - rand_dat_1[i], vec_difference_3D_2[i])
            << "Vector<3> index: " << static_cast<int>(i);
    }
}
TEST(Vector_tests, scalar_multiplication) {
    const std::array<float, 3> rand_dat = {rand_val(200), rand_val(200), rand_val(200)};
    const std::array<F64, 3> rand_dat_F64 = {rand_val(200), rand_val(200), rand_val(200)};

    const geo::Vector<3> test_vec_3(rand_dat);
    const geo::Vector<3, F64> test_vec_3_F64(rand_dat_F64);
    const geo::Vector3D test_vec_3D(rand_dat);

    const auto scale_factor = rand_val(10);

    const auto test_prod_3 = test_vec_3 * scale_factor;
    const auto test_prod_3_F64 = test_vec_3_F64 * static_cast<F64>(scale_factor);
    const auto test_prod_3D = test_vec_3D * scale_factor;

    for (FwSizeType i = 0; i < 3; i++) {
        EXPECT_FLOAT_EQ(rand_dat[i] * scale_factor, test_prod_3D[i]) << "Vector<3> index: " << static_cast<int>(i);
        EXPECT_FLOAT_EQ(rand_dat_F64[i] * static_cast<F64>(scale_factor), test_prod_3_F64[i])
            << "Vector<3, F64> index: " << static_cast<int>(i);
        EXPECT_FLOAT_EQ(rand_dat[i] * scale_factor, test_prod_3[i]) << "Vector3D index: " << static_cast<int>(i);
    }
}
TEST(Vector_tests, scalar_division) {
    const std::array<float, 3> rand_dat = {rand_val(200), rand_val(200), rand_val(200)};
    const std::array<F64, 3> rand_dat_F64 = {rand_val(200), rand_val(200), rand_val(200)};

    const geo::Vector<3> test_vec_3(rand_dat);
    const geo::Vector<3, F64> test_vec_3_F64(rand_dat_F64);
    const geo::Vector3D test_vec_3D(rand_dat);

    const auto scale_factor = rand_val(10);

    const auto test_quotient_3 = test_vec_3 / scale_factor;
    const auto test_quotient_3_F64 = test_vec_3_F64 / static_cast<F64>(scale_factor);
    const auto test_quotient_3D = test_vec_3D / scale_factor;

    for (FwSizeType i = 0; i < 3; i++) {
        EXPECT_FLOAT_EQ(rand_dat[i] / scale_factor, test_quotient_3[i]) << "Vector<3> index: " << static_cast<int>(i);
        EXPECT_FLOAT_EQ(rand_dat_F64[i] / static_cast<F64>(scale_factor), test_quotient_3_F64[i])
            << "Vector<3, F64> index: " << static_cast<int>(i);
        EXPECT_FLOAT_EQ(rand_dat[i] / scale_factor, test_quotient_3D[i]) << "Vector3D index: " << static_cast<int>(i);
    }
}

}  // namespace geo
