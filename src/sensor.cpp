#include "sensor.h"
#include <iostream>

Sensor::Sensor(){
  sid=0;
  object=NULL;
  period=0;
  position=Position();
}

Sensor::Sensor(int sid,std::shared_ptr<ObjectWithSensor> obj){
  object=obj;
  this->sid=sid;
  obj->addSensor(sid);
  position=Position();
  if(!obj->getType().compare("Ball"))
    period=500000000;
}

Sensor::Sensor(int sid,std::shared_ptr<ObjectWithSensor> obj,unsigned int hertzFrequency){
  object=obj;
  obj->addSensor(sid);
  position=Position();
  this->setFrequency(hertzFrequency);
}

std::shared_ptr<ObjectWithSensor> Sensor::getObject(){
  return object;
}

void Sensor::setObject(std::shared_ptr<ObjectWithSensor> obj){
  object=obj;
  if(!obj->getType().compare("Ball") && period==0)
    period=500000000;
}

void Sensor::setPosition(Position pos){
  position=pos;
}

Position Sensor::getPosition(){
  return position;
}

int Sensor::getSid(){
  return sid;
}

void Sensor::setFrequency(unsigned int hertzFrequency){
  period=(1/hertzFrequency)*1000000000000;
}

unsigned long int Sensor::getPeriod(){
  return period;
}
