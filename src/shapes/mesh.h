// This header defines the Mesh class which is made up of triangles defined by vertices and element
// indices. Each Triangle implements the Shape interface and stores a pointer to the parent
// Mesh and its index in that Mesh.
//
// Author: brian@brkho.com

#ifndef LIANG_SHAPES_MESH_H
#define LIANG_SHAPES_MESH_H

#include "core/geometry.h"
#include "core/liang.h"
#include "core/transform.h"
#include "shapes/shape.h"

namespace liang {

// Forward declaration of Triangle so Mesh can actually use it.
class Triangle;

// Abstraction that describes a vertex for use in a Mesh.
struct TriangleVertex {
  // Location of the vertex.
  Point3f position;
  // Normal of the vertex.
  Normal3f normal;
};

// All the information describing a triangle mesh.
struct Mesh {
  const uint num_vertices;
  // Pointer to a array of vertices in object space.
  const std::shared_ptr<TriangleVertex> vertices;
  // Number of elements (should be divisible by 3).
  const uint num_elements;
  // Pointer to a array of elements.
  const std::shared_ptr<uint> elements;
  // Object to world transform.
  const Transform *object_to_world;
  // World to object transform.
  const Transform *world_to_object;
};

// A nice wrapper around creating a shared pointer to a Mesh that performs some error checking on
// the input.
std::shared_ptr<Mesh> CreateMesh(uint num_vertices, const std::shared_ptr<TriangleVertex> vertices,
    uint num_elements, const std::shared_ptr<uint> elements, const Transform *object_to_world,
    const Transform *world_to_object);

class Triangle : Shape {
  public:
    // Triangle constructor that takes a Mesh as a parent and its index in that mesh.
    Triangle(std::shared_ptr<Mesh> parent, uint triangle_index);

    // The bounds of the triangle in object space.
    AABB3f ObjectBounds() const;

    // The bounds of the triangle in world space.
    AABB3f WorldBounds() const;

    // Intersects the triangle with a ray and returns true if there is an intersection.
    bool Intersect(Ray3f ray) const;

  private:
    // The parent mesh that the triangle is a part of.
    const std::shared_ptr<Mesh> parent;
    // The index of the triangle into the parent mesh.
    const uint triangle_index;

    // Gets the nth vertex of the triangle (0 <= n <= 2).
    TriangleVertex GetVertex(uint n) const;
};

// Creates a vector to a list of shared pointers to a Mesh's Triangles. This actually
// constructs the Triangle instances, so multiple calls to GetTriangles will return different
// sets of Triangle instances.
std::vector<std::shared_ptr<Triangle>> GetTriangles(std::shared_ptr<Mesh> mesh);

}

#endif  // LIANG_SHAPES_MESH_H
