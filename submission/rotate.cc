#include "rotate.h"
#include "ppm.h"
#include <vector>
#include <utility>

RotatedImage::RotatedImage(Image *image): Decorator{image} {}

void RotatedImage::render(PPM &ppm) {
  image->render(ppm);
  std::vector<Pixel> newPixels{};
  for(int i = 0; i < ppm.getWidth(); ++i) {
    for(int j = 0; j < ppm.getHeight(); ++j) {
      newPixels.emplace_back(ppm.getPixels().at(ppm.getWidth() * (ppm.getHeight() - j - 1) + i));
    }
  }
  std::swap(ppm.getWidth(), ppm.getHeight());
  std::swap(ppm.getPixels(), newPixels);
}
