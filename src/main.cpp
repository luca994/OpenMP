#include <iostream>
#include "parser.h"

using namespace std;

int main(){
	/*leggi metadata
	Position vertex1(x,y,z);
	Position vertex2(x,y,z);
	Position vertex3(x,y,z);
	Position vertex4(x,y,z);
	Field field(vertex1,vertex2,vertex3,vertex4);
	Match match(field,startTime,endTime);
	while(...)
	  match.addSensor(Sensor(sid,make_shared<Referee>()));
	while(...)
	  match.addSensor(Sensor(sid,make_shared<Ball>()));
	while(...)
	  match.addSensor(Sensor(sid,make_shared<Player>(name,team,isInPlay)));
	loop(ogni T){
	  read and create vector<Event> events;
	  read and create vector<TimeInterval> intervals;
	  match.simulateMatch(events,intervals);
	  for(auto &e: match.getPossessionStatistics())
	  std::cout<<"Ball Possession "<<e.first<<" = "<<e.second*100<<"%"<< std::endl
	}
	*/
	int exit=0;
	Parser p("/home/riccardo/Desktop/middleware_projects/full-game/full-game", 60);
	while(!exit){
		p.parse_file();
		cin>>exit;
	}
}
