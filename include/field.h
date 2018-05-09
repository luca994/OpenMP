#ifndef FIELD_H_
#define FIELD_H_
#include "position.h"

class Field{
public:
  Field();
  Field(Position v1, Position v2, Position v3, Position v4);
  bool isOnField(Position pos);
private:
  Position v1,v2,v3,v4;
  bool checkRectangle();
};
#endif
