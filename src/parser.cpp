#include "ball.h"
#include "referee.h"
#include "player.h"
#include "position.h"
#include "parser.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <sstream>

using namespace std;

/**
*
*Constructor of the class Parser, takes the name of the file to parse as input
*and opens it in reading mode.
*
*/
Parser::Parser(std::string file_name){
	infile.open(file_name, ios::in);
	interval=0;
	lastEventTs=0;
	if(!infile.is_open())
		std::cout<<"failed opening "<<file_name<<std::endl;
}

/**
*
*Constructor of the class Parser, takes the name of the file to parse as input
*and opens it in reading mode. It takes also an integer that is the interval (in seconds) at which
*the file will be parsed.
*
*/
Parser::Parser(std::string file_name, int interval){
	this->interval=interval;
	lastEventTs=0;
	infile.open(file_name, ios::in);
}

/**
*
*Destroyer of the class Parser, closes the file before destroy the object
*
*/
Parser::~Parser(){
	infile.close();
}

/**
*
*Parses the event file (full-game) set in the constructor.
*Returns a list of events for the interval of time (based on the timestamps of the events)
*set in the constructor.
*
*/
vector<Event> Parser::parse_event_file(){
	vector<Event> events;
	string sid, ts, posx, posy, posz, trash;
	unsigned long int diff=0;
	while(diff<=interval*pow(10,12) && !infile.eof()){
		getline(infile, sid, ',');
		getline(infile, ts, ',');
		getline(infile, posx, ',');
		getline(infile, posy, ',');
		getline(infile, posz, ',');
		getline(infile, trash, '\n');
		if(sid.empty() || ts.empty() || posx.empty() || posy.empty() || posz.empty())
			continue;
		Position p(stoi(posx),stoi(posy),stoi(posz));
		Event e(stoi(sid), stoul(ts), p);
		events.push_back(e);
		diff = (e.getTimestamp()-lastEventTs);
	}
	lastEventTs = events[events.size()-1].getTimestamp();
	//cout<<"number of parsed events: "<<events.size()<<endl;
	return events;
}

/**
*
*Parses the interval file where there are the phases of the game (in pause or not).
*Returns a vector of time intervals.
*Takes the timestamp of the begin of the match as input.
*
*/
vector<TimeInterval> Parser::parse_interval_file(unsigned long int beginMatch){
	string timeStart, timeEnd, temp;
	vector<TimeInterval> intervalVect;
	getline(infile, temp, '\n');
	getline(infile, temp, ';');
	while(temp.compare("end")){
		getline(infile, temp, ';');
		getline(infile, timeStart, ';');
		getline(infile, temp, '\n');
		getline(infile, temp, ';');
		getline(infile, temp, ';');
		getline(infile, timeEnd, ';');
		getline(infile, temp, '\n');
		TimeInterval tint(convertTime(timeStart)+beginMatch, convertTime(timeEnd)+beginMatch, true);
		intervalVect.push_back(tint);
		getline(infile, temp, ';');
	}
	return intervalVect;
}

/**
*
*Method to convert the time given as a string in the format hh:mm:ss:ms
*in picoseconds as an unsigned long int
*
*/
unsigned long int Parser::convertTime(string time){
	istringstream iss(time);
	unsigned long int result=0;
	string temp;
	getline(iss, temp, ':');
	result=stoul(temp)*60; //time in minutes
	getline(iss, temp, ':');
	result=(result+stoul(temp))*60; //time in seconds
	getline(iss, temp, '.');
	result=(result+stoul(temp))*1000; //time in milliseconds
	getline(iss, temp, ';');
	result=(result+stoul(temp))*pow(10,9); //time in picoseconds
	return result;
}

/**
*
*Parses the file with the field coordinates. Returns
*a field object.
*
*/
Field Parser::initialize_field(){
	Position *vertex=new Position[4];
	string x,y,z;
	getline(infile,x,'\n');
	for(int i=0;i<4 && !infile.eof();i++){
		getline(infile,x,';');
		getline(infile,y,';');
		getline(infile,z,'\n');
		vertex[i]=Position(stoi(x),stoi(y),stoi(z));
	}
	Field field(vertex[0],vertex[1],vertex[2],vertex[3]);
	delete[] vertex;
	return field;
}

/**
*
*Parses the file with the data of the sensors, the players and the team.
*Takes a Match object as input and initializes it with the informations parsed
*
*/
void Parser::initialize_match(Match &match){
	vector<tuple<string,string,string,string>> elements;
	string id,type,name,team;
	for(int i=0;!infile.eof();i++) {
		if(i==0) //Skip the first line
			getline(infile,id,'\n');
		else{
			getline(infile,id,';');
			getline(infile,type,';');
			getline(infile,name,';');
			getline(infile,team,'\n');
			if(id.compare(""))
				elements.push_back(make_tuple(id,type,name,team));
		}
	}
	for(auto &e:elements)
		if(get<1>(e)=="Ball")
			match.addSensor(Sensor(stoi(get<0>(e)),make_shared<Ball>()));
	for(auto &e:elements)
		if(get<1>(e)=="Referee")
			match.addSensor(Sensor(stoi(get<0>(e)),make_shared<Referee>()));
	vector<tuple<string,string,string,string>>::iterator it;
  	for(it = elements.begin(); it != elements.end(); ++it){
		if(get<1>(*it)=="Player"){
			shared_ptr<Player> player = make_shared<Player>(get<2>(*it),get<3>(*it),true);
			while(!get<2>(*it).compare(player->getName())){
				match.addSensor(Sensor(stoi(get<0>(*it)),player));
				it++;
			}
			it--;
		}
	}
}

/**
*
*Parses the file with the informations about the time of the begin
*and end of the first and second half of the match
*Returns a vector of timestamps with the time informations
*
*/
unsigned long int * Parser::read_time(){
	unsigned long int * ts=new unsigned long int[4];
	string start,end;
	getline(infile,start,'\n');
	getline(infile,start,';');
	getline(infile,end,'\n');
	ts[0]=stoul(start);
	ts[1]=stoul(end);
	getline(infile,start,';');
	getline(infile,end,'\n');
	ts[2]=stoul(start);
	ts[3]=stoul(end);
	return ts;
}

/**
*
*Sets the interval at which the event_file is parsed
*
*/
void Parser::setInterval(int interv){
	interval=interv;
}

/**
*
*Open a new file with file_name as name in the parser object.
*If there is a file already opened, closes it.
*
*/
void Parser::setFile(string file_name){
	if(infile.is_open())
		infile.close();
	infile.open(file_name, ios::in);
	if(!infile.is_open())
		std::cout<<"failed opening "<<file_name<<std::endl;
}