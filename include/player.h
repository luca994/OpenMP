#ifndef PLAYER_H_
#define PLAYER_H_
#include <string.h>
#include "objectwithsensor.h"

class Player: public ObjectWithSensor{
public:
  Player();
  Player(std::string name,std::string team,bool playing);
  bool operator < (const Player &other);
  std::string getType() const;
  std::string getName();
  std::string getTeam();
private:
  std::string fullName;
  std::string team;
  bool playing;
};
#endif
