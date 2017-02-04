// The main include of the Liang Renderer testing suite. This defines constants and global includes.
//
// Author: brian@brkho.com

#include "tests/util.h"
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

void Point2IntEquals(liang::Point2i point, int x, int y) {
  ASSERT_EQ(point.x, x);
  ASSERT_EQ(point.y, y);
}

void Point2FloatEquals(liang::Point2f point, float x, float y) {
  ASSERT_FLOAT_EQ(point.x, x);
  ASSERT_FLOAT_EQ(point.y, y);
}

void Point3IntEquals(liang::Point3i point, int x, int y, int z) {
  ASSERT_EQ(point.x, x);
  ASSERT_EQ(point.y, y);
  ASSERT_EQ(point.z, z);
}

void Point3FloatEquals(liang::Point3f point, float x, float y, float z) {
  ASSERT_FLOAT_EQ(point.x, x);
  ASSERT_FLOAT_EQ(point.y, y);
  ASSERT_FLOAT_EQ(point.z, z);
}

void Normal3FloatEquals(liang::Normal3f normal, float x, float y, float z) {
  ASSERT_FLOAT_EQ(normal.x, x);
  ASSERT_FLOAT_EQ(normal.y, y);
  ASSERT_FLOAT_EQ(normal.z, z);
}

void AABB3FloatEquals(liang::AABB3f box, float min_x, float min_y, float min_z, float max_x,
    float max_y, float max_z) {
  ASSERT_FLOAT_EQ(min_x, box.min_point.x);
  ASSERT_FLOAT_EQ(min_y, box.min_point.y);
  ASSERT_FLOAT_EQ(min_z, box.min_point.z);
  ASSERT_FLOAT_EQ(max_x, box.max_point.x);
  ASSERT_FLOAT_EQ(max_y, box.max_point.y);
  ASSERT_FLOAT_EQ(max_z, box.max_point.z);
}

void AssertMatEquals(const liang::Matrix4x4 &matrix, const std::vector<float> &values) {
  for (int i = 0; i < 16; i++) {
    ASSERT_NEAR(values[i], matrix.Get(i / 4, i % 4), 0.00001);
  }
}

std::shared_ptr<liang::Mesh> CreateUnitCube(liang::Transform *object_to_world) {
  std::shared_ptr<liang::TriangleVertex> vertices(new liang::TriangleVertex[36]);
  vertices.get()[0] = {liang::Point3f(-0.5, -0.5, -0.5), liang::Normal3f(0.0, 0.0, -1.0)};
  vertices.get()[1] = {liang::Point3f(0.5, -0.5, -0.5), liang::Normal3f(0.0, 0.0, -1.0)};
  vertices.get()[2] = {liang::Point3f(0.5, 0.5, -0.5), liang::Normal3f(0.0, 0.0, -1.0)};
  vertices.get()[3] = {liang::Point3f(0.5, 0.5, -0.5), liang::Normal3f(0.0, 0.0, -1.0)};
  vertices.get()[4] = {liang::Point3f(-0.5, 0.5, -0.5), liang::Normal3f(0.0, 0.0, -1.0)};
  vertices.get()[5] = {liang::Point3f(-0.5, -0.5, -0.5), liang::Normal3f(0.0, 0.0, -1.0)};
  vertices.get()[6] = {liang::Point3f(-0.5, -0.5, 0.5), liang::Normal3f(0.0, 0.0, 1.0)};
  vertices.get()[7] = {liang::Point3f(0.5, -0.5, 0.5), liang::Normal3f(0.0, 0.0, 1.0)};
  vertices.get()[8] = {liang::Point3f(0.5, 0.5, 0.5), liang::Normal3f(0.0, 0.0, 1.0)};
  vertices.get()[9] = {liang::Point3f(0.5, 0.5, 0.5), liang::Normal3f(0.0, 0.0, 1.0)};
  vertices.get()[10] = {liang::Point3f(-0.5, 0.5, 0.5), liang::Normal3f(0.0, 0.0, 1.0)};
  vertices.get()[11] = {liang::Point3f(-0.5, -0.5, 0.5), liang::Normal3f(0.0, 0.0, 1.0)};
  vertices.get()[12] = {liang::Point3f(-0.5, 0.5, 0.5), liang::Normal3f(-1.0, 0.0, 0.0)};
  vertices.get()[13] = {liang::Point3f(-0.5, 0.5, -0.5), liang::Normal3f(-1.0, 0.0, 0.0)};
  vertices.get()[14] = {liang::Point3f(-0.5, -0.5, -0.5), liang::Normal3f(-1.0, 0.0, 0.0)};
  vertices.get()[15] = {liang::Point3f(-0.5, -0.5, -0.5), liang::Normal3f(-1.0, 0.0, 0.0)};
  vertices.get()[16] = {liang::Point3f(-0.5, -0.5, 0.5), liang::Normal3f(-1.0, 0.0, 0.0)};
  vertices.get()[17] = {liang::Point3f(-0.5, 0.5, 0.5), liang::Normal3f(-1.0, 0.0, 0.0)};
  vertices.get()[18] = {liang::Point3f(0.5, 0.5, 0.5), liang::Normal3f(1.0, 0.0, 0.0)};
  vertices.get()[19] = {liang::Point3f(0.5, 0.5, -0.5), liang::Normal3f(1.0, 0.0, 0.0)};
  vertices.get()[20] = {liang::Point3f(0.5, -0.5, -0.5), liang::Normal3f(1.0, 0.0, 0.0)};
  vertices.get()[21] = {liang::Point3f(0.5, -0.5, -0.5), liang::Normal3f(1.0, 0.0, 0.0)};
  vertices.get()[22] = {liang::Point3f(0.5, -0.5, 0.5), liang::Normal3f(1.0, 0.0, 0.0)};
  vertices.get()[23] = {liang::Point3f(0.5, 0.5, 0.5), liang::Normal3f(1.0, 0.0, 0.0)};
  vertices.get()[24] = {liang::Point3f(-0.5, -0.5, -0.5), liang::Normal3f(0.0, -1.0, 0.0)};
  vertices.get()[25] = {liang::Point3f(0.5, -0.5, -0.5), liang::Normal3f(0.0, -1.0, 0.0)};
  vertices.get()[26] = {liang::Point3f(0.5, -0.5, 0.5), liang::Normal3f(0.0, -1.0, 0.0)};
  vertices.get()[27] = {liang::Point3f(0.5, -0.5, 0.5), liang::Normal3f(0.0, -1.0, 0.0)};
  vertices.get()[28] = {liang::Point3f(-0.5, -0.5, 0.5), liang::Normal3f(0.0, -1.0, 0.0)};
  vertices.get()[29] = {liang::Point3f(-0.5, -0.5, -0.5), liang::Normal3f(0.0, -1.0, 0.0)};
  vertices.get()[30] = {liang::Point3f(-0.5, 0.5, -0.5), liang::Normal3f(0.0, 1.0, 0.0)};
  vertices.get()[31] = {liang::Point3f(0.5, 0.5, -0.5), liang::Normal3f(0.0, 1.0, 0.0)};
  vertices.get()[32] = {liang::Point3f(0.5, 0.5, 0.5), liang::Normal3f(0.0, 1.0, 0.0)};
  vertices.get()[33] = {liang::Point3f(0.5, 0.5, 0.5), liang::Normal3f(0.0, 1.0, 0.0)};
  vertices.get()[34] = {liang::Point3f(-0.5, 0.5, 0.5), liang::Normal3f(0.0, 1.0, 0.0)};
  vertices.get()[35] = {liang::Point3f(-0.5, 0.5, -0.5), liang::Normal3f(0.0, 1.0, 0.0)};

  std::shared_ptr<uint> elements(new uint[36]);
  for (uint i = 0; i < 36; i++) {
    elements.get()[i] = i;
  }
  return liang::CreateMesh(36, vertices, 36, elements, object_to_world);
}

std::shared_ptr<liang::Mesh> CreateUnitCube() {
  liang::Transform *object_to_world = new liang::Transform();
  return CreateUnitCube(object_to_world);
}
