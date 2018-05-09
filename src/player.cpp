#include "player.h"

Player::Player(){}

Player::Player(std::string name,std::string team,bool playing)
{
  fullName=name;
  this->team=team;
  this->playing=playing;
}

std::string Player::getType() const
{
  return "Player";
}

std::string Player::getName()
{
  return fullName;
}

std::string Player::getTeam()
{
  return team;
}

bool Player::operator <(const Player &other)
{
  if(fullName.compare(other.fullName) < 0)
    return true;
  else
    return false;
}
