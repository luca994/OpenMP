#include "parser.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include "position.h"
#include <sstream>

using namespace std;

int klo;

Parser::Parser(std::string file_name, int interval){
	this->interval=interval;
	infile.open(file_name, ios::in);
}

Parser::~Parser(){
	infile.close();
}

//delete
void print_list_events(vector<Event> events){
	for(auto &e: events){
		cout<<e.getSid()<<" "<<e.getTimestamp()<<" "<<e.getPosition().getX()<<" "<<e.getPosition().getY()<<" "<<e.getPosition().getZ()<<endl;
	}
}

void print_list_pauses(vector<TimeInterval> tints){
	for(auto &e: tints){
		cout<<"start: "<<e.getStart()<<" end: "<<e.getEnd()<<endl;
	}
}

vector<Event> Parser::parse_event_file(){
	long int count=0; //delete
	vector<Event> events;
	string sid, ts, posx, posy, posz, vel, acc, velx, vely, velz, accx, accy, accz;
	unsigned long int ts_old=0;
	unsigned long int diff=0;
	bool firstTime=true;
	while(diff<=interval*pow(10,12) && !infile.eof()){ //loop to parse the T interval of the file
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
	cout<<"num di elem: "<<count<<endl; //delete
//	klo+=count;
//	cout<<"total: "<<klo<<endl;
	//print_list(events);//delete
	return events;
}

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

void Parser::setFile(string file_name){
	infile.close();
	infile.open(file_name, ios::in);
}
