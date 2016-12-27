#include "core/geometry.h"
#include "tests/test.h"

void Vector2IntEquals(liang::Vector2i vec, int x, int y) {
  ASSERT_EQ(vec.x, x);
  ASSERT_EQ(vec.y, y);
}

void Vector2FloatEquals(liang::Vector2f vec, float x, float y) {
  ASSERT_FLOAT_EQ(vec.x, x);
  ASSERT_FLOAT_EQ(vec.y, y);
}

void Vector3IntEquals(liang::Vector3i vec, int x, int y, int z) {
  ASSERT_EQ(vec.x, x);
  ASSERT_EQ(vec.y, y);
  ASSERT_EQ(vec.z, z);
}

void Vector3FloatEquals(liang::Vector3f vec, float x, float y, float z) {
  ASSERT_FLOAT_EQ(vec.x, x);
  ASSERT_FLOAT_EQ(vec.y, y);
  ASSERT_FLOAT_EQ(vec.z, z);
}

TEST(GeometryTest, Vector2Creation) {
  liang::Vector2i default_int_vector = liang::Vector2i();
  Vector2IntEquals(default_int_vector, 0, 0);
  liang::Vector2i initialized_int_vector = liang::Vector2i(-5, 5);
  Vector2IntEquals(initialized_int_vector, -5, 5);

  liang::Vector2f default_float_vector = liang::Vector2f();
  Vector2FloatEquals(default_float_vector, 0.0, 0.0);
  liang::Vector2f initialized_float_vector = liang::Vector2f(-5.0, 5.0);
  Vector2FloatEquals(initialized_float_vector, -5.0, 5.0);
}

TEST(GeometryTest, Vector2Indexing) {
  liang::Vector2i vec = liang::Vector2i(1, 2);
  Vector2IntEquals(vec, vec[0], vec[1]);
  vec[0] = 3;
  vec[1] = 4;
  Vector2IntEquals(vec, 3, 4);
}

TEST(GeometryTest, Vector2IndexingOutOfRange) {
  liang::Vector2i vec = liang::Vector2i(1, 2);
  ASSERT_DEATH(vec[2], liang::ASSERTION_FAILURE);
  ASSERT_DEATH(vec[-1], liang::ASSERTION_FAILURE);
  ASSERT_DEATH({ vec[2] = 5; }, liang::ASSERTION_FAILURE);
  ASSERT_DEATH({ vec[-1] = 5; }, liang::ASSERTION_FAILURE);
}

TEST(GeometryTest, Vector2Addition) {
  liang::Vector2f vec1 = liang::Vector2f(1.1, 2.2);
  liang::Vector2f vec2 = liang::Vector2f(0.5, 0.6);
  auto vec3 = vec1 + vec2;
  Vector2FloatEquals(vec1, 1.1, 2.2);
  Vector2FloatEquals(vec2, 0.5, 0.6);
  Vector2FloatEquals(vec3, 1.6, 2.8);

  vec1 += vec2;
  Vector2FloatEquals(vec1, 1.6, 2.8);
  Vector2FloatEquals(vec2, 0.5, 0.6);
}

TEST(GeometryTest, Vector2Subtraction) {
  liang::Vector2f vec1 = liang::Vector2f(1.6, 2.8);
  liang::Vector2f vec2 = liang::Vector2f(0.3, 0.4);
  auto vec3 = vec1 - vec2;
  Vector2FloatEquals(vec1, 1.6, 2.8);
  Vector2FloatEquals(vec2, 0.3, 0.4);
  Vector2FloatEquals(vec3, 1.3, 2.4);

  vec1 -= vec2;
  Vector2FloatEquals(vec1, 1.3, 2.4);
  Vector2FloatEquals(vec2, 0.3, 0.4);
}

TEST(GeometryTest, Vector2Multiplication) {
  liang::Vector2f vec1 = liang::Vector2f(1.1, 2.1);
  auto vec2 = vec1 * 2.0;
  Vector2FloatEquals(vec1, 1.1, 2.1);
  Vector2FloatEquals(vec2, 2.2, 4.2);

  vec1 *= 10.0;
  Vector2FloatEquals(vec1, 11.0, 21.0);
}

TEST(GeometryTest, Vector2Division) {
  liang::Vector2f vec1 = liang::Vector2f(10.5, 20.5);
  auto vec2 = vec1 / 5.0;
  Vector2FloatEquals(vec1, 10.5, 20.5);
  Vector2FloatEquals(vec2, 2.1,  4.1);

  vec1 /= 10.0;
  Vector2FloatEquals(vec1, 1.05, 2.05);
}

TEST(GeometryTest, Vector2DivisonByZero) {
  liang::Vector2f vec = liang::Vector2f(1.0, 2.0);
  ASSERT_DEATH(vec / 0.0, liang::ASSERTION_FAILURE);
  ASSERT_DEATH({ vec /= 0.0; }, liang::ASSERTION_FAILURE);
}

TEST(GeometryTest, Vector2Abs) {
  liang::Vector2f vec = liang::Vector2f(-1.0, -2.0);
  Vector2FloatEquals(liang::Abs(vec), 1.0, 2.0);
}

TEST(GeometryTest, Vector2Dot) {
  liang::Vector2f vec1 = liang::Vector2f(3.2, -5.2);
  liang::Vector2f vec2 = liang::Vector2f(1.6, 123.4);
  float dot = liang::Dot(vec1, vec2);
  float dot_reversed = liang::Dot(vec2, vec1);
  Vector2FloatEquals(vec1, 3.2, -5.2);
  Vector2FloatEquals(vec2, 1.6, 123.4);
  ASSERT_FLOAT_EQ(-636.56, dot);
  ASSERT_FLOAT_EQ(-636.56, dot_reversed);
}

TEST(GeometryTest, Vector2Length) {
  liang::Vector2f vec = liang::Vector2f(3.0, 4.0);
  ASSERT_FLOAT_EQ(25.0, vec.LengthSquared());
  ASSERT_FLOAT_EQ(5.0, vec.Length());
}

TEST(GeometryTest, Vector2Normalize) {
  liang::Vector2f vec = liang::Vector2f(3.0, 4.0);
  liang::Vector2f normalized = liang::Normalize(vec);
  Vector2FloatEquals(vec, 3.0, 4.0);
  Vector2FloatEquals(normalized, 0.6, 0.8);
  ASSERT_FLOAT_EQ(1.0, normalized.Length());
  ASSERT_FLOAT_EQ(1.0, normalized.LengthSquared());
}

TEST(GeometryTest, Vector3Creation) {
  liang::Vector3i default_int_vector = liang::Vector3i();
  Vector3IntEquals(default_int_vector, 0, 0, 0);
  liang::Vector3i initialized_int_vector = liang::Vector3i(-5, 5, -10);
  Vector3IntEquals(initialized_int_vector, -5, 5, -10);

  liang::Vector3f default_float_vector = liang::Vector3f();
  Vector3FloatEquals(default_float_vector, 0.0, 0.0, 0.0);
  liang::Vector3f initialized_float_vector = liang::Vector3f(-5.0, 5.0, -10.0);
  Vector3FloatEquals(initialized_float_vector, -5.0, 5.0, -10.0);
}

TEST(GeometryTest, Vector3Indexing) {
  liang::Vector3i vec = liang::Vector3i(1, 2, 3);
  Vector3IntEquals(vec, vec[0], vec[1], vec[2]);
  vec[0] = 4;
  vec[1] = 5;
  vec[2] = 6;
  Vector3IntEquals(vec, 4, 5, 6);
}

TEST(GeometryTest, Vector3IndexingOutOfRange) {
  liang::Vector3i vec = liang::Vector3i(1, 2, 3);
  ASSERT_DEATH(vec[3], liang::ASSERTION_FAILURE);
  ASSERT_DEATH(vec[-1], liang::ASSERTION_FAILURE);
  ASSERT_DEATH({ vec[3] = 5; }, liang::ASSERTION_FAILURE);
  ASSERT_DEATH({ vec[-1] = 5; }, liang::ASSERTION_FAILURE);
}

TEST(GeometryTest, Vector3Addition) {
  liang::Vector3f vec1 = liang::Vector3f(1.1, 2.2, 3.3);
  liang::Vector3f vec2 = liang::Vector3f(0.5, 0.6, 0.7);
  auto vec3 = vec1 + vec2;
  Vector3FloatEquals(vec1, 1.1, 2.2, 3.3);
  Vector3FloatEquals(vec2, 0.5, 0.6, 0.7);
  Vector3FloatEquals(vec3, 1.6, 2.8, 4.0);

  vec1 += vec2;
  Vector3FloatEquals(vec1, 1.6, 2.8, 4.0);
  Vector3FloatEquals(vec2, 0.5, 0.6, 0.7);
}

TEST(GeometryTest, Vector3Subtraction) {
  liang::Vector3f vec1 = liang::Vector3f(1.6, 2.8, 5.6);
  liang::Vector3f vec2 = liang::Vector3f(0.3, 0.4, 0.5);
  auto vec3 = vec1 - vec2;
  Vector3FloatEquals(vec1, 1.6, 2.8, 5.6);
  Vector3FloatEquals(vec2, 0.3, 0.4, 0.5);
  Vector3FloatEquals(vec3, 1.3, 2.4, 5.1);

  vec1 -= vec2;
  Vector3FloatEquals(vec1, 1.3, 2.4, 5.1);
  Vector3FloatEquals(vec2, 0.3, 0.4, 0.5);
}

TEST(GeometryTest, Vector3Multiplication) {
  liang::Vector3f vec1 = liang::Vector3f(1.1, 2.1, 3.1);
  auto vec2 = vec1 * 2.0;
  Vector3FloatEquals(vec1, 1.1, 2.1, 3.1);
  Vector3FloatEquals(vec2, 2.2, 4.2, 6.2);

  vec1 *= 10.0;
  Vector3FloatEquals(vec1, 11.0, 21.0, 31.0);
}

TEST(GeometryTest, Vector3Division) {
  liang::Vector3f vec1 = liang::Vector3f(10.5, 20.5, 30.5);
  auto vec2 = vec1 / 5.0;
  Vector3FloatEquals(vec1, 10.5, 20.5, 30.5);
  Vector3FloatEquals(vec2, 2.1,  4.1, 6.1);

  vec1 /= 10.0;
  Vector3FloatEquals(vec1, 1.05, 2.05, 3.05);
}

TEST(GeometryTest, Vector3DivisonByZero) {
  liang::Vector3f vec = liang::Vector3f(1.0, 2.0, 3.0);
  ASSERT_DEATH(vec / 0.0, liang::ASSERTION_FAILURE);
  ASSERT_DEATH({ vec /= 0.0; }, liang::ASSERTION_FAILURE);
}

TEST(GeometryTest, Vector3Abs) {
  liang::Vector3f vec = liang::Vector3f(-1.0, -2.0, -3.0);
  Vector3FloatEquals(liang::Abs(vec), 1.0, 2.0, 3.0);
}

TEST(GeometryTest, Vector3Dot) {
  liang::Vector3f vec1 = liang::Vector3f(3.2, -5.2, 3.2);
  liang::Vector3f vec2 = liang::Vector3f(1.6, 123.4, -12.1);
  float dot = liang::Dot(vec1, vec2);
  float dot_reversed = liang::Dot(vec2, vec1);
  Vector3FloatEquals(vec1, 3.2, -5.2, 3.2);
  Vector3FloatEquals(vec2, 1.6, 123.4, -12.1);
  ASSERT_FLOAT_EQ(-675.28, dot);
  ASSERT_FLOAT_EQ(-675.28, dot_reversed);
}

TEST(GeometryTest, Vector3Length) {
  liang::Vector3f vec = liang::Vector3f(1.0, 2.0, 3.0);
  ASSERT_FLOAT_EQ(14.0, vec.LengthSquared());
  ASSERT_FLOAT_EQ(3.74165738, vec.Length());
}

TEST(GeometryTest, Vector3Normalize) {
  liang::Vector3f vec = liang::Vector3f(1.0, 2.0, 3.0);
  liang::Vector3f normalized = liang::Normalize(vec);
  Vector3FloatEquals(vec, 1.0, 2.0, 3.0);
  Vector3FloatEquals(normalized, 0.2672612, 0.53452248, 0.80178372);
  ASSERT_FLOAT_EQ(1.0, normalized.Length());
  ASSERT_FLOAT_EQ(1.0, normalized.LengthSquared());
}

TEST(GeometryTest, Vector3Cross) {
  liang::Vector3f vec1 = liang::Vector3f(3.0, 4.0, 5.0);
  liang::Vector3f vec2 = liang::Vector3f(0.1, -5.0, 10.0);
  Vector3FloatEquals(vec1, 3.0, 4.0, 5.0);
  Vector3FloatEquals(vec2, 0.1, -5.0, 10.0);
  Vector3FloatEquals(liang::Cross(vec1, vec2), 65.0, -29.5, -15.4);
}

TEST(GeometryTest, Vector3CreateCoordSystem) {
  liang::Vector3f vec1 = liang::Vector3f(0.6, 0.8, 0.0);
  liang::Vector3f vec2 = liang::Vector3f();
  liang::Vector3f vec3 = liang::Vector3f();
  liang::CreateCoordSystem(vec1, &vec2, &vec3);
  Vector3FloatEquals(vec1, 0.6, 0.8, 0.0);
  Vector3FloatEquals(vec2, 0.0, 0.0, -1.0);
  Vector3FloatEquals(vec3, -0.8, 0.6, 0.0);
}
