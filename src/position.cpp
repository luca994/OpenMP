#include "math.h"

int Position::compute2DDistance(Position p){
  if(x==NULL || y==NULL || z==NULL || p.getX()==NULL || P.getY()==NULL || p.getZ()==NULL)
    return NULL;
  else
    return sqrt((pow(p.getX()-x),2)+(pow(p.getY()-y),2));
}

int Position::compute3DDistance(Position p){
  if(x==NULL || y==NULL || z==NULL || p.getX()==NULL || P.getY()==NULL || p.getZ()==NULL)
    return NULL;
  else
    return sqrt((pow(p.getX()-x),2)+(pow(p.getY()-y),2)+(pow(p.getZ()-z),2));
}

int Position::getX(){
  return x;
}
int Position::getY(){
  return y;
}
int Position::getZ(){
  return z;
}

void Postion::setX(int x){
  this->x=x;
}
void Postion::setY(int y){
  this->y=y;
}
void Postion::setZ(int z){
  this->z=z;
}
