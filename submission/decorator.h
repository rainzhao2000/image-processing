#ifndef _DECORATOR_H_
#define _DECORATOR_H_
#include "image.h"

class Decorator: public Image {
  protected:
    Image *image;
  public:
    Decorator(Image *image);
    virtual ~Decorator();
};

#endif
