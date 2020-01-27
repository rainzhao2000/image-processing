#ifndef _SEPIA_H_
#define _SEPIA_H_
#include "image.h"
#include "decorator.h"
#include "ppm.h"

class SepiaImage final: public Decorator {
  public:
    SepiaImage(Image *image);
    void render(PPM &ppm) override;
};

#endif
