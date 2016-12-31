#include "core/geometry.h"
#include "core/transform.h"
#include "tests/util.h"
#include "tests/test.h"

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
  ASSERT_DEATH(mat[-1], ASSERTION_FAILURE);
  ASSERT_DEATH(mat[17], ASSERTION_FAILURE);
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
  ASSERT_DEATH(mat.Get(5, 0), ASSERTION_FAILURE);
  ASSERT_DEATH(mat.Get(0, 5), ASSERTION_FAILURE);
  ASSERT_DEATH(mat.Get(5, 5), ASSERTION_FAILURE);
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
  ASSERT_DEATH(mat.Set(5, 0, 0), ASSERTION_FAILURE);
  ASSERT_DEATH(mat.Set(0, 5, 0), ASSERTION_FAILURE);
  ASSERT_DEATH(mat.Set(5, 5, 0), ASSERTION_FAILURE);
}

TEST(TransformTest, Matrix4x4Transpose) {
  liang::Matrix4x4 identity = liang::Matrix4x4();
  ASSERT_TRUE(identity == identity.Transpose());
  float values[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  liang::Matrix4x4 mat = liang::Matrix4x4(values);
  AssertMatEquals(mat.Transpose(), std::vector<float>{0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10,
      14, 3, 7, 11, 15});
  AssertMatEquals(mat.Transpose().Transpose(), std::vector<float>{0, 1, 2, 3, 4, 5, 6,
      7, 8, 9, 10, 11, 12, 13, 14, 15});
}

TEST(TransformTest, Matrix4x4Inverse) {
  float values1[16] = {4, 1, 3, 2, 5, 6, 7, 8, 10, 9, 12, 11, 16, 15, 14, 12};
  liang::Matrix4x4 mat1 = liang::Matrix4x4(values1);
  AssertMatEquals(mat1.Inverse(), std::vector<float>{0.55029586, 0.31360947, -0.43786982,
      0.10059172, -0.43786982, -0.14201183, 0.04733728, 0.12426036, -0.58579882, -0.94674556,
      0.98224852, -0.17159763, 0.49704142, 0.86390533, -0.62130178, -0.00591716});
  AssertMatEquals(mat1.Inverse().Inverse(), std::vector<float>{4, 1, 3, 2, 5, 6, 7, 8,
      10, 9, 12, 11, 16, 15, 14, 12});
  float values2[16] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, -0.1, -0.2, -0.3, -0.4, -0.5, -0.6,
      -0.7, -0.8};
  liang::Matrix4x4 mat2 = liang::Matrix4x4(values2);
  ASSERT_DEATH(mat2.Inverse(), ASSERTION_FAILURE);
}

TEST(TransformTest, TransformCreation) {
  liang::Matrix4x4 identity = liang::Matrix4x4();
  ASSERT_TRUE(liang::Transform() == liang::Transform(identity, identity));
  ASSERT_TRUE(liang::Transform(identity) == liang::Transform(identity, identity));
}

TEST(TransformTest, TransformInverse) {
  ASSERT_TRUE(liang::ScaleTransform(2, 3, 4).Inverse() ==
      liang::ScaleTransform(0.5, 0.3333333, 0.25));
  float values[16] = {4, 1, 3, 2, 5, 6, 7, 8, 10, 9, 12, 11, 16, 15, 14, 12};
  liang::Matrix4x4 mat = liang::Matrix4x4(values);
  liang::Matrix4x4 mat_inverse = mat.Inverse();
  liang::Transform t = liang::Transform(mat, mat_inverse);
  liang::Transform t_inverse = liang::Transform(mat_inverse, mat);
  ASSERT_TRUE(t.Inverse() == t_inverse);
}

TEST(TransformTest, TransformTranspose) {
  ASSERT_TRUE(liang::ScaleTransform(2, 3, 4).Transpose() == liang::ScaleTransform(2, 3, 4));
  float values[16] = {4, 1, 3, 2, 5, 6, 7, 8, 10, 9, 12, 11, 16, 15, 14, 12};
  liang::Matrix4x4 mat = liang::Matrix4x4(values);
  liang::Matrix4x4 mat_inverse = mat.Inverse();
  liang::Transform t = liang::Transform(mat, mat_inverse);
  liang::Transform t_transpose = liang::Transform(mat.Transpose(), mat_inverse.Transpose());
  ASSERT_TRUE(t.Transpose() == t_transpose);
}

TEST(TransformTest, TransformEquality) {
  ASSERT_TRUE(liang::ScaleTransform(2, 3, 4) == liang::ScaleTransform(2, 3, 4));
  ASSERT_FALSE(liang::ScaleTransform(2, 3, 4) == liang::ScaleTransform(3, 3, 4));
}

TEST(TransformTest, TransformTranslation) {
  liang::Transform translation = liang::TranslationTransform(liang::Vector3f(2, 3, 4));
  float values[16] = {1, 0, 0, 2, 0, 1, 0, 3, 0, 0, 1, 4, 0, 0, 0, 1};
  liang::Transform expected = liang::Transform(liang::Matrix4x4(values));
  ASSERT_TRUE(expected == translation);
  liang::Point3f point = liang::Point3f(0.5, 0.6, 0.7);
  Point3FloatEquals(translation(point), 2.5, 3.6, 4.7);
  liang::Vector3f vec = liang::Vector3f(0.1, 0.2, 0.3);
  Vector3FloatEquals(translation(vec), 0.1, 0.2, 0.3);
  liang::Normal3f normal = liang::Normal3f(0.1, 0.2, 0.3);
  Normal3FloatEquals(translation(normal), 0.1, 0.2, 0.3);
  liang::Ray3f ray = liang::Ray3f(point, vec);
  Point3FloatEquals(translation(ray).origin, 2.5, 3.6, 4.7);
  Vector3FloatEquals(translation(ray).direction, 0.1, 0.2, 0.3);
  liang::AABB3f box = liang::AABB3f(liang::Point3f(1.0, 1.0, 1.0), liang::Point3f(2.0, 2.0, 2.0));
  AABB3FloatEquals(translation(box), 3.0, 4.0, 5.0, 4.0, 5.0, 6.0);
}

TEST(TransformTest, TransformScale) {
  liang::Transform scale = liang::ScaleTransform(2, 3, 4);
  float values[16] = {2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 4, 0, 0, 0, 0, 1};
  liang::Transform expected = liang::Transform(liang::Matrix4x4(values));
  ASSERT_TRUE(expected == scale);
  liang::Point3f point = liang::Point3f(0.5, 0.6, 0.7);
  Point3FloatEquals(scale(point), 1.0, 1.8, 2.8);
  liang::Vector3f vec = liang::Vector3f(0.1, 0.2, 0.3);
  Vector3FloatEquals(scale(vec), 0.2, 0.6, 1.2);
  liang::Normal3f normal = liang::Normal3f(0.1, 0.2, 0.3);
  Normal3FloatEquals(scale(normal), 0.05, 0.06666667, 0.075);
  liang::Ray3f ray = liang::Ray3f(point, vec);
  Point3FloatEquals(scale(ray).origin, 1.0, 1.8, 2.8);
  Vector3FloatEquals(scale(ray).direction, 0.2, 0.6, 1.2);
  liang::AABB3f box = liang::AABB3f(liang::Point3f(1.0, 1.0, 1.0), liang::Point3f(2.0, 2.0, 2.0));
  AABB3FloatEquals(scale(box), 2.0, 3.0, 4.0, 4.0, 6.0, 8.0);
}

// TODO(brkho): Maybe fill these in sometime so it also transforms points, but I just can't be
// bothered right now.
TEST(TransformTest, TransformRotateX) {
  float radians = PI / 4.0;
  float r2o2 = std::sqrt(2) / 2.0;
  liang::Transform rotate = liang::RotateXTransform(radians);
  float values[16] = {1, 0, 0, 0, 0, r2o2, -r2o2, 0, 0, r2o2, r2o2, 0, 0, 0, 0, 1};
  liang::Transform expected = liang::Transform(liang::Matrix4x4(values));
  ASSERT_TRUE(expected == rotate);
}

TEST(TransformTest, TransformRotateY) {
  float radians = PI / 4.0;
  float r2o2 = std::sqrt(2) / 2.0;
  liang::Transform rotate = liang::RotateYTransform(radians);
  float values[16] = {r2o2, 0, r2o2, 0, 0, 1, 0, 0, -r2o2, 0, r2o2, 0, 0, 0, 0, 1};
  liang::Transform expected = liang::Transform(liang::Matrix4x4(values));
  ASSERT_TRUE(expected == rotate);
}

TEST(TransformTest, TransformRotateZ) {
  float radians = PI / 4.0;
  float r2o2 = std::sqrt(2) / 2.0;
  liang::Transform rotate = liang::RotateZTransform(radians);
  float values[16] = {r2o2, -r2o2, 0, 0, r2o2, r2o2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
  liang::Transform expected = liang::Transform(liang::Matrix4x4(values));
  ASSERT_TRUE(expected == rotate);
}

TEST(TransformTest, TransformArbitraryAxisRotate) {
  liang::Transform rotate = liang::RotateArbitraryAxisTransform(
      liang::Vector3f(0.58139534, 0.29069767, 0.40697674), 1.0);
  float values[16] = {0.804496, -0.314445, 0.503895, 0, 0.578639, 0.606351, -0.54545, 0, -0.134023,
      0.730385, 0.669757, 0, 0, 0, 0, 1};
  liang::Transform expected = liang::Transform(liang::Matrix4x4(values));
  ASSERT_TRUE(expected == rotate);
}

TEST(TransformTest, TransformLookAt) {
  liang::Transform look = liang::LookAtTransformation(liang::Vector3f(1.0, 2.0, 3.0),
      liang::Vector3f(-2.0, -5.0, 3.0), liang::Vector3f(1.0, 0.0, 0.0));
  float values[16] = {0, 0, -1, 3, 0.919145, -0.393919, 0, -0.131306, -0.393919, -0.919145, 0,
      2.232209, 0, 0, 0, 1};
  liang::Transform expected = liang::Transform(liang::Matrix4x4(values));
  ASSERT_TRUE(expected == look);
}

TEST(TransformTest, TransformComposition) {
  liang::Transform translate = liang::TranslationTransform(liang::Vector3f(1.0, 2.0, 3.0));
  liang::Transform scale = liang::ScaleTransform(-1.0, 2.0, 5.0);
  liang::Transform rotate = liang::RotateXTransform(PI / 2);
  float values[16] = {-1,  0, 0, 1, 0, 0, -2, 2, 0, 5, 0, 3, 0, 0, 0, 1};
  liang::Transform expected = liang::Transform(liang::Matrix4x4(values));
  ASSERT_TRUE(expected == (translate * scale * rotate));
  ASSERT_FALSE((translate * scale * rotate) == (rotate * scale * translate));
}
