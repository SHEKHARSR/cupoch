#pragma once

// TEST_DATA_DIR defined in CMakeLists.txt
// Put it here to avoid editor warnings
#ifndef TEST_DATA_DIR
#define TEST_DATA_DIR
#endif

#include <gtest/gtest.h>
#include <Eigen/Core>
#include <thrust/host_vector.h>

#include "tests/test_utility/print.h"
#include "tests/test_utility/rand.h"
#include "tests/test_utility/sort.h"

namespace unit_test {
// thresholds for comparing floating point values
const float THRESHOLD_1E_4 = 1e-4;

// Eigen Zero()
const Eigen::Vector2f Zero2f = Eigen::Vector2f::Zero();
const Eigen::Vector3f Zero3f = Eigen::Vector3f::Zero();
const Eigen::Matrix<float, 6, 1> Zero6f = Eigen::Matrix<float, 6, 1>::Zero();
const Eigen::Vector2i Zero2i = Eigen::Vector2i::Zero();

// Mechanism for reporting unit tests for which there is no implementation yet.
void NotImplemented();

// Equal test.
template <class T, int M, int N, int A>
void ExpectEQ(const Eigen::Matrix<T, M, N, A>& v0,
              const Eigen::Matrix<T, M, N, A>& v1,
              double threshold = THRESHOLD_1E_4) {
    EXPECT_EQ(v0.size(), v1.size());
    for (int i = 0; i < v0.size(); i++)
        EXPECT_NEAR(v0.coeff(i), v1.coeff(i), threshold);
}
template <class T, int M, int N, int A>
void ExpectEQ(const thrust::host_vector<Eigen::Matrix<T, M, N, A>>& v0,
              const thrust::host_vector<Eigen::Matrix<T, M, N, A>>& v1,
              double threshold = THRESHOLD_1E_4) {
    EXPECT_EQ(v0.size(), v1.size());
    for (size_t i = 0; i < v0.size(); i++) ExpectEQ(v0[i], v1[i], threshold);
}
template <class T, int M, int N, int A>
void ExpectEQ(
        const std::vector<Eigen::Matrix<T, M, N, A>,
                          Eigen::aligned_allocator<Eigen::Matrix<T, M, N, A>>>&
                v0,
        const std::vector<Eigen::Matrix<T, M, N, A>,
                          Eigen::aligned_allocator<Eigen::Matrix<T, M, N, A>>>&
                v1,
        double threshold = THRESHOLD_1E_4) {
    EXPECT_EQ(v0.size(), v1.size());
    for (size_t i = 0; i < v0.size(); i++) ExpectEQ(v0[i], v1[i], threshold);
}

// Less than or Equal test.
template <class T, int M, int N, int A>
void ExpectLE(const Eigen::Matrix<T, M, N, A>& v0,
              const Eigen::Matrix<T, M, N, A>& v1) {
    EXPECT_EQ(v0.size(), v1.size());
    for (int i = 0; i < v0.size(); i++) EXPECT_LE(v0.coeff(i), v1.coeff(i));
}
template <class T, int M, int N, int A>
void ExpectLE(const Eigen::Matrix<T, M, N, A>& v0,
              const thrust::host_vector<Eigen::Matrix<T, M, N, A>>& v1) {
    for (size_t i = 0; i < v1.size(); i++) ExpectLE(v0, v1[i]);
}
template <class T, int M, int N, int A>
void ExpectLE(const thrust::host_vector<Eigen::Matrix<T, M, N, A>>& v0,
              const thrust::host_vector<Eigen::Matrix<T, M, N, A>>& v1) {
    EXPECT_EQ(v0.size(), v1.size());
    for (size_t i = 0; i < v0.size(); i++) ExpectLE(v0[i], v1[i]);
}

// Greater than or Equal test.
template <class T, int M, int N, int A>
void ExpectGE(const Eigen::Matrix<T, M, N, A>& v0,
              const Eigen::Matrix<T, M, N, A>& v1) {
    EXPECT_EQ(v0.size(), v1.size());
    for (int i = 0; i < v0.size(); i++) EXPECT_GE(v0.coeff(i), v1.coeff(i));
}
template <class T, int M, int N, int A>
void ExpectGE(const Eigen::Matrix<T, M, N, A>& v0,
              const thrust::host_vector<Eigen::Matrix<T, M, N, A>>& v1) {
    for (size_t i = 0; i < v1.size(); i++) ExpectGE(v0, v1[i]);
}
template <class T, int M, int N, int A>
void ExpectGE(const thrust::host_vector<Eigen::Matrix<T, M, N, A>>& v0,
              const thrust::host_vector<Eigen::Matrix<T, M, N, A>>& v1) {
    EXPECT_EQ(v0.size(), v1.size());
    for (size_t i = 0; i < v0.size(); i++) ExpectGE(v0[i], v1[i]);
}

// Test equality of two arrays of uint8_t.
void ExpectEQ(const uint8_t* const v0,
              const uint8_t* const v1,
              const size_t& size);

// Test equality of two vectors of uint8_t.
void ExpectEQ(const thrust::host_vector<uint8_t>& v0, const thrust::host_vector<uint8_t>& v1);

// Test equality of two arrays of int.
void ExpectEQ(const int* const v0, const int* const v1, const size_t& size);

// Test equality of two vectors of int.
void ExpectEQ(const thrust::host_vector<int>& v0, const thrust::host_vector<int>& v1);

// Test equality of two arrays of float.
void ExpectEQ(const float* const v0, const float* const v1, const size_t& size);

// Test equality of two vectors of float.
void ExpectEQ(const thrust::host_vector<float>& v0, const thrust::host_vector<float>& v1);

// Test equality of two arrays of double.
void ExpectEQ(const float* const v0,
              const float* const v1,
              const size_t& size);

// Reinterpret cast from uint8_t* to float*.
template <class T>
T* const Cast(uint8_t* data) {
    return reinterpret_cast<T* const>(data);
}
}  // namespace unit_test