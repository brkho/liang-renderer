// This header defines the Mesh class which is made up of triangles defined by vertices and element
// indices.
//
// Author: brian@brkho.com

#ifndef LIANG_SHAPES_MESH_H
#define LIANG_SHAPES_MESH_H

#include "core/geometry.h"
#include "core/liang.h"
#include "core/transform.h"
#include "shapes/shape.h"

namespace liang {

// Abstraction that describes a vertex for use in a Mesh.
struct TriangleVertex {
  // Location of the vertex.
  Point3f position;
  // Normal of the vertex.
  Normal3f normal;
};

class Mesh : Shape {
  public:
    // Mesh constructor that takes the transform from world space to object space and vice versa,
    // a shared pointer to a vector of vertices, and a shared pointer to a vector of elements.
    Mesh(uint num_vertices, const std::shared_ptr<TriangleVertex> vertices, uint num_elements,
        const std::shared_ptr<uint> elements, const Transform *object_to_world,
        const Transform *world_to_object);

    // The bounds of the mesh in object space.
    AABB3f ObjectBounds() const;

    // The bounds of the mesh in world space.
    AABB3f WorldBounds() const;

    // Intersects the mesh with a ray and returns true if there is an intersection.
    bool Intersect(Ray3f ray) const;

  private:
    // Number of vertices.
    const uint num_vertices;
    // Pointer to a array of vertices.
    const std::shared_ptr<TriangleVertex> vertices;
    // Number of elements (should be divisible by 3).
    const uint num_elements;
    // Pointer to a array of elements.
    const std::shared_ptr<uint> elements;
};

}

#endif  // LIANG_SHAPES_MESH_H
