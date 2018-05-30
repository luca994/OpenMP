#include "match.h"
#include "objectwithsensor.h"
#include <iostream>
#include <omp.h>

/**
*
*Constructor of class Match, initializes the field of the game, the start time and the end time (both in picoseconds)
*of the game and the distance from the ball (in meters) at which the ball possession has to be calculated
*
*/
Match::Match(Field f,unsigned long int startTime,unsigned long int endTime,double maxDistFromTheBall){
	field=f;
	this->startTime=startTime;
	this->endTime=endTime;
	currentTime=0;
	numberOfPlayers=0;
	maximumDistanceFromTheBall=maxDistFromTheBall*1000;
}

/**
*
*Second constructor of class Match, takes only the field, initializes the maximumDistanceFromTheBall
*to 1 meter and initializes to 0 all the other variables
*
*/
Match::Match(Field f){
	field=f;
	startTime=0;
	endTime=0;
	currentTime=0;
	numberOfPlayers=0;
	maximumDistanceFromTheBall=1000;
}

/**
*
*The methods takes in input the position taken by a ball sensor and a map of sensors (taken by the previous events)
*and returns the player that is the closest to the ball, if his distance is less than the maximumDistanceFromTheBall.
*Returns NULL if there isn't a player close enough to the ball.
*
*/
std::shared_ptr<Player> Match::findPlayerCloserToTheBall(std::map<int,Sensor> & tempSens, Position pos){
	std::shared_ptr<Player> player=NULL;
	double distance = maximumDistanceFromTheBall;
	double tempdistance;
	for(auto &e:tempSens){
		if(!e.second.getObject()->getType().compare("Player")){
			if(!std::static_pointer_cast<Player>(e.second.getObject())->isPlaying())
				continue;
			tempdistance = pos.compute3DDistance(e.second.getPosition());
			if(tempdistance<=distance){
				distance=tempdistance;
				player=std::static_pointer_cast<Player>(e.second.getObject());
			}
		}
	}
	return player;
}

/**
*
*The methods takes in input a map of sensors, a list of events and an integer i that represents the index
*at which the list of event is already checked. Then for each player in tempSens that has an invalid position,
*the method tries to find a recent valid position in the list of events and updates tempSens.
*
*/
void Match::findAllMostRecentPositions(std::map<int,Sensor> & tempSens,std::vector<Event> & events,int i){
	std::list<int> notfoundidsens;
	int elemtoremove=0;
	for(auto &e:tempSens){
		if(!e.second.getObject()->getType().compare("Player") && !e.second.getPosition().isValid())
			notfoundidsens.push_back(e.first);
	}
	for(;!notfoundidsens.empty() && i>=0;i--){
		for(auto &e: notfoundidsens){
			if(events[i].getSid()==e){
				tempSens[e].setPosition(events[i].getPosition());
				elemtoremove=events[i].getSid();
			}
		}
		if(elemtoremove!=0){
			notfoundidsens.remove(elemtoremove);
			elemtoremove=0;
		}
	}
	if(!notfoundidsens.empty())
		for(auto &e: notfoundidsens)
			tempSens[e]=sensors[e];
	}

/**
*
*Checks if the timestamp ts (in picoseconds) belongs to an interval in which the game is in play.
*Return true if the game is in play, false otherwise
*
*/
bool Match::isInPlay(std::vector<TimeInterval> & intervals,unsigned long int ts){
	if(ts<startTime || ts>endTime)
		return false;
	for(auto &e:intervals){
		if(e.isInPause(ts))
			return false;
	}
	return true;
}

/**
*
*It is the main method of the class, it is called for each interval T and takes the list of events for that interval.
*The main loop is executed in parallel through OpenMP and updates the ball possesion statistics of the players.
*Each time a ball events is found, the method checks if the game is in play and if the ball is in the field, then finds
*the closest player and assigns him the possesion. For each player event updates the position.
*
*/
void Match::simulateMatch(std::vector<Event> & events, std::vector<TimeInterval> & intervals){
	if(events.empty())
		return;
	Position p=Position();
	std::shared_ptr<Player> playerCloserToTheBall;
	bool updatedPositions,hasToUpdate;
	std::map<std::shared_ptr<Player>,unsigned long int> tempPossession=playerBallPossession;
	std::map<int,Sensor> tempSens=sensors;
	for(auto & e1:tempPossession)
		e1.second=0;
	for(auto & e1:tempSens)
		e1.second.setPosition(p);
	#pragma omp parallel default(shared) private(p,updatedPositions,playerCloserToTheBall,hasToUpdate) firstprivate(tempSens,tempPossession)
	{
		p=Position();
		hasToUpdate=false;
		updatedPositions=false;
		playerCloserToTheBall=NULL;
    	#pragma omp for schedule(static)
		for(int i=0;i<events.size();i++){
			std::shared_ptr<ObjectWithSensor> tempObj=tempSens[events[i].getSid()].getObject();
			if(!tempObj->getType().compare("Player")){
				tempSens[events[i].getSid()].setPosition(events[i].getPosition());
			}
			if(!tempObj->getType().compare("Ball")){
				if(field.isOnField(events[i].getPosition()) && isInPlay(intervals,events[i].getTimestamp())){
					if(!updatedPositions){
						findAllMostRecentPositions(tempSens,events,i);
						updatedPositions=true;
					}
					playerCloserToTheBall=findPlayerCloserToTheBall(tempSens,events[i].getPosition());
					if(!playerCloserToTheBall==NULL){
						tempPossession[playerCloserToTheBall]+=tempSens[events[i].getSid()].getPeriod();
						playerCloserToTheBall=NULL;
					}
				}
			}
			if(i==events.size()-1){
				if(updatedPositions==false)
					findAllMostRecentPositions(tempSens,events,i);
				hasToUpdate=true;
			}
		}
		for(auto & e1:playerBallPossession){
    		#pragma omp atomic
			e1.second+=tempPossession[e1.first];
            #pragma omp atomic
			teamBallPossession[e1.first->getTeam()]+=tempPossession[e1.first];
		}
		if(hasToUpdate){
			for(auto &e:sensors){
				if(tempSens[e.first].getPosition().isValid())
					e.second=tempSens[e.first];
			}
		}
	}
	currentTime=events[events.size()-1].getTimestamp();
}

/**
*
*Returns the ball possession of the player.
*Takes the name of the player as input
*
*/
unsigned long int Match::getPlayerBallPossession(std::string playerName){
	for(auto &e:playerBallPossession)
		if(!e.first->getName().compare(playerName))
	return e.second;
	return 0;
}

/**
*
*Return the ball possesion of the team.
*Takes the name of the team as input
*
*/
unsigned long int Match::getTeamBallPossession(std::string team){
	for(auto &e:teamBallPossession)
	if(!e.first.compare(team))
		return e.second;
	return 0;
}

/**
*
*Calculates the percentage of the ball possession for each player and for
*each team. Returns a map with the name of the player/team and the percentage
*
*/
std::map<std::string,double> Match::getPossessionStatistics(){
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

/**
*
*Returns the map of sensors
*
*/
std::map<int,Sensor> Match::getSensors(){
	return sensors;
}

/**
*
*Returns the current time of the game
*
*/
unsigned long int Match::getCurrentTime(){
	return currentTime;
}

/**
*
*Returns the end time of the game (useful only when you have all the events
*of the game, so the match is already finished)
*
*/
unsigned long int Match::getEndTime(){
	return endTime;
}

/**
*
*Returns a vector with the names of all the players
*
*/
std::vector<std::string> Match::getPlayersName(){
	std::vector<std::string> plrs;
	for(auto &e:playerBallPossession)
		plrs.push_back(e.first->getName());
	return plrs;
}

/**
*
*Adds the sensor s to the list of sensors.
*If it's a sensor of a player initializes the player ball possesion
*
*/
void Match::addSensor(Sensor s){
	std::map<std::string,unsigned long int>::iterator it;
	sensors[s.getSid()]=s;
	if(!s.getObject()->getType().compare("Player")){
		std::shared_ptr<Player> player=std::static_pointer_cast<Player>(s.getObject());
		playerBallPossession[player]=0;
		numberOfPlayers++;
		it = teamBallPossession.find(player->getTeam());
		if (it == teamBallPossession.end())
			teamBallPossession[player->getTeam()]=0;
	}
}