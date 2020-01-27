#ifndef _FLIP_H_
#define _FLIP_H_
#include "image.h"
#include "decorator.h"
#include "ppm.h"

class FlippedImage final: public Decorator {
  public:
    FlippedImage(Image *image);
    void render(PPM &ppm) override;
};

#endif
