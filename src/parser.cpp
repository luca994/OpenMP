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


Parser::Parser(std::string file_name){
	infile.open(file_name, ios::in);
	interval=0;
	if(!infile.is_open())
		std::cout<<"failed opening "<<file_name<<std::endl;
}

Parser::Parser(std::string file_name, int interval){
	this->interval=interval;
		infile.open(file_name, ios::in);
}

Parser::~Parser(){
	infile.close();
}

//delete
void print_list_events(vector<Event> events)
{
	for(auto &e: events)
		cout<<e.getSid()<<" "<<e.getTimestamp()<<" "<<e.getPosition().getX()<<" "<<e.getPosition().getY()<<" "<<e.getPosition().getZ()<<endl;
}

void print_list_pauses(vector<TimeInterval> tints)
{
	for(auto &e: tints)
		cout<<"start: "<<e.getStart()<<" end: "<<e.getEnd()<<endl;
}

vector<Event> Parser::parse_event_file()
{
	long int count=0; //delete
	vector<Event> events;
	string sid, ts, posx, posy, posz, vel, acc, velx, vely, velz, accx, accy, accz;
	unsigned long int ts_old=0;
	unsigned long int diff=0;
	bool firstTime=true;
	while(diff<=interval*pow(10,12) && !infile.eof())
	{ //loop to parse the T interval of the file
		getline(infile, sid, ',');
		getline(infile, ts, ',');
		if(firstTime){
			ts_old = stoul(ts);
			firstTime=false;
		}
		getline(infile, posx, ',');
		getline(infile, posy, ',');
		getline(infile, posz, ',');
		getline(infile, vel, ',');
		getline(infile, acc, ',');
		getline(infile, velx, ',');
		getline(infile, vely, ',');
		getline(infile, velz, ',');
		getline(infile, accx, ',');
		getline(infile, accy, ',');
		getline(infile, accz, '\n');
		Position p(stoi(posx),stoi(posy),stoi(posz));
		unsigned long int timest = stoul(ts);
		Event e(stoi(sid, NULL), timest, p);
		events.push_back(e);
		diff = (e.getTimestamp()-ts_old);
		count++; //delete
	}
	cout<<"number of parsed events: "<<count<<endl; //delete
	return events;
}

vector<TimeInterval> Parser::parse_interval_file(unsigned long int beginMatch)
{
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

unsigned long int Parser::convertTime(string time)
{
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

Field Parser::initialize_field()
{
	Position *vertex=new Position[4];
	string x,y,z;
	getline(infile,x,'\n');
	for(int i=0;i<4 && !infile.eof();i++)
	{
			getline(infile,x,';');
			getline(infile,y,';');
			getline(infile,z,'\n');
			vertex[i]=Position(stoi(x),stoi(y),stoi(z));
	}
	Field field(vertex[0],vertex[1],vertex[2],vertex[3]);
	delete[] vertex;
	return field;
}


void Parser::initialize_match(Match &match)
{
	vector<tuple<string,string,string,string>> elements;
	string id,type,name,team;
	for(int i=0;!infile.eof();i++) {
		if(i==0) //Skip the first line
			getline(infile,id,'\n');
		else
		{
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
  for(it = elements.begin(); it != elements.end(); ++it)
	{
		if(get<1>(*it)=="Player")
		{
			shared_ptr<Player> player = make_shared<Player>(get<2>(*it),get<3>(*it),true);
			while(!get<2>(*it).compare(player->getName()))
			{
				match.addSensor(Sensor(stoi(get<0>(*it)),player));
				it++;
			}
			it--;
		}
	}
}

unsigned long int * Parser::read_time()
{
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

void Parser::setInterval(int interv)
{
	interval=interv;
}

void Parser::setFile(string file_name)
{
	if(infile.is_open())
		infile.close();
	infile.open(file_name, ios::in);
	if(!infile.is_open())
		std::cout<<"failed opening "<<file_name<<std::endl;
}
