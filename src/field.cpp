#include "field.h"
#include <stdexcept>

Field::Field(){}

Field::Field(Position v1, Position v2, Position v3, Position v4): v1(v1),v2(v2),v3(v3),v4(v4)
{
  this->v1=v1;
  this->v2=v2;
  this->v1=v1;
  this->v1=v1;
  minx=std::min(std::min(v1.getX(),v2.getX()),std::min(v3.getX(),v4.getX()));
  maxx=std::max(std::max(v1.getX(),v2.getX()),std::max(v3.getX(),v4.getX()));
  miny=std::min(std::min(v1.getY(),v2.getY()),std::min(v3.getY(),v4.getY()));
  maxy=std::max(std::max(v1.getY(),v2.getY()),std::max(v3.getY(),v4.getY()));
  if(!checkRectangle())
  {
      throw std::invalid_argument("Error in Field initialization.");
  }
}


bool Field::checkRectangle()
{
/* There must not exist two vertex with the same position*/
  if(v1.getX()==v2.getX() && v1.getY()==v2.getY())
    return false;
  if(v1.getX()==v3.getX() && v1.getY()==v3.getY())
    return false;
  if(v1.getX()==v4.getX() && v1.getY()==v4.getY())
    return false;
  if(v2.getX()==v3.getX() && v2.getY()==v3.getY())
    return false;
  if(v2.getX()==v4.getX() && v2.getY()==v4.getY())
    return false;
  if(v3.getX()==v4.getX() && v3.getY()==v4.getY())
    return false;
/* There must not exist three axis-aligned points*/
  if(v1.getX()==v2.getX() && (v1.getX()==v3.getX() || v1.getX()==v4.getX() || v2.getX()==v3.getX() || v2.getX()==v4.getX()))
    return false;
  if(v1.getX()==v3.getX() && (v1.getX()==v2.getX() || v1.getX()==v4.getX() || v3.getX()==v2.getX() || v3.getX()==v4.getX()))
    return false;
  if(v1.getX()==v4.getX() && (v1.getX()==v2.getX() || v1.getX()==v3.getX() || v4.getX()==v2.getX() || v4.getX()==v3.getX()))
    return false;
  if(v2.getX()==v3.getX() && (v2.getX()==v1.getX() || v2.getX()==v4.getX() || v3.getX()==v1.getX() || v3.getX()==v4.getX()))
    return false;
  if(v2.getX()==v4.getX() && (v2.getX()==v1.getX() || v2.getX()==v3.getX() || v4.getX()==v1.getX() || v4.getX()==v3.getX()))
    return false;
  if(v3.getX()==v4.getX() && (v3.getX()==v1.getX() || v3.getX()==v2.getX() || v4.getX()==v1.getX() || v4.getX()==v2.getX()))
    return false;
  if(v1.getY()==v2.getY() && (v1.getY()==v3.getY() || v1.getY()==v4.getY() || v2.getY()==v3.getY() || v2.getY()==v4.getY()))
    return false;
  if(v1.getY()==v3.getY() && (v1.getY()==v2.getY() || v1.getY()==v4.getY() || v3.getY()==v2.getY() || v3.getY()==v4.getY()))
    return false;
  if(v1.getY()==v4.getY() && (v1.getY()==v2.getY() || v1.getY()==v3.getY() || v4.getY()==v2.getY() || v4.getY()==v3.getY()))
    return false;
  if(v2.getY()==v3.getY() && (v2.getY()==v1.getY() || v2.getY()==v4.getY() || v3.getY()==v1.getY() || v3.getY()==v4.getY()))
    return false;
  if(v2.getY()==v4.getY() && (v2.getY()==v1.getY() || v2.getY()==v3.getY() || v4.getY()==v1.getY() || v4.getY()==v3.getY()))
    return false;
  if(v3.getY()==v4.getY() && (v3.getY()==v1.getY() || v3.getY()==v2.getY() || v4.getY()==v1.getY() || v4.getY()==v2.getY()))
    return false;
/* Two couples of points must be axis-aligned */
  if(v1.getX()==v2.getX())
    if(v3.getX()!=v4.getX() || v1.compute2DDistance(v2)!=v3.compute2DDistance(v4))
      return false;
  if(v1.getX()==v3.getX())
    if(v2.getX()!=v4.getX() || v1.compute2DDistance(v3)!=v2.compute2DDistance(v4))
      return false;
  if(v1.getX()==v4.getX())
    if(v3.getX()!=v2.getX() || v1.compute2DDistance(v4)!=v2.compute2DDistance(v3))
      return false;
  if(v2.getX()==v3.getX())
    if(v1.getX()!=v4.getX() || v2.compute2DDistance(v3)!=v1.compute2DDistance(v4))
      return false;
  if(v2.getX()==v4.getX())
    if(v1.getX()!=v3.getX() || v2.compute2DDistance(v4)!=v1.compute2DDistance(v3))
      return false;
  if(v3.getX()==v4.getX())
    if(v1.getX()!=v2.getX() || v3.compute2DDistance(v4)!=v1.compute2DDistance(v2))
      return false;
/* If we are at this point the vertices are corresponding on a rectangle axis-aligned*/
  return true;
}

double Field::getMaxX()
{
  return maxx;
}
double Field::getMinX()
{
  return minx;
}
double Field::getMaxY()
{
  return maxy;
}
double Field::getMinY()
{
  return miny;
}

bool Field::isOnField(Position p)
{
  if(p.getX()<=maxx && p.getX()>=minx && p.getY()<=maxy && p.getY()>=miny)
    return true;
  else
    return false;
}
