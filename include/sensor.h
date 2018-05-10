#ifndef SENSOR_H_
#define SENSOR_H_
#include "objectwithsensor.h"
#include "position.h"
#include <memory>


class Sensor {
public:
  Sensor();
  Sensor(int sid,std::shared_ptr<ObjectWithSensor> obj);
  Sensor(int sid,std::shared_ptr<ObjectWithSensor> obj,unsigned int hertzFrequency);
  void setObject(std::shared_ptr<ObjectWithSensor> obj);
  std::shared_ptr<ObjectWithSensor> getObject();
  void setPosition(Position pos);
  void setFrequency(unsigned int hertzFrequency);
  unsigned long int getPeriod();
  int getSid();
  Position getPosition();
private:
  int sid;
  Position position;
  std::shared_ptr<ObjectWithSensor> object;
  /*the period of the sensor expressed in picoseconds*/
  unsigned long int period;
};
#endif
