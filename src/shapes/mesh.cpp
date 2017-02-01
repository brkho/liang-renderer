#include "shapes/mesh.h"

namespace liang {

Mesh::Mesh(uint num_vertices, const std::shared_ptr<TriangleVertex> vertices,
    uint num_elements, const std::shared_ptr<uint> elements, const Transform *object_to_world,
    const Transform *world_to_object) : Shape(object_to_world, world_to_object),
    num_vertices{num_vertices}, vertices{vertices}, num_elements{num_elements},
    elements{elements} {}

bool Mesh::Intersect(Ray3f ray) const {
  return true;
}

}
