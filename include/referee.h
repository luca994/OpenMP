#ifndef REFEREE_H_
#define REFEREE_H_
#include "objectwithsensor.h"
#include <string>

class Referee: public ObjectWithSensor{
public:
  std::string getType() const;
};
#endif
