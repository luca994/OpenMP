#include "sensor.h"
#include <iostream>

/**
*
*Default constructor of the Sensor class.
*Initializes the sensor id and the period to 0, the object to NULL
*and the position as not valid.
*
*/
Sensor::Sensor(){
  sid=0;
  object=NULL;
  period=0;
  position=Position();
}

/**
*
*Constructor of the Sensor class.
*Takes a sensor id and an ObjectWithSensor object (the object to which the sensor belongs, player, ball or referee) as input.
*Addes the sensor id to the object, assigns an invalid position and if the object is a ball set the frequency to 2000Hz
*
*/
Sensor::Sensor(int sid,std::shared_ptr<ObjectWithSensor> obj){
  object=obj;
  this->sid=sid;
  obj->addSensor(sid);
  position=Position();
  if(!obj->getType().compare("Ball"))
    period=500000000;
}

/**
*
*Constructor of the Sensor class.
*Takes a sensor id and an ObjectWithSensor object (the object to which the sensor belongs, player, ball or referee) 
*and the frequency of the sensor (in Hertz) as input.
*Addes the sensor id to the object, assigns an invalid position.
*
*/
Sensor::Sensor(int sid,std::shared_ptr<ObjectWithSensor> obj,unsigned int hertzFrequency){
  object=obj;
  obj->addSensor(sid);
  position=Position();
  this->setFrequency(hertzFrequency);
}

/**
*
*Returns the object to which the sensor belongs
*
*/
std::shared_ptr<ObjectWithSensor> Sensor::getObject(){
  return object;
}

/**
*
*Sets the object to which the sensor belongs.
*If the object is a ball and the frequency of the sensor is set to 0,
*sets the frequency to 2000Hz
*
*/
void Sensor::setObject(std::shared_ptr<ObjectWithSensor> obj){
  object=obj;
  if(!obj->getType().compare("Ball") && period==0)
    period=500000000;
}

/**
*
*Sets the position of the sensor
*
*/
void Sensor::setPosition(Position pos){
  position=pos;
}

/**
*
*Returns the position of th sensor
*
*/
Position Sensor::getPosition(){
  return position;
}

/**
*
*Returns the sensor id
*
*/
int Sensor::getSid(){
  return sid;
}

/**
*
*Set the frequency of the sensor to the value taken as input (in Hertz)
*
*/
void Sensor::setFrequency(unsigned int hertzFrequency){
  period=(1/hertzFrequency)*1000000000000;
}

/**
*
*Returns the frequency of the sensor as a period in picoseconds
*
*/
unsigned long int Sensor::getPeriod(){
  return period;
}
