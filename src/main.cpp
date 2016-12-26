// The main entry point of the Liang Renderer.
//
// Author: brian@brkho.com

#include "core/liang.h"
#include "core/geometry.h"

// Main point of entry for the code.
int main(int /* argc */, char* /* argv */ []) {
  liang::Vector2<int> point = liang::Vector2<int>();
  point[0] = 1;
  std::cout << point.ToString() << std::endl;
  return EXIT_SUCCESS;
}
