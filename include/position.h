#ifndef POSITION_H_
#define POSITION_H_

class Position{
public:
  Position(int x, int y, int z);
  int getX();
  int getY();
  int getZ();
  void setX(int x);
  void setY(int y);
  void setZ(int z);
  int compute2DDistance(Position p);
  int compute3DDistance(Position p);
private:
  int x;
  int y;
  int z;
};
#endif
