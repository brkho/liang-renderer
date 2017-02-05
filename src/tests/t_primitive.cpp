#include "shapes/mesh.h"
#include "primitives/aggregate_primitive.h"
#include "primitives/geometric_primitive.h"
#include "primitives/primitive.h"
#include "tests/util.h"
#include "tests/test.h"

TEST(GeometricPrimitiveTest, Creation) {
  auto prims = CreateUnitCubePrimitives();
  ASSERT_EQ(12u, prims.size());
}

TEST(AggregatePrimitiveTest, Creation) {
  std::vector<std::shared_ptr<liang::GeometricPrimitive>> geo_prims = CreateUnitCubePrimitives();
  std::vector<std::shared_ptr<liang::Primitive>> prims(geo_prims.begin(), geo_prims.end());
  liang::AggregatePrimitive aggregate(prims);
}
