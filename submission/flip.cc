#include "flip.h"
#include "ppm.h"
#include <vector>
#include <utility>

FlippedImage::FlippedImage(Image *image): Decorator{image} {}

// reverseRow(ppm, row): reverses the rowth row of ppm
// Requires: row >= 0
// Effects: mutates ppm
static void reverseRow(PPM &ppm, int row) {
  int start = row * ppm.getWidth();
  int len = start + ppm.getWidth();
#ifdef DEBUG
  std::cerr << "inside:" << std::endl;
    for(int j = start; j < len; ++j) {
      std::cout << "(" << ppm.getPixels().at(j).r << ",";
      std::cout << ppm.getPixels().at(j).g << ",";
      std::cout << ppm.getPixels().at(j).b << "), ";
    }
    std::cout << std::endl;
#endif
  for(int i = 0; i < ppm.getWidth() / 2; ++i) {
    std::swap(ppm.getPixels().at(start + i), ppm.getPixels().at(len - i - 1));
  }
#ifdef DEBUG
  std::cerr << "transformed:" << std::endl;
    for(int j = start; j < len; ++j) {
      std::cout << "(" << ppm.getPixels().at(j).r << ",";
      std::cout << ppm.getPixels().at(j).g << ",";
      std::cout << ppm.getPixels().at(j).b << "), ";
    }
    std::cout << std::endl;
#endif
}

void FlippedImage::render(PPM &ppm) {
  image->render(ppm);
  for(int row = 0; row < ppm.getHeight(); ++row) {
    reverseRow(ppm, row);
  }
}
