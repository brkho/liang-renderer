#include "core/geometry.h"
#include "core/transform.h"
#include "shapes/mesh.h"
#include "tests/util.h"
#include "tests/test.h"

// This is ugly and leaks memory. Clean this up when we have a real model loading system.
liang::Mesh CreateUnitCube() {
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

  liang::Transform *object_to_world = new liang::Transform();
  liang::Transform *world_to_object = new liang::Transform();
  return liang::Mesh(36, vertices, 36, elements, object_to_world, world_to_object);
}

TEST(MeshTest, MeshCreationTest) {
  liang::Mesh mesh = CreateUnitCube();
}
