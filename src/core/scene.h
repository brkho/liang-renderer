// This header defines the Scene. This is used directly with an Integrator in the main rendering
// loop to generate a Film. A Scene contains a single Primitive, most likely some type of
// AggregatePrimitive.
//
// Author: brian@brkho.com

#ifndef LIANG_CORE_SCENE_H
#define LIANG_CORE_SCENE_H

#include "core/geometry.h"
#include "core/liang.h"
#include "primitives/primitive.h"

namespace liang {

class Scene {
  public:
    // Constuctor initializing the Scene with a single primitive.
    Scene(std::shared_ptr<Primitive> primitive);

    // Gets the world space bounding box of the geometric data contained by the scene's primitive.
    AABB3f WorldBounds() const;

    // Intersects a ray with the scene and return true if there is an intersection.
    bool Intersect(Ray3f ray) const;

  private:
    // TODO(brkho): Add some lights.
    // The primitives the AggregatePrimitive contains.
    std::shared_ptr<Primitive> primitive;

};

}

#endif  // LIANG_CORE_SCENE_H
