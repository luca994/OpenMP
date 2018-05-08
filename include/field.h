#ifndef FIELD_H_
#define FIELD_H_
#include "position.h"

class Field{
public:
  Field(Position v1, Position v2, Position v3, Position v4);
  bool isOnField(Position pos);
private:
  Position vertex1,vertex2,vertex3,vertex4;
  bool checkRectangle();
};
#endif
