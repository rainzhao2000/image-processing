#include "sepia.h"
#include "ppm.h"
#include <vector>
#include <utility>

SepiaImage::SepiaImage(Image *image): Decorator{image} {}

void SepiaImage::render(PPM &ppm) {
  image->render(ppm);
  for(auto p = ppm.getPixels().begin(); p != ppm.getPixels().end(); ++p) {
    Pixel np{};
    np.r = p->r *.393 + p->g * .769 + p->b * .189;
    np.g = p->r *.349 + p->g * .686 + p->b * .168;
    np.b = p->r *.272 + p->g * .534 + p->b * .131;
    p->r = np.r > colourMax ? colourMax : np.r;
    p->g = np.g > colourMax ? colourMax : np.g;
    p->b = np.b > colourMax ? colourMax : np.b;
  }
}
