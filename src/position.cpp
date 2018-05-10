#include "math.h"
#include "position.h"
#include <limits>

Position::Position():x(0),y(0),z(0),valid(false){}

Position::Position(double x,double y,double z)
{
  this->x=x,
  this->y=y;
  this->z=z;
  valid=true;
}

double Position::compute2DDistance(Position p)
{
    if(valid && p.isValid())
      return sqrt((pow((p.getX()-x),2)+ pow((p.getY()-y),2)));
    else
      return std::numeric_limits<double>::infinity();
}

double Position::compute3DDistance(Position p)
{
    if(valid && p.isValid())
      return sqrt((pow((p.getX()-x),2)+pow((p.getY()-y),2))+pow((p.getZ()-z),2));
    else
      return std::numeric_limits<double>::infinity();
}

bool Position::isValid()
{
  return valid;
}

double Position::getX()
{
  return x;
}

double Position::getY()
{
  return y;
}

double Position::getZ()
{
  return z;
}

void Position::setValidity(bool v)
{
  valid=v;
}

void Position::setX(double x)
{
  this->x=x;
}

void Position::setY(double y)
{
  this->y=y;
}

void Position::setZ(double z)
{
  this->z=z;
}
