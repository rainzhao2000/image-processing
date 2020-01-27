#include "lut.h"
#include "ppm.h"
#include <vector>
#include <utility>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <math.h>
#include "trilinear.h"

LutImage::LutImage(Image *image): Decorator{image} {}

void read(
    std::fstream &fs,
    std::vector<double> &r,
    std::vector<double> &g,
    std::vector<double> &b) {
  std::string line = "";
  int i = 1;
  while(std::getline(fs, line)) {
    std::stringstream ss{line};
    double val;
    ss >> val;
    r.emplace_back(val);
    ss >> val;
    g.emplace_back(val);
    ss >> val;
    b.emplace_back(val);
    ++i;
  }
}

void read(
    std::fstream &fs,
    std::vector<Vec3> &data) {
  std::string line = "";
  int i = 1;
  while(std::getline(fs, line)) {
    std::stringstream ss{line};
    double r, g, b;
    ss >> r;
    ss >> g;
    ss >> b;
    Vec3 vec{r, g, b};
    data.emplace_back(vec);
    ++i;
  }
}

void LutImage::render(PPM &ppm) {
  //std::fstream lutfs{"../slog2sgamut_5207_pfe50.cube", std::fstream::in};
  std::fstream lutfs{"../srgb5207.cube", std::fstream::in};
  //std::fstream lutfs{"../Rec709 Kodak 2383 D60.cube", std::fstream::in};

  // queue up the lut
  std::vector<double> rimage{};
  std::vector<double> gimage{};
  std::vector<double> bimage{};
  read(lutfs, rimage, gimage, bimage);
  std::cerr << "# elements: r=" << rimage.size() << ", g=" << gimage.size() << ", b=" << bimage.size() << std::endl;
  int length = cbrt(rimage.size());
  std::cerr << "length: " << length << std::endl;

  // read mapping
  std::map<double, double> rmap{};
  std::map<double, double> gmap{};
  std::map<double, double> bmap{};
  for(int b = 0; b < length; ++b) {
    for(int g = 0; g < length; ++g) {
      for(int r = 0; r < length; ++r) {
        int i = b * length * length + g * length + r;
        rmap.emplace((r + 1.0) / length, rimage.at(i));
        gmap.emplace((g + 1.0) / length, gimage.at(i));
        bmap.emplace((b + 1.0) / length, bimage.at(i));
      }
    }
  }

  image->render(ppm);
  for(auto p = ppm.getPixels().begin(); p != ppm.getPixels().end(); ++p) {
    Pixel np{};
    Vec3 vec{static_cast<double>(p->r) / colourMax, static_cast<double>(p->g) / colourMax, static_cast<double>(p->b) / colourMax};
    Vec3 image = function(rmap, gmap, bmap, vec);
    np.r = image.getX() * colourMax;
    np.g = image.getY() * colourMax;
    np.b = image.getZ() * colourMax;
    p->r = np.r > colourMax ? colourMax : np.r;
    p->g = np.g > colourMax ? colourMax : np.g;
    p->b = np.b > colourMax ? colourMax : np.b;
  }
}
