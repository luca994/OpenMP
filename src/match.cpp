#include "match.h"
#include "objectwithsensor.h"
#define BALL_FREQUENCY 500000000
#define K 1

Match::Match(Field f)
{
  field=f;
  startTime=0;
  endTime=0;
  currentTime=0;
  numberOfPlayers=0;
}

void Match::findPlayerCloserToTheBall(std::map<int,Sensor> & tempSens, Position pos, std::shared_ptr<Player> player,int distance)
{
  for(auto &e:tempSens)
  {
    if(!e.second.getObject()->getType().compare("Player"))
    {
      int tempdistance = pos.compute3DDistance(e.second.getPosition());
      if(tempdistance<=distance)
      {
        distance=tempdistance;
        player=std::static_pointer_cast<Player>(e.second.getObject());
      }
    }
  }
}

void Match::findAllMostRecentPositions(std::map<int,Sensor> & tempSens,std::vector<Event> & events,int i)
{
  std::list<int> notfoundidsens;
  int elemtoremove;
  for(auto &e:tempSens)
  {
    if(e.second.getObject()->getType().compare("Player") && !e.second.getPosition().isValid())
      notfoundidsens.push_back(e.first);
  }
  for(;!notfoundidsens.empty() && i>=0;--i)
  {
    for(auto &e: notfoundidsens)
    {
      if(events[i].getSid()==e)
      {
        tempSens[e].setPosition(events[i].getPosition());
        elemtoremove=events[i].getSid();
      }
    }
      notfoundidsens.remove(elemtoremove);
  }
  if(!notfoundidsens.empty())
  {
    for(auto &e: notfoundidsens)
    {
      tempSens[e]=sensors[e];
    }
  }
}

bool Match::isInPlay(std::vector<TimeInterval> intervals,unsigned long int ts)
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

void Match::simulateMatch(std::vector<Event> events, std::vector<TimeInterval> intervals)
{
  Position p;
  std::shared_ptr<Player> playerCloserToTheBall;
  bool updatedPositions=false;
  std::map<std::shared_ptr<Player>,unsigned long int> tempPossession=ballPossession;
  std::map<int,Sensor> tempSens=sensors;
  for(auto & e1:tempPossession)
    e1.second=0;
  for(auto & e1:tempSens)
    e1.second.setPosition(p);
#pragma omp parallel shared(sensors,ballPossession) private(playerCloserToTheBall) firstprivate(updatedPositions,tempSens,tempPossession)
  {
    #pragma omp for schedule(static)
    for(int i=0;i<events.size();i++)
    {
      std::shared_ptr<ObjectWithSensor> tempObj=tempSens[events[i].getSid()].getObject();
      if(!tempObj->getType().compare("Player"))
      {
        tempSens[events[i].getSid()].setPosition(events[i].getPosition());
      }
      else if(!tempObj->getType().compare("Ball"))
      {
        if(field.isOnField(events[i].getPosition()) && !this->isInPlay(intervals,events[i].getTimestamp()))
        {
          if(!updatedPositions)
          {
            this->findAllMostRecentPositions(tempSens,events,i);
            updatedPositions=true;
          }
          this->findPlayerCloserToTheBall(tempSens,events[i].getPosition(),playerCloserToTheBall,K);
          if(playerCloserToTheBall==NULL)
            continue;
          else
          {
            tempPossession[playerCloserToTheBall]+=BALL_FREQUENCY;
            playerCloserToTheBall=NULL;
          }
        }
      }
    }
//  #pragma omp critical
  {
    for(auto & e1:ballPossession)
      e1.second+=tempPossession[e1.first];
  }
  }
}

void Match::addSensor(Sensor s)
{
  sensors[s.getSid()]=s;
  if(!s.getObject()->getType().compare("Player"))
  {
    ballPossession[std::static_pointer_cast<Player>(s.getObject())]=0;
    numberOfPlayers++;
  }
}
