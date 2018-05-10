#include <iostream>
#include "parser.h"

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
	Parser *p= new Parser();
	p->parse_file("game_splitted");
	*/
	Parser *p= new Parser();
	p->parse_file("/home/riccardo/Desktop/middleware_projects/full-game/full-game");
}
