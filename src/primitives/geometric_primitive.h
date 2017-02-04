// This header defines the GeometricPrimitive, a Primitive that contains geometric data about a
// single shape.
//
// Author: brian@brkho.com

#ifndef LIANG_PRIMITIVES_GEOMETRIC_PRIMITIVE_H
#define LIANG_PRIMITIVES_GEOMETRIC_PRIMITIVE_H

#include "core/geometry.h"
#include "core/liang.h"
#include "primitives/primitive.h"
#include "shapes/mesh.h"
#include "shapes/shape.h"

namespace liang {

class GeometricPrimitive : public Primitive {
  public:
    // Constuctor initializing the GeometricPrimitive with a pointer to the shape it contains.
    GeometricPrimitive(std::shared_ptr<Shape> shape);

    // Gets the world space bounding box of the geometric data contained inside the primitive.
    AABB3f WorldBounds() const;

    // Intersects a ray with the primitive and return true if there is an intersection.
    bool Intersect(Ray3f ray) const;

  private:
    std::shared_ptr<Shape> shape;
    // TODO(brkho): Add Material support.
};

// Creates and returns a vector of GeometricPrimitive pointers created from a vector of Triangle
// pointers.
std::vector<std::shared_ptr<GeometricPrimitive>> CreateGeometricPrimitives(
    std::vector<std::shared_ptr<Triangle>> triangles);
  
}

#endif  // LIANG_PRIMITIVES_GEOMETRIC_PRIMITIVE_H
