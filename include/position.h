#ifndef POSITION_H_
#define POSITION_H_

class Position{
public:
  Position();
  Position(double x, double y, double z);
  double getX();
  double getY();
  double getZ();
  void setX(double x);
  void setY(double y);
  void setZ(double z);
  void setValidity(bool v);
  double compute2DDistance(Position p);
  double compute3DDistance(Position p);
  bool isValid();
private:
  bool valid;
  double x;
  double y;
  double z;
};
#endif
