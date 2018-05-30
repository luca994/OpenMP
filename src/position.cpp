#include "math.h"
#include "position.h"
#include <limits>

/**
*
*Defaults constructor of the Position class. Sets all the coordinates to 0
*and the position as not valid.
*
*/
Position::Position():x(0),y(0),z(0),valid(false){}

/**
*
*Constructor of the position class. Sets all the coordinates to the values
*taken as input. Sets the position as valid.
*
*/
Position::Position(double x,double y,double z){
  this->x=x,
  this->y=y;
  this->z=z;
  valid=true;
}

/**
*
*Computes the 2D distance between the caller and the position taken as input.
*Returns the distance.
*
*/
double Position::compute2DDistance(Position p){
    if(valid && p.isValid())
      return sqrt((pow((p.getX()-x),2)+ pow((p.getY()-y),2)));
    else
      return std::numeric_limits<double>::infinity();
}

/**
*
*Computes the 3D distance between the caller and the position taken as input.
*Returns the distance.
*
*/
double Position::compute3DDistance(Position p){
    if(valid && p.isValid())
      return sqrt((pow((p.getX()-x),2)+pow((p.getY()-y),2))+pow((p.getZ()-z),2));
    else
      return std::numeric_limits<double>::infinity();
}

/**
*
*Returns true if the position is valid, false otherwise.
*
*/
bool Position::isValid(){
  return valid;
}

/**
*
*Returns the x coordinate of the position
*
*/
double Position::getX(){
  return x;
}

/**
*
*Returns the y coordinate of the position
*
*/
double Position::getY(){
  return y;
}

/**
*
*Returns the z coordinate of the position
*
*/
double Position::getZ(){
  return z;
}

/**
*
*Sets the validity of the position to the boolean taken as input.
*
*/
void Position::setValidity(bool v){
  valid=v;
}

/**
*
*Sets the x coordinate of the position to the value taken as input.
*
*/
void Position::setX(double x){
  this->x=x;
}

/**
*
*Sets the y coordinate of the position to the value taken as input.
*
*/
void Position::setY(double y){
  this->y=y;
}

/**
*
*Sets the z coordinate of the position to the value taken as input.
*
*/
void Position::setZ(double z){
  this->z=z;
}
