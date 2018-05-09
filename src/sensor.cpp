#include "sensor.h"

Sensor::Sensor()
{
  sid=0;
  object=NULL;
}

Sensor::Sensor(int sid,std::shared_ptr<ObjectWithSensor> obj)
{
  object=obj;
  obj->getSid().push_back(sid);
}

std::shared_ptr<ObjectWithSensor> Sensor::getObject()
{
  return object;
}

void Sensor::setObject(std::shared_ptr<ObjectWithSensor> obj)
{
  object=obj;
}

void Sensor::setPosition(Position pos)
{
  position=pos;
}

Position Sensor::getPosition()
{
  return position;
}

int Sensor::getSid()
{
  return sid;
}
