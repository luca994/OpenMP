#include "field.h"
#include <iostream>

Field::Field(Position v1, Position v2, Position v3, Position v4){
    vertex1 = v1;
    vertex1 = v2;
    vertex1 = v3;
    vertex1 = v4;
    if(!checkRectangle){
      vertex1 = NULL;
      vertex1 = NULL;
      vertex1 = NULL;
      vertex1 = NULL;
      std::cout << "Error in Field initialization, maybe the vertices are not corresponding on a rectangle axis-aligned..." << std::endl;
    }
}

bool Field::checkRectangle(){
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



bool Field::isOnField(Position p){
  int minx=fmin(fmin(v1.getX(),v2.getX()),fmin(v3.getX(),v4.getX()));
  int maxx=fmax(fmax(v1.getX(),v2.getX()),fmax(v3.getX(),v4.getX()));
  int miny=fmin(fmin(v1.getY(),v2.getY()),fmin(v3.getY(),v4.getY()));
  int maxy=fmax(fmax(v1.getY(),v2.getY()),fmax(v3.getY(),v4.getY()));
  if(p.getX()<=maxx && p.getX()>=minx && p.getY()<=maxy && p.getY()>=miny)
    return true;
  else
    return false;
}
