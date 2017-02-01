// This header defines the Shape interface which abstracts a few common functions of shapes to be
// implemented in Mesh and friends.
//
// Author: brian@brkho.com

#ifndef LIANG_SHAPES_SHAPE_H
#define LIANG_SHAPES_SHAPE_H

#include "core/geometry.h"
#include "core/liang.h"
#include "core/transform.h"

namespace liang {

class Shape {
  public:
    // Shape constructor that takes the transform from world space to object space and vice versa.
    Shape(const Transform *object_to_world, const Transform *world_to_object);

    // // The bounds of the object in object space.
    // virtual AABB3f ObjectBounds() const = 0;

    // // The bounds of the object in world space.
    // virtual AABB3f WorldBounds() const = 0;

    // // Intersects the shape with a ray and returns true if there is an intersection.
    // virtual bool Intersect(Ray3f ray) const = 0;

  private:
    // The transform to get from object coordinates to world coordinates.
    const Transform *object_to_world;
    // The transform to get from world coordinates to object coordinates. This should be the
    // inverse of object_to_world, but we precompute it for performance.
    const Transform *world_to_object;
    // Whether the world-object transforms swap the handedness of the coordinate space.
    const bool swaps_handedness;
};

}

#endif  // LIANG_SHAPES_SHAPE_H
