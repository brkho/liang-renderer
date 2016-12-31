#include "tests/test.h"
#include "tests/util.h"

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
  ASSERT_DEATH(vec[2], ASSERTION_FAILURE);
  ASSERT_DEATH(vec[-1], ASSERTION_FAILURE);
  ASSERT_DEATH({ vec[2] = 5; }, ASSERTION_FAILURE);
  ASSERT_DEATH({ vec[-1] = 5; }, ASSERTION_FAILURE);
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
  ASSERT_DEATH(vec / 0.0, ASSERTION_FAILURE);
  ASSERT_DEATH({ vec /= 0.0; }, ASSERTION_FAILURE);
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
  ASSERT_DEATH(vec[3], ASSERTION_FAILURE);
  ASSERT_DEATH(vec[-1], ASSERTION_FAILURE);
  ASSERT_DEATH({ vec[3] = 5; }, ASSERTION_FAILURE);
  ASSERT_DEATH({ vec[-1] = 5; }, ASSERTION_FAILURE);
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
  ASSERT_DEATH(vec / 0.0, ASSERTION_FAILURE);
  ASSERT_DEATH({ vec /= 0.0; }, ASSERTION_FAILURE);
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

TEST(GeometryTest, Point2Creation) {
  liang::Point2i default_int_point = liang::Point2i();
  Point2IntEquals(default_int_point, 0, 0);
  liang::Point2i initialized_int_point = liang::Point2i(-5, 5);
  Point2IntEquals(initialized_int_point, -5, 5);

  liang::Point2f default_float_point = liang::Point2f();
  Point2FloatEquals(default_float_point, 0.0, 0.0);
  liang::Point2f initialized_float_point = liang::Point2f(-5.0, 5.0);
  Point2FloatEquals(initialized_float_point, -5.0, 5.0);
}

TEST(GeometryTest, Point2Indexing) {
  liang::Point2i vec = liang::Point2i(1, 2);
  Point2IntEquals(vec, vec[0], vec[1]);
  vec[0] = 3;
  vec[1] = 4;
  Point2IntEquals(vec, 3, 4);
}

TEST(GeometryTest, Point2IndexingOutOfBounds) {
  liang::Point2i vec = liang::Point2i(1, 2);
  ASSERT_DEATH(vec[-1], ASSERTION_FAILURE);
  ASSERT_DEATH(vec[2], ASSERTION_FAILURE);
  ASSERT_DEATH({ vec[-1] = 5; }, ASSERTION_FAILURE);
  ASSERT_DEATH({ vec[2] = 5; }, ASSERTION_FAILURE);
}

TEST(GeometryTest, Point2Addition) {
  liang::Point2f point = liang::Point2f(1.0, 2.0);
  liang::Vector2f vector = liang::Vector2f(0.5, 0.6);
  liang::Point2f translated = point + vector;
  Point2FloatEquals(point, 1.0, 2.0);
  Point2FloatEquals(translated, 1.5, 2.6);

  point += vector;
  Point2FloatEquals(point, 1.5, 2.6);
  Vector2FloatEquals(vector, 0.5, 0.6);
}

TEST(GeometryTest, Point2VectorSubtraction) {
  liang::Point2f point = liang::Point2f(1.0, 2.0);
  liang::Vector2f vector = liang::Vector2f(0.5, 0.6);
  liang::Point2f translated = point - vector;
  Point2FloatEquals(point, 1.0, 2.0);
  Point2FloatEquals(translated, 0.5, 1.4);

  point -= vector;
  Point2FloatEquals(point, 0.5, 1.4);
  Vector2FloatEquals(vector, 0.5, 0.6);
}

TEST(GeometryTest, Point2PointSubtraction) {
  liang::Point2f p1 = liang::Point2f(1.0, 2.0);
  liang::Point2f p2 = liang::Point2f(0.5, -0.5);
  Vector2FloatEquals(p1 - p2, 0.5, 2.5);
}

TEST(GeometryTest, Point2Distance) {
  liang::Point2f p1 = liang::Point2f(1.0, 2.0);
  liang::Point2f p2 = liang::Point2f(4.0, -2.0);
  ASSERT_FLOAT_EQ(5.0, liang::Distance(p1, p2));
  ASSERT_FLOAT_EQ(25.0, liang::DistanceSquared(p1, p2));
}

TEST(GeometryTest, Point2Lerp) {
  liang::Point2f p1 = liang::Point2f(1.0, 2.0);
  liang::Point2f p2 = liang::Point2f(2.0, 3.0);
  Point2FloatEquals(liang::Lerp(p1, p2, 0.0), 1.0, 2.0);
  Point2FloatEquals(liang::Lerp(p1, p2, 0.25), 1.25, 2.25);
  Point2FloatEquals(liang::Lerp(p1, p2, 0.5), 1.5, 2.5);
  Point2FloatEquals(liang::Lerp(p1, p2, 0.75), 1.75, 2.75);
  Point2FloatEquals(liang::Lerp(p1, p2, 1.0), 2.0, 3.0);
}

TEST(GeometryTest, Point2LerpOutOfBounds) {
  liang::Point2f p1 = liang::Point2f(1.0, 2.0);
  liang::Point2f p2 = liang::Point2f(2.0, 3.0);
  ASSERT_DEATH(liang::Lerp(p1, p2, -0.5), ASSERTION_FAILURE);
  ASSERT_DEATH(liang::Lerp(p1, p2, 1.1), ASSERTION_FAILURE);
}

TEST(GeometryTest, Point3Creation) {
  liang::Point3i default_int_point = liang::Point3i();
  Point3IntEquals(default_int_point, 0, 0, 0);
  liang::Point3i initialized_int_point = liang::Point3i(-5, 5, -10);
  Point3IntEquals(initialized_int_point, -5, 5, -10);

  liang::Point3f default_float_point = liang::Point3f();
  Point3FloatEquals(default_float_point, 0.0, 0.0, 0.0);
  liang::Point3f initialized_float_point = liang::Point3f(-5.0, 5.0, -10.0);
  Point3FloatEquals(initialized_float_point, -5.0, 5.0, -10.0);
}

TEST(GeometryTest, Point3Indexing) {
  liang::Point3i vec = liang::Point3i(1, 2, 3);
  Point3IntEquals(vec, vec[0], vec[1], vec[2]);
  vec[0] = 4;
  vec[1] = 5;
  vec[2] = 6;
  Point3IntEquals(vec, 4, 5, 6);
}

TEST(GeometryTest, Point3IndexingOutOfBounds) {
  liang::Point3i vec = liang::Point3i(1, 2, 3);
  ASSERT_DEATH(vec[-1], ASSERTION_FAILURE);
  ASSERT_DEATH(vec[3], ASSERTION_FAILURE);
  ASSERT_DEATH({ vec[-1] = 5; }, ASSERTION_FAILURE);
  ASSERT_DEATH({ vec[3] = 5; }, ASSERTION_FAILURE);
}


TEST(GeometryTest, Point3Addition) {
  liang::Point3f point = liang::Point3f(1.0, 2.0, 3.0);
  liang::Vector3f vector = liang::Vector3f(0.5, 0.6, 0.7);
  liang::Point3f translated = point + vector;
  Point3FloatEquals(point, 1.0, 2.0, 3.0);
  Point3FloatEquals(translated, 1.5, 2.6, 3.7);

  point += vector;
  Point3FloatEquals(point, 1.5, 2.6, 3.7);
  Vector3FloatEquals(vector, 0.5, 0.6, 0.7);
}

TEST(GeometryTest, Point3VectorSubtraction) {
  liang::Point3f point = liang::Point3f(1.0, 2.0, 3.0);
  liang::Vector3f vector = liang::Vector3f(0.5, 0.6, 0.7);
  liang::Point3f translated = point - vector;
  Point3FloatEquals(point, 1.0, 2.0, 3.0);
  Point3FloatEquals(translated, 0.5, 1.4, 2.3);

  point -= vector;
  Point3FloatEquals(point, 0.5, 1.4, 2.3);
  Vector3FloatEquals(vector, 0.5, 0.6, 0.7);
}

TEST(GeometryTest, Point3PointSubtraction) {
  liang::Point3f p1 = liang::Point3f(1.0, 2.0, 3.0);
  liang::Point3f p2 = liang::Point3f(0.5, -0.5, 1.0);
  Vector3FloatEquals(p1 - p2, 0.5, 2.5, 2.0);
}

TEST(GeometryTest, Point3Distance) {
  liang::Point3f p1 = liang::Point3f(4.0, 6.0, 8.0);
  liang::Point3f p2 = liang::Point3f(3.0, 4.0, 5.0);
  ASSERT_FLOAT_EQ(3.74165738, liang::Distance(p1, p2));
  ASSERT_FLOAT_EQ(14.0, liang::DistanceSquared(p1, p2));
}

TEST(GeometryTest, Point3Lerp) {
  liang::Point3f p1 = liang::Point3f(1.0, 2.0, 3.0);
  liang::Point3f p2 = liang::Point3f(2.0, 3.0, 4.0);
  Point3FloatEquals(liang::Lerp(p1, p2, 0.0), 1.0, 2.0, 3.0);
  Point3FloatEquals(liang::Lerp(p1, p2, 0.25), 1.25, 2.25, 3.25);
  Point3FloatEquals(liang::Lerp(p1, p2, 0.5), 1.5, 2.5, 3.5);
  Point3FloatEquals(liang::Lerp(p1, p2, 0.75), 1.75, 2.75, 3.75);
  Point3FloatEquals(liang::Lerp(p1, p2, 1.0), 2.0, 3.0, 4.0);
}

TEST(GeometryTest, Point3LerpOutOfBounds) {
  liang::Point3f p1 = liang::Point3f(1.0, 2.0, 3.0);
  liang::Point3f p2 = liang::Point3f(2.0, 3.0, 4.0);
  ASSERT_DEATH(liang::Lerp(p1, p2, -0.5), ASSERTION_FAILURE);
  ASSERT_DEATH(liang::Lerp(p1, p2, 1.1), ASSERTION_FAILURE);
}

TEST(GeometryTest, Normal3Creation) {
  liang::Normal3f default_normal = liang::Normal3f();
  Normal3FloatEquals(default_normal, 0.0, 0.0, 0.0);
  liang::Normal3f initialized_normal = liang::Normal3f(-5.0, 5.0, -10.0);
  Normal3FloatEquals(initialized_normal, -5.0, 5.0, -10.0);
}

TEST(GeometryTest, Ray3fCreation) {
  liang::Point3f origin = liang::Point3f(1.0, 2.0, 3.0);
  liang::Vector3f direction = liang::Vector3f(0.1, 0.2, 0.3);
  liang::Ray3f ray1 = liang::Ray3f(origin, direction, 5.0);
  Point3FloatEquals(ray1.origin, 1.0, 2.0, 3.0);
  Vector3FloatEquals(ray1.direction, 0.1, 0.2, 0.3);
  ASSERT_FLOAT_EQ(ray1.max_t, 5.0);

  liang::Ray3f ray2 = liang::Ray3f(origin, direction);
  Point3FloatEquals(ray2.origin, 1.0, 2.0, 3.0);
  Vector3FloatEquals(ray2.direction, 0.1, 0.2, 0.3);
  ASSERT_FLOAT_EQ(ray2.max_t, std::numeric_limits<float>::infinity());
}

TEST(GeometryTest, Ray3fParameterization) {
  liang::Point3f origin = liang::Point3f(1.0, 2.0, 3.0);
  liang::Vector3f direction = liang::Vector3f(0.1, 0.2, 0.3);
  liang::Ray3f ray = liang::Ray3f(origin, direction);
  Point3FloatEquals(ray(0.0), 1.0, 2.0, 3.0);
  Point3FloatEquals(ray(1.0), 1.1, 2.2, 3.3);
  Point3FloatEquals(ray(2.0), 1.2, 2.4, 3.6);
  Point3FloatEquals(ray(10.0), 2.0, 4.0, 6.0);
}

TEST(GeometryTest, Ray3fParameterizationOutOfBounds) {
  liang::Point3f origin = liang::Point3f(1.0, 2.0, 3.0);
  liang::Vector3f direction = liang::Vector3f(0.1, 0.2, 0.3);
  liang::Ray3f ray = liang::Ray3f(origin, direction, 5.0);
  ASSERT_DEATH(ray(-1.0), ASSERTION_FAILURE);
  ASSERT_DEATH(liang::Ray3f(origin, direction, -5.0), ASSERTION_FAILURE);
}

TEST(GeometryTest, AABB3Creation) {
  liang::AABB3f box = liang::AABB3f(liang::Point3f(1.0, 2.0, 3.0));
  AABB3FloatEquals(box, 1.0, 2.0, 3.0, 1.0, 2.0, 3.0);
  box = liang::AABB3f(liang::Point3f(1.0, 2.0, 3.0), liang::Point3f(0.5, 1.2, 3.3));
  AABB3FloatEquals(box, 0.5, 1.2, 3.0, 1.0, 2.0, 3.3);
  box = liang::AABB3f(liang::Point3f(1.1, 1.2, 1.3), liang::Point3f(0.1, 0.2, 0.3));
  AABB3FloatEquals(box, 0.1, 0.2, 0.3, 1.1, 1.2, 1.3);
  box = liang::AABB3f(liang::Point3f(0.1, 0.2, 0.3), liang::Point3f(1.1, 1.2, 1.3));
  AABB3FloatEquals(box, 0.1, 0.2, 0.3, 1.1, 1.2, 1.3);
}

TEST(GeometryTest, AABB3Corner) {
  liang::AABB3f box = liang::AABB3f(liang::Point3f(1.0, 1.0, 1.0), liang::Point3f(2.0, 2.0, 2.0));
  Point3FloatEquals(box.Corner(0), 1.0, 1.0, 1.0);
  Point3FloatEquals(box.Corner(1), 1.0, 1.0, 2.0);
  Point3FloatEquals(box.Corner(2), 1.0, 2.0, 1.0);
  Point3FloatEquals(box.Corner(3), 1.0, 2.0, 2.0);
  Point3FloatEquals(box.Corner(4), 2.0, 1.0, 1.0);
  Point3FloatEquals(box.Corner(5), 2.0, 1.0, 2.0);
  Point3FloatEquals(box.Corner(6), 2.0, 2.0, 1.0);
  Point3FloatEquals(box.Corner(7), 2.0, 2.0, 2.0);
}

TEST(GeometryTest, AABB3CornerOutOfBounds) {
  liang::AABB3f box = liang::AABB3f(liang::Point3f(1.0, 2.0, 1.0), liang::Point3f(2.0, 1.0, 2.0));
  ASSERT_DEATH(box.Corner(8), ASSERTION_FAILURE);
}

TEST(GeometryTest, AABB3IsEmpty) {
  liang::AABB3f box = liang::AABB3f(liang::Point3f(1.0, 1.0, 1.0));
  ASSERT_FALSE(box.IsEmpty());
  box.max_point = liang::Point3f(0.0, 0.0, 0.0);
  ASSERT_TRUE(box.IsEmpty());
}

TEST(GeometryTest, AABB3Expand) {
  liang::AABB3f box = liang::AABB3f(liang::Point3f(1.0, 1.0, 1.0), liang::Point3f(2.0, 2.0, 2.0));
  box.Expand(0.5);
  AABB3FloatEquals(box, 0.5, 0.5, 0.5, 2.5, 2.5, 2.5);
}

TEST(GeometryTest, AABB3Diagonal) {
  liang::AABB3f box = liang::AABB3f(liang::Point3f(1.0, 1.0, 1.0), liang::Point3f(2.0, 2.0, 2.0));
  Vector3FloatEquals(box.Diagonal(), 1.0, 1.0, 1.0);
  box.max_point = liang::Point3f();
  Vector3FloatEquals(box.Diagonal(), 0.0, 0.0, 0.0);
}

TEST(GeometryTest, AABB3SurfaceArea) {
  liang::AABB3f box = liang::AABB3f(liang::Point3f(1.0, 1.0, 1.0), liang::Point3f(3.0, 4.0, 5.0));
  ASSERT_FLOAT_EQ(52.0, box.SurfaceArea());
  box.max_point = liang::Point3f();
  ASSERT_FLOAT_EQ(0.0, box.SurfaceArea());
}

TEST(GeometryTest, AABB3Volume) {
  liang::AABB3f box = liang::AABB3f(liang::Point3f(1.0, 1.0, 1.0), liang::Point3f(3.0, 4.0, 5.0));
  ASSERT_FLOAT_EQ(24.0, box.Volume());
  box.max_point = liang::Point3f();
  ASSERT_FLOAT_EQ(0.0, box.Volume());
}

TEST(GeometryTest, AABB3Union) {
  // Partial intersection.
  liang::AABB3f b1 = liang::AABB3f(liang::Point3f(2.0, 2.0, 2.0), liang::Point3f(8.0, 8.0, 8.0));
  liang::AABB3f b2 = liang::AABB3f(liang::Point3f(0.0, 3.0, 0.0), liang::Point3f(3.0, 9.0, 5.0));
  AABB3FloatEquals(liang::Union(b1, b2), 0.0, 2.0, 0.0, 8.0, 9.0, 8.0);
  // Full intersection.
  b1 = liang::AABB3f(liang::Point3f(2.0, 2.0, 2.0), liang::Point3f(8.0, 8.0, 8.0));
  b2 = liang::AABB3f(liang::Point3f(3.0, 3.0, 3.0), liang::Point3f(7.0, 7.0, 7.0));
  AABB3FloatEquals(liang::Union(b1, b2), 2.0, 2.0, 2.0, 8.0, 8.0, 8.0);
  // The second bounding box is invalid.
  b2.max_point = liang::Point3f(0.0, 0.0, 0.0);
  AABB3FloatEquals(liang::Union(b1, b2), b1.min_point.x, b1.min_point.y, b1.min_point.z,
      b1.max_point.x, b1.max_point.y, b1.max_point.z);
  // Disjoint.
  b1 = liang::AABB3f(liang::Point3f(2.0, 2.0, 2.0), liang::Point3f(8.0, 8.0, 8.0));
  b2 = liang::AABB3f(liang::Point3f(0.0, 0.0, 0.0), liang::Point3f(1.0, 1.0, 1.0));
  AABB3FloatEquals(liang::Union(b1, b2), 0.0, 0.0, 0.0, 8.0, 8.0, 8.0);
  // The first bounding box is invalid.
  b1.max_point = liang::Point3f(0.0, 0.0, 0.0);
  AABB3FloatEquals(liang::Union(b1, b2), b2.min_point.x, b2.min_point.y, b2.min_point.z,
      b2.max_point.x, b2.max_point.y, b2.max_point.z);
}

TEST(GeometryTest, AABB3Intersect) {
  // Partial intersection.
  liang::AABB3f b1 = liang::AABB3f(liang::Point3f(2.0, 2.0, 2.0), liang::Point3f(8.0, 8.0, 8.0));
  liang::AABB3f b2 = liang::AABB3f(liang::Point3f(0.0, 3.0, 0.0), liang::Point3f(3.0, 9.0, 5.0));
  AABB3FloatEquals(liang::Intersect(b1, b2), 2.0, 3.0, 2.0, 3.0, 8.0, 5.0);
  // Full intersection.
  b1 = liang::AABB3f(liang::Point3f(2.0, 2.0, 2.0), liang::Point3f(8.0, 8.0, 8.0));
  b2 = liang::AABB3f(liang::Point3f(3.0, 3.0, 3.0), liang::Point3f(7.0, 7.0, 7.0));
  AABB3FloatEquals(liang::Intersect(b1, b2), 3.0, 3.0, 3.0, 7.0, 7.0, 7.0);
  // The second bounding box is invalid.
  b2.max_point = liang::Point3f(0.0, 0.0, 0.0);
  ASSERT_TRUE(liang::Intersect(b1, b2).IsEmpty());
  // Disjoint.
  b1 = liang::AABB3f(liang::Point3f(2.0, 2.0, 2.0), liang::Point3f(8.0, 8.0, 8.0));
  b2 = liang::AABB3f(liang::Point3f(0.0, 0.0, 0.0), liang::Point3f(1.0, 1.0, 1.0));
  ASSERT_TRUE(liang::Intersect(b1, b2).IsEmpty());
  // The first bounding box is invalid.
  b1.max_point = liang::Point3f(0.0, 0.0, 0.0);
  ASSERT_TRUE(liang::Intersect(b1, b2).IsEmpty());
}

TEST(GeometryTest, AABB3Overlaps) {
  // Partial intersection.
  liang::AABB3f b1 = liang::AABB3f(liang::Point3f(2.0, 2.0, 2.0), liang::Point3f(8.0, 8.0, 8.0));
  liang::AABB3f b2 = liang::AABB3f(liang::Point3f(0.0, 3.0, 0.0), liang::Point3f(3.0, 9.0, 5.0));
  ASSERT_TRUE(liang::Overlaps(b1, b2));
  // Full intersection.
  b1 = liang::AABB3f(liang::Point3f(2.0, 2.0, 2.0), liang::Point3f(8.0, 8.0, 8.0));
  b2 = liang::AABB3f(liang::Point3f(3.0, 3.0, 3.0), liang::Point3f(7.0, 7.0, 7.0));
  ASSERT_TRUE(liang::Overlaps(b1, b2));
  // The second bounding box is invalid.
  b2.max_point = liang::Point3f(0.0, 0.0, 0.0);
  ASSERT_FALSE(liang::Overlaps(b1, b2));
  // Disjoint.
  b1 = liang::AABB3f(liang::Point3f(2.0, 2.0, 2.0), liang::Point3f(8.0, 8.0, 8.0));
  b2 = liang::AABB3f(liang::Point3f(0.0, 0.0, 0.0), liang::Point3f(1.0, 1.0, 1.0));
  ASSERT_FALSE(liang::Overlaps(b1, b2));
  // The first bounding box is invalid.
  b1.max_point = liang::Point3f(0.0, 0.0, 0.0);
  ASSERT_FALSE(liang::Overlaps(b1, b2));
}

TEST(GeometryTest, AABB3Contains) {
  liang::AABB3f box = liang::AABB3f(liang::Point3f(2.0, 2.0, 2.0), liang::Point3f(8.0, 8.0, 8.0));
  ASSERT_TRUE(liang::Contains(box, liang::Point3f(3.0, 3.0, 3.0)));
  ASSERT_FALSE(liang::Contains(box, liang::Point3f(3.0, 10.0, 3.0)));
  ASSERT_TRUE(liang::Contains(box, liang::Point3f(2.0, 2.0, 2.0)));
  // Invalid AABB3.
  box.max_point = liang::Point3f(0.0, 0.0, 0.0);
  ASSERT_FALSE(liang::Contains(box, liang::Point3f(0.0, 0.0, 0.0)));
  ASSERT_FALSE(liang::Contains(box, liang::Point3f(1.0, 1.0, 1.0)));
  ASSERT_FALSE(liang::Contains(box, liang::Point3f(2.0, 2.0, 2.0)));
}
