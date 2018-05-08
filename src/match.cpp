#include "match.h"
#include "objectwithsensor.h"
#define DUMMY_DEPTH -1000000

Match::Match(Field f) : field(f),startTime(0),endTime(0),currentTime(0),currentlyPlaying(false),numberOfPlayers(0){}

void Match::simulateMatch(std::vector<Event> events, std::vector<TimeInterval> intervals){
  Position p(0, 0,DUMMY_DEPTH);
  bool updatedPositions=false;
  Player closerToTheBall;
  std::map<Player,unsigned long int> tempPossession=ballPossesion;
  std::map<int,Sensor> tempSens=sensors;
  for(auto & e1:tempSens)
    e1.second.setPosition(p);
  for(auto & e1:tempPossession)
    e1.second=0;
#pragma omp parallel default(shared) private(updatedPositions,closerToTheBall,tempPossession,tempSens)
{
  for(int i=0;i<events.length();i++){
    ObjectWithSensor tempObj=tempSens[events[i].getSid()].getObject();
    if(!strcmp(tempObj.getType(),"Player")){
      tempSens[events[i].getSid()].setPosition(events[i].getPosition());
    }
    else if(!strcmp(tempObj.getType(),"Ball"){
      if(field.isOnField(tempObj.getPosition()) && !isInPause(intervals,event[i].getTimestamp())){
        if(!updatedPositions){
          checkPositions(tempSens,events,i)
          updatedPositions=true;
        }
        closerToTheBall(tempSens,tempObj.getPosition(),closerToTheBall);
        if(closerToTheBall==NULL)
          continue;
        else{
          tempPossession[closerToTheBall]+=500000000;
        }
      }
    }
  }
  #pragma omp critical{
    for(auto & e1:ballPossesion)
      e1.second+=tempPossession[e1.first];
    }
}
}

void closerToTheBall(std::map<int,Sensor> tempSens,Position pos, Player & player,int distance){
  for(auto &e:tempSens){
    if(strcmp(e.second.getObject().getType(),"Player")){
      int tempd = pos.compute3DDistance(e.second.getPosition());
      if(tempd<=distance){
        distance=tempd;
        player=e.second.getObject();
      }

    }

}}

void checkPositions(std::map<int,Sensor> & tempSens,std::vector<Event> events,int i){
  std::list<int> notfoundidsens;
  int elemtoremove;
  for(auto &e:tempSens){
    if(strcmp(e.second.getObject().getType(),"Player") && e.second.getPosition().getZ()==DUMMY_DEPTH)
      notfoundidsens.push_back(e.first);
  }
  for(;!notfoundidsens.empty() && i>=0;--i){
    for(auto &e: notfoundidsens){
      if(event[i].getSid()==e){
        tempSens[e].setPosition(event[i].getPosition());
        elemtoremove=event[i].getSid();
      }
    }
      notfoundidsens.remove(elemtoremove);
  }
  if(!notfoundidsens.empty() && i+1==0){
    for(auto &e: notfoundidsens){
      tempSens[e]=sensors[e];
    }
}}

bool isInPause(std::vector<TimeInterval> intervals,unsigned long int ts){
  for(auto &e:intervals){
    if(e.isInPause(ts))
      return true;
  }
  return false;
}

void Match::addPlayer(Player & p){
  players.push_back(p)
  numberOfPlayers++;
  ballPossesion[p]=0;
}

void Match::addReferee(Referee & r){
  referees.push_back(r);
}

void Match::addBall(Ball & b){
    balls.push_back(b);
}
