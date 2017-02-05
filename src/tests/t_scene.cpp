#include "core/scene.h"
#include "primitives/aggregate_primitive.h"
#include "primitives/primitive.h"
#include "tests/util.h"
#include "tests/test.h"

TEST(SceneTest, Creation) {
  std::vector<std::shared_ptr<liang::GeometricPrimitive>> geo_prims = CreateUnitCubePrimitives();
  std::vector<std::shared_ptr<liang::Primitive>> prims(geo_prims.begin(), geo_prims.end());
  ASSERT_NO_THROW({liang::Scene(std::make_shared<liang::AggregatePrimitive>(prims));});
}
