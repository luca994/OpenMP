#include "parser.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <cmath>

using namespace std;

#define T 30

class Position{
public:
	Position(){}
	Position(int posx, int posy, int posz){
		x=posx;
		y=posy;
		z=posz;
	}
	int x;
	int y;
	int z;
};

class Event{
public:
	Event(int sid,unsigned long int timestamp, Position actualPosition){
		sensorid=sid;
		ts=timestamp;
		p=actualPosition;
	}
	Position p;
	int sensorid;
	unsigned long int ts;
};

void print_list(vector<Event> events){
	for(auto &e: events){
		cout<<e.sensorid<<" "<<e.ts<<" "<<e.p.x<<" "<<e.p.y<<" "<<e.p.z<<endl;
	}
}

void Parser::parse_file(string file_name){
	long int count=0;
	int end=1;
	vector<Event> events;
	ifstream infile;
	infile.open(file_name, ios::in);
	string dataLine;
	string sid, ts, posx, posy, posz, vel, acc, velx, vely, velz, accx, accy, accz;
	unsigned long int ts_old=0;
	unsigned long int diff=0;
	bool firstTime=true;
	while(!infile.eof()){
		int eventField=0;
		std::getline(infile, dataLine);
		string temp;
		for(int i=0;dataLine[i]!='\0';i++){
			if(dataLine[i]!=',')
				temp+=dataLine[i];
			if(dataLine[i]==','){
				switch(eventField){
					case 0:
						sid=temp;							
						break;
					case 1:
						ts=temp;
						if(firstTime){
							const char * tsol = ts.c_str();
							ts_old = strtoul(tsol, NULL, 10);
							cout<<"tsold: "<<ts_old<<endl;
							firstTime=false;					
						}
						break;
					case 2:
						posx=temp;						
						break;
					case 3:
						posy=temp;						
						break;
					case 4:
						posz=temp;						
						break;
					case 5:
						vel=temp;						
						break;
					case 6:
						acc=temp;						
						break;
					case 7:
						velx=temp;						
						break;
					case 8:
						vely=temp;						
						break;
					case 9:
						velz=temp;						
						break;
					case 10:
						accx=temp;						
						break;
					case 11:
						accy=temp;						
						break;
					case 12:
						accz=temp;						
						break;
					default:
						cout<<"Error"<<endl;
						eventField=0;
						break;
				}
				temp="";
				eventField++;
			}
		}
		accz=temp;
		temp="";		
		Position p(stoi(posx,NULL),stoi(posy,NULL),stoi(posz,NULL));
		const char * c = ts.c_str();
		unsigned long int timest = strtoul(c, NULL, 10);
		Event e(stoi(sid, NULL), timest, p);
		events.push_back(e);
		//print_list(events);
		//cout<<"---------------------------------"<<endl;
		diff = (e.ts-ts_old)*pow(10,12);
		count++;
		//cout<<"diff: "<<diff<<endl;
	}
	//print_list(events);
	cout<<count<<endl;
}
