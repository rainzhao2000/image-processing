#ifndef _ROTATE_H_
#define _ROTATE_H_
#include "image.h"
#include "decorator.h"
#include "ppm.h"

class RotatedImage final: public Decorator {
  public:
    RotatedImage(Image *image);
    void render(PPM &ppm) override;
};

#endif
