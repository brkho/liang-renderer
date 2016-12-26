#include "core/geometry.h"
#include "tests/test.h"

void Vector2IntEquals(liang::Vector2<int> vec, int x, int y) {
  ASSERT_EQ(vec.x, x);
  ASSERT_EQ(vec.y, y);
}

void Vector2FloatEquals(liang::Vector2<float> vec, float x, float y) {
  ASSERT_FLOAT_EQ(vec.x, x);
  ASSERT_FLOAT_EQ(vec.y, y);
}

TEST(GeometryTest, Point2Creation) {
  liang::Vector2<int> default_int_vector = liang::Vector2<int>();
  Vector2IntEquals(default_int_vector, 0, 0);
  liang::Vector2<int> initialized_int_vector = liang::Vector2<int>(-5, 5);
  Vector2IntEquals(initialized_int_vector, -5, 5);

  liang::Vector2<float> default_float_vector = liang::Vector2<float>();
  Vector2FloatEquals(default_float_vector, 0.0, 0.0);
  liang::Vector2<float> initialized_float_vector = liang::Vector2<float>(-5.0, 5.0);
  Vector2FloatEquals(initialized_float_vector, -5.0, 5.0);
}

TEST(GeometryTest, Point2Indexing) {
  liang::Vector2<int> vec = liang::Vector2<int>(1, 2);
  Vector2IntEquals(vec, vec[0], vec[1]);
  vec[0] = 3;
  vec[1] = 4;
  Vector2IntEquals(vec, 3, 4);
}

TEST(GeometryTest, Point2IndexingOutOfRange) {
  liang::Vector2<int> vec = liang::Vector2<int>(1, 2);
  ASSERT_DEATH(vec[3], liang::ASSERTION_FAILURE);
  ASSERT_DEATH(vec[-1], liang::ASSERTION_FAILURE);
}

TEST(GeometryTest, Point2Addition) {
  liang::Vector2<float> vec1 = liang::Vector2<float>(1.1, 2.2);
  liang::Vector2<float> vec2 = liang::Vector2<float>(0.5, 0.6);
  auto vec3 = vec1 + vec2;
  Vector2FloatEquals(vec1, 1.1, 2.2);
  Vector2FloatEquals(vec2, 0.5, 0.6);
  Vector2FloatEquals(vec3, 1.6, 2.8);

  vec1 += vec2;
  Vector2FloatEquals(vec1, 1.6, 2.8);
  Vector2FloatEquals(vec2, 0.5, 0.6);
}
