#include <iostream>
#include "trilinear.h"

struct Bound {
  double x0, x1, y0, y1, z0, z1;
};

// sets the codomain lattice corresponding to the
// nearest neighbours of (in) in domain
// Requires: xmap, ymap, zmap have more than 2 elements
Bound nearest(
    const std::map<double, double> &xmap,
    const std::map<double, double> &ymap,
    const std::map<double, double> &zmap,
    const Vec3 &in,
    Vec3 &c000, Vec3 &c001, Vec3 &c010, Vec3 &c011,
    Vec3 &c100, Vec3 &c101, Vec3 &c110, Vec3 &c111) {
  // find nearest x0, x1
  double x0 = xmap.lower_bound(in.getX())->first;
  double up = xmap.upper_bound(in.getX())->first;
  double x1 = up == xmap.end()->first ? x0 : up;
  // find nearest y0, y1
  double y0 = ymap.lower_bound(in.getY())->first;
  up = ymap.upper_bound(in.getY())->first;
  double y1 = up == xmap.end()->first ? y0 : up;
  // find nearest z0, z1
  double z0 = zmap.lower_bound(in.getZ())->first;
  up = zmap.upper_bound(in.getZ())->first;
  double z1 = up == xmap.end()->first ? z0 : up;

  // set codomain lattice
  c000 = {xmap.at(x0), ymap.at(y0), zmap.at(z0)};
  c001 = {xmap.at(x0), ymap.at(y0), zmap.at(z1)};
  c010 = {xmap.at(x0), ymap.at(y1), zmap.at(z0)};
  c011 = {xmap.at(x0), ymap.at(y1), zmap.at(z1)};
  c100 = {xmap.at(x1), ymap.at(y0), zmap.at(z0)};
  c101 = {xmap.at(x1), ymap.at(y0), zmap.at(z1)};
  c110 = {xmap.at(x1), ymap.at(y1), zmap.at(z0)};
  c111 = {xmap.at(x1), ymap.at(y1), zmap.at(z1)};

  return {x0, x1, y0, y1, z0, z0};
}

Vec3 function(
    const std::map<double, double> &xmap,
    const std::map<double, double> &ymap,
    const std::map<double, double> &zmap,
    const Vec3 &in) {
  Vec3 c000{}, c001{}, c010{}, c011{}, c100{}, c101{}, c110{}, c111{};
  Bound bound = nearest(xmap, ymap, zmap, in, c000, c001, c010, c011, c100, c101, c110, c111);
  double xmatch = in.getX() - bound.x0;
  double ymatch = in.getY() - bound.y0;
  double zmatch = in.getZ() - bound.z0;
  
  double xden = bound.x1 - bound.x0;
  double yden = bound.y1 - bound.y0;
  double zden = bound.z1 - bound.z0;

  if(!xden || !yden || !zden) {
    return {xmap.at(bound.x0), ymap.at(bound.y0), zmap.at(bound.z0)};
  }

  double dx = xmatch / xden;
  double dy = ymatch / yden;
  double dz = zmatch / zden;

  std::cerr << "dx: " << dx << " dy: " << dy << " dz: " << dz << std::endl;

  // interpolate along x
  Vec3 c00{c000.getX() * (1 - dx) + c100.getX() * dx, c000.getY(), c000.getZ()};
  Vec3 c01{c001.getX() * (1 - dx) + c101.getX() * dx, c001.getY(), c001.getZ()};
  Vec3 c10{c010.getX() * (1 - dx) + c110.getX() * dx, c010.getY(), c010.getZ()};
  Vec3 c11{c011.getX() * (1 - dx) + c111.getX() * dx, c011.getY(), c011.getZ()};

  // interpolate along y
  Vec3 c0{c00.getX(), c00.getY() * (1 - dy) + c10.getY() * dy, c00.getZ()};
  Vec3 c1{c01.getX(), c01.getY() * (1 - dy) + c11.getY() * dy, c01.getZ()};

  // interpolate along z
  return {c0.getX(), c0.getY(), c0.getZ() * (1 - dz) + c1.getZ() * dz};
}

double Vec3::getX() const {return this->x;}
double Vec3::getY() const {return this->y;}
double Vec3::getZ() const {return this->z;}
void Vec3::setX(double x) {this->x = x;};
void Vec3::setY(double y) {this->y = y;};
void Vec3::setZ(double z) {this->z = z;};
