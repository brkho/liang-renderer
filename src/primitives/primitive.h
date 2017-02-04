// This header defines the Primitive interface. A primitive is the abstraction that bridges the
// geometric propeties of a mesh with the shading properties of a material.
//
// Author: brian@brkho.com

#ifndef LIANG_PRIMITIVES_PRIMITIVE_H
#define LIANG_PRIMITIVES_PRIMITIVE_H

#include "core/geometry.h"
#include "core/liang.h"
#include "core/transform.h"

namespace liang {

class Primitive {
  public:
    // Gets the world space bounding box of the geometric data contained inside the primitive.
    virtual AABB3f WorldBounds() const = 0;

    // Intersects a ray with the primitive and return true if there is an intersection.
    virtual bool Intersect(Ray3f ray) const = 0;
};

}

#endif  // LIANG_PRIMITIVES_PRIMITIVE_H
