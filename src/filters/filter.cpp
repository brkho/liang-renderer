#include "filters/filter.h"

namespace liang {

Filter::Filter(float radius) : radius{radius}, radius_inverse{1.f / radius} {}

}
