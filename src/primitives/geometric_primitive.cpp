#include "primitives/geometric_primitive.h"

namespace liang {

GeometricPrimitive::GeometricPrimitive(std::shared_ptr<Shape> shape) : shape{shape} {}

AABB3f GeometricPrimitive::WorldBounds() const {
  return shape->WorldBounds();
}

bool GeometricPrimitive::Intersect(Ray3f ray) const {
  return shape->Intersect(ray);
}

std::vector<std::shared_ptr<GeometricPrimitive>> CreateGeometricPrimitives(
    std::vector<std::shared_ptr<Triangle>> triangles) {
  std::vector<std::shared_ptr<GeometricPrimitive>> prims;
  for (std::shared_ptr<Triangle> triangle : triangles) {
    prims.push_back(std::make_shared<GeometricPrimitive>(triangle));
  }
  return prims;
}

}
