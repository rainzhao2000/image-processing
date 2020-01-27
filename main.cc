#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include "trilinear.h"

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

int main(int argc, char *argv[]) {
  std::string lut{argv[1]};
  std::string in{argv[2]};
  std::string out{argv[3]};
  std::fstream lutfs{lut, std::fstream::in};
  std::fstream infs{in, std::fstream::in};
  std::fstream outfs{out, std::fstream::out};

  // queue up the lut
  std::vector<double> rimage{};
  std::vector<double> gimage{};
  std::vector<double> bimage{};
  read(lutfs, rimage, gimage, bimage);
  std::cerr << "# elements: r=" << rimage.size() << ", g=" << gimage.size() << ", b=" << bimage.size() << std::endl;
  int length = rimage.size();

  // read mapping
  std::map<double, double> rmap{};
  std::map<double, double> gmap{};
  std::map<double, double> bmap{};
  for(int i = 0; i < length; ++i) {
    double key = (i + 1.0) / length;
    rmap.emplace(key, rimage.at(i));
    gmap.emplace(key, gimage.at(i));
    bmap.emplace(key, bimage.at(i));
  }

  // read data points
  std::vector<Vec3> input{};
  read(infs, input);

  // transform data
  for(Vec3 vec : input) {
    Vec3 image = function(rmap, gmap, bmap, vec);
    outfs << image.getX() << " " << image.getY() << " " << image.getZ() << std::endl;
  }
  return 0;
}
