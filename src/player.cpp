#include "player.h"

/**
*
*Default constructor of Player class
*
*/
Player::Player(){}

/**
*
*Constructor of Player class, takes as input the name of the player,
*the name of the team he belongs to and if he is playing or is on the bench
*
*/
Player::Player(std::string name,std::string team,bool playing){
  fullName=name;
  this->team=team;
  this->playing=playing;
}

/**
*
*Returns the string Player, that is the type of the sensor
*
*/
std::string Player::getType() const{
  return "Player";
}

/**
*
*Returns the name of the player
*
*/
std::string Player::getName(){
  return fullName;
}

/**
*
*Returns the name of the team that the player belongs to
*
*/
std::string Player::getTeam(){
  return team;
}

/**
*
*Returns true if the player is playing, false if he is on the bench
*
*/
bool Player::isPlaying(){
  return playing;
}

/**
*
*Sets the playing boolean to check if the player is playing
*
*/
void Player::setPlaying(bool Playing){
  this->playing=Playing;
}
