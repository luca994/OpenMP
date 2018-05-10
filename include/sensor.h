#ifndef SENSOR_H_
#define SENSOR_H_
#include "objectwithsensor.h"
#include "position.h"
#include <memory>


class Sensor {
public:
  Sensor();
  Sensor(int sid,std::shared_ptr<ObjectWithSensor> obj);
  void setObject(std::shared_ptr<ObjectWithSensor> obj);
  std::shared_ptr<ObjectWithSensor> getObject();
  void setPosition(Position pos);
  int getSid();
  Position getPosition();
private:
  int sid;
  Position position;
  std::shared_ptr<ObjectWithSensor> object;
};
#endif
