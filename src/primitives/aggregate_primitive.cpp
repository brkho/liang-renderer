#include "primitives/aggregate_primitive.h"

namespace liang {

AggregatePrimitive::AggregatePrimitive(std::vector<std::shared_ptr<Primitive>> primitives) :
    primitives{primitives}, world_bounds{AABB3f(primitives[0]->WorldBounds())} {
  for (auto primitive : primitives) {
    world_bounds = Union(world_bounds, primitive->WorldBounds());
  }
}

AABB3f AggregatePrimitive::WorldBounds() const {
  return world_bounds;
}

// This is slow. Acceleration data structures should override this function.
bool AggregatePrimitive::Intersect(Ray3f ray) const {
  for (auto primitive : primitives) {
    if (primitive->Intersect(ray)) {
      return true;
    }
  }
  return false;
}

}
