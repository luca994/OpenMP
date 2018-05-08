#ifndef BALL_H_
#define BALL_H_
#include "objectwithsensor.h"
#include <string>

class Ball: public ObjectWithSensor{
public:
  std::string getType();
};
#endif
