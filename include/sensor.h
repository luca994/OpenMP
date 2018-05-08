#ifndef SENSOR_H_
#define SENSOR_H_
#include "objectwithsensor.h"
#include "position.h"


class Sensor {
public:
  ObjectWithSensor getObject();
  void setPosition(Position pos);
  Position getPosition();
private:
  int sid;
  Position position;
  ObjectWithSensor object;
};
#endif
