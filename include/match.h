#ifndef MATCH_H_
#define MATCH_H_
#include "field.h"
#include "player.h"
#include "ball.h"
#include "referee.h"
#include "event.h"
#include "timeinterval.h"
#include "sensor.h"
#include <vector>
#include <list>
#include <map>
#include <string>

class Match(){
public:
  Match(Field f);
  void addPlayer(Player p);
  void addBall(Ball b);
  void addReferee(Referee r);
//  void restartMatch();
  void simulateMatch(std::vector<Event> events, std::vector<TimeInterval> intervals);
//  double getBallPossession();
private:
  Field field;
  int numberOfPlayers;
  unsigned long int startTime;
  unsigned long int endTime;
  unsigned long int currentTime;
  std::map<int,Sensor> sensors;
  std::map<Player,unsigned long int> ballPossesion;
};
#endif
