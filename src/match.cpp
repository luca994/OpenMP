#include "match.h"
#include "objectwithsensor.h"
#include <iostream>
#include <omp.h>

Match::Match(Field f,unsigned long int startTime,unsigned long int endTime,double maxDistFromTheBall)
{
  field=f;
  this->startTime=startTime;
  this->endTime=endTime;
  currentTime=0;
  numberOfPlayers=0;
  maximumDistanceFromTheBall=maxDistFromTheBall*1000;
}

Match::Match(Field f)
{
  field=f;
  startTime=0;
  endTime=0;
  currentTime=0;
  numberOfPlayers=0;
  maximumDistanceFromTheBall=1000;
}

std::shared_ptr<Player> Match::findPlayerCloserToTheBall(std::map<int,Sensor> & tempSens, Position pos)
{
  std::shared_ptr<Player> player=NULL;
  double distance = maximumDistanceFromTheBall;
  double tempdistance;
  for(auto &e:tempSens)
  {
    if(!e.second.getObject()->getType().compare("Player"))
    {
      if(!std::static_pointer_cast<Player>(e.second.getObject())->isPlaying())
        continue;
      tempdistance = pos.compute3DDistance(e.second.getPosition());
      if(tempdistance<=distance)
      {
        distance=tempdistance;
        player=std::static_pointer_cast<Player>(e.second.getObject());
      }
    }
  }
  return player;
}

void Match::findAllMostRecentPositions(std::map<int,Sensor> & tempSens,std::vector<Event> & events,int i)
{
  std::list<int> notfoundidsens;
  int elemtoremove=0;
  for(auto &e:tempSens)
  {
    if(!e.second.getObject()->getType().compare("Player") && !e.second.getPosition().isValid())
      notfoundidsens.push_back(e.first);
  }
  for(;!notfoundidsens.empty() && i>=0;i--)
  {
    for(auto &e: notfoundidsens)
    {
      if(events[i].getSid()==e)
      {
        tempSens[e].setPosition(events[i].getPosition());
        elemtoremove=events[i].getSid();
      }
    }
    if(elemtoremove!=0)
      notfoundidsens.remove(elemtoremove);
  }
  if(!notfoundidsens.empty())
    for(auto &e: notfoundidsens)
      tempSens[e]=sensors[e];
}

bool Match::isInPlay(std::vector<TimeInterval> & intervals,unsigned long int ts)
{
  if(ts<startTime || ts>endTime)
    return false;
  for(auto &e:intervals)
  {
    if(e.isInPause(ts))
      return false;
  }
  return true;
}

int Match::simulateMatch(std::vector<Event> & events, std::vector<TimeInterval> & intervals)
{
  if(events.empty())
    return 0;
  int n=0;
  Position p;
  std::shared_ptr<Player> playerCloserToTheBall;
  bool updatedPositions;
  bool hasToUpdate;
  std::map<std::shared_ptr<Player>,unsigned long int> tempPossession=playerBallPossession;
  std::map<int,Sensor> tempSens=sensors;
  for(auto & e1:tempPossession)
    e1.second=0;
  for(auto & e1:tempSens)
    e1.second.setPosition(p);
//  #pragma omp parallel default(shared) private(p,updatedPositions,playerCloserToTheBall,hasToUpdate) firstprivate(tempSens,tempPossession)
//    {
    p=Position();
    hasToUpdate=false;
    updatedPositions=false;
    playerCloserToTheBall=NULL;
//    #pragma omp for schedule(static)
      for(int i=0;i<events.size();i++)
      {
        std::shared_ptr<ObjectWithSensor> tempObj=tempSens[events[i].getSid()].getObject();
        if(!tempObj->getType().compare("Player")){
          tempSens[events[i].getSid()].setPosition(events[i].getPosition());
          n++;
        }
        else if(!tempObj->getType().compare("Ball"))
        {
          if(field.isOnField(events[i].getPosition()) && isInPlay(intervals,events[i].getTimestamp()))
          {
            n++;
            if(!updatedPositions)
            {
              findAllMostRecentPositions(tempSens,events,i);
              updatedPositions=true;
            }
            playerCloserToTheBall=findPlayerCloserToTheBall(tempSens,events[i].getPosition());
            if(playerCloserToTheBall==NULL)
              continue;
            else
            {
              tempPossession[playerCloserToTheBall]+=tempSens[events[i].getSid()].getPeriod();
              playerCloserToTheBall=NULL;
            }
          }
        }
        if(i==events.size()-1)
          hasToUpdate=true;
      }
          for(auto & e1:playerBallPossession)
          {
//            #pragma omp atomic
            e1.second+=tempPossession[e1.first];
//            #pragma omp atomic
            teamBallPossession[e1.first->getTeam()]+=tempPossession[e1.first];
          }
      if(hasToUpdate)
      {
        for(auto &e:sensors)
        {
          if(tempSens[e.first].getPosition().isValid())
            e.second=tempSens[e.first];
        }
      }
  //  }
  currentTime=events[events.size()-1].getTimestamp();
  return n;
}

unsigned long int Match::getPlayerBallPossession(std::string playerName)
{
  for(auto &e:playerBallPossession)
    if(!e.first->getName().compare(playerName))
      return e.second;
  return 0;
}

unsigned long int Match::getTeamBallPossession(std::string team)
{
  for(auto &e:teamBallPossession)
    if(!e.first.compare(team))
      return e.second;
  return 0;
}

std::map<std::string,double> Match::getPossessionStatistics()
{
  unsigned long int totaltime=0;
  std::map<std::string,double> possessionMap;
  for(auto &e:teamBallPossession)
    totaltime+=e.second;
  if(totaltime==0)
    return possessionMap;
  for(auto &e:teamBallPossession)
    possessionMap[e.first]=(e.second/(double)totaltime);
  for(auto &e:playerBallPossession)
    possessionMap[e.first->getName()]=(e.second/(double)totaltime);
  return possessionMap;
}

std::map<int,Sensor> Match::getSensors()
{
  return sensors;
}

unsigned long int Match::getCurrentTime()
{
  return currentTime;
}

std::vector<std::string> Match::getPlayersName()
{
  std::vector<std::string> plrs;
  for(auto &e:playerBallPossession)
    plrs.push_back(e.first->getName());
  return plrs;
}

void Match::addSensor(Sensor s)
{
  std::map<std::string,unsigned long int>::iterator it;
  sensors[s.getSid()]=s;
  if(!s.getObject()->getType().compare("Player"))
  {
    std::shared_ptr<Player> player=std::static_pointer_cast<Player>(s.getObject());
    playerBallPossession[player]=0;
    numberOfPlayers++;
    it = teamBallPossession.find(player->getTeam());
    if (it == teamBallPossession.end())
      teamBallPossession[player->getTeam()]=0;
  }
}
