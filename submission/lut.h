#ifndef _LUT_H_
#define _LUT_H_
#include "image.h"
#include "decorator.h"
#include "ppm.h"

class LutImage final: public Decorator {
  public:
    LutImage(Image *image);
    void render(PPM &ppm) override;
};

#endif
