#ifndef MATCH_H_
#define MATCH_H_
#include "field.h"
#include "player.h"
#include "event.h"
#include "timeinterval.h"
#include "sensor.h"
#include "position.h"
#include <memory>
#include <vector>
#include <map>

class Match{
public:
  Match(Field f,unsigned long int startTime,unsigned long int endTime,int minDistFromTheBall);
  Match(Field f);
  void addSensor(Sensor s);
  std::map<int,Sensor> getSensors();
//  void restartMatch();
  void simulateMatch(std::vector<Event> events, std::vector<TimeInterval> intervals);
  unsigned long int getPlayerBallPossession(std::string playerName);
  unsigned long int getTeamBallPossession(std::string team);
  std::map<std::string,double> getPossessionStatistics();
private:
  Field field;
  int numberOfPlayers;
  int maximumDistanceFromTheBall;
  unsigned long int startTime;
  unsigned long int endTime;
  unsigned long int currentTime;
  std::map<int,Sensor> sensors;
  std::map<std::shared_ptr<Player>,unsigned long int> playerBallPossession;
  std::map<std::string,unsigned long int> teamBallPossession;

  void findPlayerCloserToTheBall(std::map<int,Sensor> & tempSens, Position pos, std::shared_ptr<Player> player);
  void findAllMostRecentPositions(std::map<int,Sensor> & tempSens,std::vector<Event> & events,int i);
  bool isInPlay(std::vector<TimeInterval> intervals,unsigned long int ts);
};
#endif
