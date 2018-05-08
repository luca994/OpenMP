#include "player.h"

std::string Player::getType(){
  return "Player";
}

std::string Player::getName(){
  return fullName;
}

std::string Player::getTeam(){
  return team;
}
