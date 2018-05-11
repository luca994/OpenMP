#include "parser.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include "position.h"

using namespace std;

Parser::Parser(std::string file_name, int interval){
	this->interval=interval;
	infile.open(file_name, ios::in);
}

Parser::~Parser(){
	infile.close();
}

void print_list(vector<Event> events){
	for(auto &e: events){
		cout<<e.getSid()<<" "<<e.getTimestamp()<<" "<<e.getPosition().getX()<<" "<<e.getPosition().getY()<<" "<<e.getPosition().getZ()<<endl;
	}
}

vector<Event> Parser::parse_file(){
	long int count=0; //delete
	vector<Event> events;
	string dataLine;
	string sid, ts, posx, posy, posz, vel, acc, velx, vely, velz, accx, accy, accz;
	unsigned long int ts_old=0;
	unsigned long int diff=0;
	bool firstTime=true;
	while(diff<=interval*pow(10,12) && !infile.eof()){ //loop to parse the T interval of the file
		int eventField=0;
		getline(infile, dataLine);
		string temp;
		for(int i=0;dataLine[i]!='\0';i++){ //loop to parse the line
			if(dataLine[i]!=',')
				temp+=dataLine[i];
			else{
				switch(eventField){
					case 0:
						sid=temp;
						break;
					case 1:
						ts=temp;
						if(firstTime){
							const char * tsol = ts.c_str();
							ts_old = strtoul(tsol, NULL, 10);
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
		diff = (e.getTimestamp()-ts_old);
		count++; //delete
	}
	cout<<"num di elem: "<<count<<endl; //delete
	return events;
}
