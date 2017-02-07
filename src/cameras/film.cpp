#include "cameras/film.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

namespace liang {

Film::Film(uint width, uint height, std::unique_ptr<Filter> filter) : width{width}, height{height},
    filter{std::move(filter)}, pixels{std::unique_ptr<Pixel[]>(new Pixel[width * height])} {}

void Film::AddSample(float x, float y, float r, float g, float b, float weight) {
  assert(x >= 0.f && x <= (float)width);
  assert(y >= 0.f && y <= (float)height);
  assert(r >= 0.f && g >= 0.f && b >= 0.f);
  // TODO(brkho): Do real conversion from continuous to discrete locations here.
  int index = (int)y * width + (int)x;
  pixels.get()[index].r += r;
  pixels.get()[index].g += g;
  pixels.get()[index].b += b;
  pixels.get()[index].weight_sum += weight;
}

void Film::SaveAsPng(std::string name) {
  char *output_pixels = new char[width * height];
  for (uint i = 0; i < height; i++) {
    for (uint j = 0; j < width; j++) {
      Pixel pixel = pixels.get()[(int)i * width + (int)j];
      int base_index = (int)i * width * 3 + (int)j * 3;
      output_pixels[base_index] = (char)((pixel.r / pixel.weight_sum) * 255);
      output_pixels[base_index + 1] = (char)((pixel.g / pixel.weight_sum) * 255);
      output_pixels[base_index + 2] = (char)((pixel.b / pixel.weight_sum) * 255);
    }
  }
  int result = stbi_write_png(name.c_str(), width, height, 3, output_pixels, width * 3);
  delete output_pixels;
  assert(result != 0);
}

}
