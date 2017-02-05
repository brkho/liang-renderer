#include "core/scene.h"

namespace liang {

Scene::Scene(std::shared_ptr<Primitive> primitive) : primitive{primitive} {}

AABB3f Scene::WorldBounds() const {
  return primitive->WorldBounds();
}

bool Scene::Intersect(Ray3f ray) const {
  return primitive->Intersect(ray);
}

}
