#include "shapes/mesh.h"
#include "primitives/geometric_primitive.h"
#include "tests/util.h"
#include "tests/test.h"

TEST(GeometricPrimitiveTest, Creation) {
  std::shared_ptr<liang::Mesh> mesh = CreateUnitCube();
  auto triangles = liang::CreateTriangles(mesh);
  auto prims = liang::CreateGeometricPrimitives(triangles);
  ASSERT_EQ(12u, prims.size());
}
