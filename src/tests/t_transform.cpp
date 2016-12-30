#include "core/transform.h"
#include "tests/test.h"

void AssertMatEquals(const liang::Matrix4x4 &matrix, const std::vector<float> &values) {
  for (int i = 0; i < 16; i++) {
    ASSERT_NEAR(values[i], matrix.Get(i / 4, i % 4), 0.00001);
  }
}

TEST(TransformTest, Matrix4x4Creation) {
  liang::Matrix4x4 mat = liang::Matrix4x4();
  AssertMatEquals(mat, std::vector<float>{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1});
  float array_2d[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
  mat = liang::Matrix4x4(array_2d);
  AssertMatEquals(mat, std::vector<float>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
  float array_1d[16] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32};
  mat = liang::Matrix4x4(array_1d);
  AssertMatEquals(mat, std::vector<float>{2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30,
      32});
}

TEST(TransformTest, Matrix4x4Equality) {
  float values[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  float other_values[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 20};
  liang::Matrix4x4 mat1 = liang::Matrix4x4(values);
  liang::Matrix4x4 mat2 = liang::Matrix4x4(values);
  liang::Matrix4x4 mat3 = liang::Matrix4x4(other_values);
  ASSERT_TRUE(mat1 == mat2);
  ASSERT_FALSE(mat1 == mat3);
  ASSERT_FALSE(mat2 == mat3);
}

TEST(TransformTest, Matrix4x4Inequality) {
  float values[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  float other_values[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 20};
  liang::Matrix4x4 mat1 = liang::Matrix4x4(values);
  liang::Matrix4x4 mat2 = liang::Matrix4x4(values);
  liang::Matrix4x4 mat3 = liang::Matrix4x4(other_values);
  ASSERT_FALSE(mat1 != mat2);
  ASSERT_TRUE(mat1 != mat3);
  ASSERT_TRUE(mat2 != mat3);
}

TEST(TransformTest, Matrix4x4Indexing) {
  float values[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  liang::Matrix4x4 mat = liang::Matrix4x4(values);
  for (int i = 0; i < 16; i++) {
    ASSERT_EQ((float)i, mat[i]);
  }
}

TEST(TransformTest, Matrix4x4IndexingOutOfBounds) {
  liang::Matrix4x4 mat = liang::Matrix4x4();
  ASSERT_DEATH(mat[-1], liang::ASSERTION_FAILURE);
  ASSERT_DEATH(mat[17], liang::ASSERTION_FAILURE);
}

TEST(TransformTest, Matrix4x4Multiplication) {
  float values1[16] = {4, 1, 3, 2, 5, 6, 7, 8, 10, 9, 12, 11, 16, 15, 14, 12};
  liang::Matrix4x4 mat1 = liang::Matrix4x4(values1);
  float values2[16] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, -0.1, -0.2, -0.3, -0.4, -0.5, -0.6,
      -0.7, -0.8};
  liang::Matrix4x4 mat2 = liang::Matrix4x4(values2);
  AssertMatEquals(mat1 * mat2, std::vector<float>{-0.4, -0.4, -0.4, -0.4, -1.2, -1.6, -2.0, -2.4,
      -1.2, -1.6, -2.0, -2.4, 1.7, 2.2, 2.7, 3.2});
  AssertMatEquals(mat2 * mat1, std::vector<float>{10.8, 10.0, 10.9, 9.9, 24.8, 22.4, 25.3, 23.1,
      -10.8, -10.0, -10.9, -9.9, -24.8, -22.4, -25.3, -23.1});
  ASSERT_TRUE(mat1 == (mat1 * liang::Matrix4x4()));
  mat1 *= mat2;
  AssertMatEquals(mat1, std::vector<float>{-0.4, -0.4, -0.4, -0.4, -1.2, -1.6, -2.0, -2.4,
      -1.2, -1.6, -2.0, -2.4, 1.7, 2.2, 2.7, 3.2});
}

TEST(TransformTest, Matrix4x4Get) {
  float values[16] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30};
  liang::Matrix4x4 mat = liang::Matrix4x4(values);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ASSERT_EQ((i * 4 + j) * 2, mat.Get(i, j));
    }
  }
}

TEST(TransformTest, Matrix4x4GetOutOfBounds) {
  liang::Matrix4x4 mat = liang::Matrix4x4();
  ASSERT_DEATH(mat.Get(5, 0), liang::ASSERTION_FAILURE);
  ASSERT_DEATH(mat.Get(0, 5), liang::ASSERTION_FAILURE);
  ASSERT_DEATH(mat.Get(5, 5), liang::ASSERTION_FAILURE);
}

TEST(TransformTest, Matrix4x4Set) {
  liang::Matrix4x4 mat = liang::Matrix4x4();
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      mat.Set(i, j, (i * 4 + j));
    }
  }
  AssertMatEquals(mat, std::vector<float>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15});
}

TEST(TransformTest, Matrix4x4SetOutOfBounds) {
  liang::Matrix4x4 mat = liang::Matrix4x4();
  ASSERT_DEATH(mat.Set(5, 0, 0), liang::ASSERTION_FAILURE);
  ASSERT_DEATH(mat.Set(0, 5, 0), liang::ASSERTION_FAILURE);
  ASSERT_DEATH(mat.Set(5, 5, 0), liang::ASSERTION_FAILURE);
}

TEST(TransformTest, Matrix4x4Transpose) {
  liang::Matrix4x4 identity = liang::Matrix4x4();
  ASSERT_TRUE(identity == liang::Transpose(identity));
  float values[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  liang::Matrix4x4 mat = liang::Matrix4x4(values);
  AssertMatEquals(liang::Transpose(mat), std::vector<float>{0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10,
      14, 3, 7, 11, 15});
  AssertMatEquals(liang::Transpose(liang::Transpose(mat)), std::vector<float>{0, 1, 2, 3, 4, 5, 6,
      7, 8, 9, 10, 11, 12, 13, 14, 15});
}

TEST(TransformTest, Matrix4x4Inverse) {
  float values1[16] = {4, 1, 3, 2, 5, 6, 7, 8, 10, 9, 12, 11, 16, 15, 14, 12};
  liang::Matrix4x4 mat1 = liang::Matrix4x4(values1);
  AssertMatEquals(liang::Inverse(mat1), std::vector<float>{0.55029586, 0.31360947, -0.43786982,
      0.10059172, -0.43786982, -0.14201183, 0.04733728, 0.12426036, -0.58579882, -0.94674556,
      0.98224852, -0.17159763, 0.49704142, 0.86390533, -0.62130178, -0.00591716});
  AssertMatEquals(liang::Inverse(liang::Inverse(mat1)), std::vector<float>{4, 1, 3, 2, 5, 6, 7, 8,
      10, 9, 12, 11, 16, 15, 14, 12});
  float values2[16] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, -0.1, -0.2, -0.3, -0.4, -0.5, -0.6,
      -0.7, -0.8};
  liang::Matrix4x4 mat2 = liang::Matrix4x4(values2);
  ASSERT_DEATH(liang::Inverse(mat2), liang::ASSERTION_FAILURE);
}
