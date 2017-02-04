#include "core/geometry.h"
#include "core/transform.h"
#include "shapes/mesh.h"
#include "tests/util.h"
#include "tests/test.h"

TEST(MeshTest, CubeCreation) {
  std::shared_ptr<liang::Mesh> mesh = CreateUnitCube();
  ASSERT_EQ(36, (int)mesh->num_vertices);
  ASSERT_EQ(36, (int)mesh->num_elements);
}

TEST(TriangleTest, Creation) {
  std::shared_ptr<liang::Mesh> mesh = CreateUnitCube();
  auto triangles = liang::CreateTriangles(mesh);
  ASSERT_EQ(12, (int)triangles.size());
}

TEST(TriangleTest, Intersection) {
  liang::Transform translate = liang::TranslationTransform(liang::Vector3f(5.0, 5.0, 5.0));
  std::shared_ptr<liang::Mesh> mesh = CreateUnitCube(&translate);
  auto triangles = liang::CreateTriangles(mesh);
  liang::Ray3f ray = liang::Ray3f(liang::Point3f(5.2, 4.8, 5.2), liang::Vector3f(0.0, 0.0, -1.0));
  ASSERT_TRUE(triangles[0]->Intersect(ray));
  ray = liang::Ray3f(liang::Point3f(5.2, 4.8, 5.2), liang::Vector3f(0.2649, -0.2649, -0.9271));
  ASSERT_TRUE(triangles[0]->Intersect(ray));
  ray = liang::Ray3f(liang::Point3f(5.2, 4.8, 5.2), liang::Vector3f(0.4444, -0.4444, -0.7778));
  ASSERT_FALSE(triangles[0]->Intersect(ray));
  ray = liang::Ray3f(liang::Point3f(4.8, 5.2, 5.2), liang::Vector3f(0.0, 0.0, -1.0));
  ASSERT_FALSE(triangles[0]->Intersect(ray));
  ray = liang::Ray3f(liang::Point3f(5.2, 4.8, 5.2), liang::Vector3f(0.0, 0.0, 1.0));
  ASSERT_FALSE(triangles[0]->Intersect(ray));
}

TEST(TriangleTest, ObjectBounds) {
  liang::Transform translate = liang::TranslationTransform(liang::Vector3f(5.0, 5.0, 5.0));
  liang::Transform scale = liang::ScaleTransform(2.0, 2.0, 2.0);
  liang::Transform transform = scale * translate;
  std::shared_ptr<liang::Mesh> mesh = CreateUnitCube(&transform);
  auto triangles = liang::CreateTriangles(mesh);
  auto bounding_box = triangles[0]->ObjectBounds();
  Point3FloatEquals(bounding_box.min_point, -0.5, -0.5, -0.5);
  Point3FloatEquals(bounding_box.max_point, 0.5, 0.5, -0.5);
}

TEST(TriangleTest, WorldBounds) {
  liang::Transform translate = liang::TranslationTransform(liang::Vector3f(5.0, 5.0, 5.0));
  liang::Transform scale = liang::ScaleTransform(2.0, 2.0, 2.0);
  liang::Transform transform = scale * translate;
  std::shared_ptr<liang::Mesh> mesh = CreateUnitCube(&transform);
  auto triangles = liang::CreateTriangles(mesh);
  auto bounding_box = triangles[0]->WorldBounds();
  Point3FloatEquals(bounding_box.min_point, 9.0, 9.0, 9.0);
  Point3FloatEquals(bounding_box.max_point, 11.0, 11.0, 9.0);
}
