#include "image.h"
#include "decorator.h"

Decorator::Decorator(Image *image): image{image} {}

Decorator::~Decorator() {
  delete image;
}
