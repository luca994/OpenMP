#ifndef PLAYER_H_
#define PLAYER_H_
#include <string.h>
#include "objectWithSensor.h"

class Player: public ObjectWithSensor{
public:
  std::string getType();
  std::string getName();
  std::string getTeam();
private:
  std::string fullName;
  std::string team;
};
#endif
