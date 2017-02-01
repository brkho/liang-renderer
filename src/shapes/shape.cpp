#include "shapes/shape.h"

namespace liang {

Shape::Shape(const Transform *object_to_world, const Transform *world_to_object) :
    object_to_world{object_to_world}, world_to_object{world_to_object},
    swaps_handedness{object_to_world->SwapsHandedness()} {}

}
