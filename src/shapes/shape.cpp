#include "shapes/shape.h"

namespace liang {

Shape::Shape(const Transform *object_to_world) : object_to_world{object_to_world},
    swaps_handedness{object_to_world->SwapsHandedness()} {}

}
