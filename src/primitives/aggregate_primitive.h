// This header defines the AggregatePrimitive, a Primitive that contains many other Primitives.
// While this can be used as a standalone Primitive, this is meant to be extended by acceleration
// data structures.
//
// Author: brian@brkho.com

#ifndef LIANG_PRIMITIVES_AGGREGATE_PRIMITIVE_H
#define LIANG_PRIMITIVES_AGGREGATE_PRIMITIVE_H

#include "core/geometry.h"
#include "core/liang.h"
#include "primitives/primitive.h"
#include "shapes/mesh.h"
#include "shapes/shape.h"

namespace liang {

class AggregatePrimitive : public Primitive {
  public:
    // Constuctor initializing the AggregatePrimitive with a vector of pointers to other Primitives.
    // The contained primitives can be GeometricPrimitives or other AggregatePrimitives.
    AggregatePrimitive(std::vector<std::shared_ptr<Primitive>> primitives);

    // Gets the world space bounding box of the geometric data contained inside all of the
    // primitives the AggregatePrimitive contains.
    AABB3f WorldBounds() const;

    // Intersects a ray with the primitive and return true if there is an intersection.
    bool Intersect(Ray3f ray) const;

  private:
    // The primitives the AggregatePrimitive contains.
    std::vector<std::shared_ptr<Primitive>> primitives;

    // The world space bounding box of the AggregatePrimitive that is precomputed for efficiency.
    AABB3f world_bounds;

};

}

#endif  // LIANG_PRIMITIVES_AGGREGATE_PRIMITIVE_H
