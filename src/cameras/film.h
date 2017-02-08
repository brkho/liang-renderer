// This header defines the Film, an analogy to the imaging sensor in a real camera. The film
// accumulates information about light hitting the sensor which can then be used in turn to output
// an image to disk.
//
// Author: brian@brkho.com

#ifndef LIANG_CAMERAS_FILM_H
#define LIANG_CAMERAS_FILM_H

#include "core/geometry.h"
#include "core/liang.h"
#include "core/transform.h"
#include "filters/filter.h"

namespace liang {

// A pixel on the Film. This accumulates samples and their weights.
struct Pixel {
    // TODO(brkho): Change these to XYZ color space.
    // The red component of the pixel.
    float r;
    // The green component of the pixel.
    float g;
    // The blue component of the pixel.
    float b;
    // The sum of all of the weights of the samples so far.
    float weight_sum;
};

class Film {
  public:
    // Width of the film.
    uint width;
    // Height of the film.
    uint height;

    // Film constructor that takes a width in pixels, a height in pixels, and a reconstruction
    // filter.
    Film(uint width, uint height, std::unique_ptr<Filter> filter);

    // Gets the pixel at the given coordinates where (0, 0) is the top left corner. This is mainy
    // exposed for testing because I'm using stb_image to write to files. A more elegant solution
    // would be to give the SaveAs* family of functions a stream instead of a filename, so then I
    // can just inspect the stream during unit tests. Oh well, I guess I'll do that if I ever get
    // around to writing my own image loading/saving module.
    Pixel GetPixel(uint x, uint y) const;

    // Clears the film back to its original state.
    void ClearFilm();

    // Adds a sample's contribution to a given pixel (supplied in continuous coordinates).
    // TODO(brkho): Abstract over RGB with a class/struct.
    void AddSample(float x, float y, float r, float g, float b, float weight);

    // Saves the image as a .png after performing tone mapping from HDR to LDR.
    void SaveAsPng(std::string name) const;

    // Saves the image in high dynamic range as a .exr.
    // void SaveAsExr(std::string name);

  protected:
    // Unique pointer to the reconstruction filter function.
    std::unique_ptr<Filter> filter;
    // Unique pointer to the array of Pixel data.
    std::unique_ptr<Pixel[]> pixels;
};

}

#endif  // LIANG_CAMERAS_FILM_H
