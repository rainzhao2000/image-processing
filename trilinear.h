// trilinear.h provides tools for trilinear interpolation for 3D LUTs
#include <map>

class Vec3 {
  double x, y, z;
  public:
    Vec3(double x = 0, double y = 0, double z = 0): x{x}, y{y}, z{z} {}
    double getX() const;
    double getY() const;
    double getZ() const;
    void setX(double x);
    void setY(double y);
    void setZ(double z);
};

Vec3 function(
    const std::map<double, double> &xmap,
    const std::map<double, double> &ymap,
    const std::map<double, double> &zmap,
    const Vec3 &in);
