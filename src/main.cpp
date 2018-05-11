#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include <tuple>
#include "position.h"
#include "field.h"
#include "parser.h"
#include "match.h"
#include "ball.h"
#include "referee.h"
#include "player.h"

using namespace std;

Field initialize_field(string filename)
{
	ifstream csv_file(filename);
	if(!csv_file.is_open())
    cout<<"error in opening file "<<filename<<endl;
	Position *vertex=new Position[4];
	string x,y,z;
	getline(csv_file,x,'\n');
	for(int i=0;i<4 && !csv_file.eof();i++)
	{
			getline(csv_file,x,';');
			getline(csv_file,y,';');
			getline(csv_file,z,'\n');
			vertex[i]=Position(stoi(x),stoi(y),stoi(z));
	}
	Field field(vertex[0],vertex[1],vertex[2],vertex[3]);
	delete[] vertex;
	csv_file.close();
	return field;
}

unsigned long int * read_time(string filename)
{
	ifstream csv_file(filename);
	unsigned long int * ts=new unsigned long int[2];
	if(!csv_file.is_open())
		cout<<"error in opening file "<<filename<<endl;
	string start,end;
	getline(csv_file,start,'\n');
	getline(csv_file,start,';');
	getline(csv_file,end,'\n');
	csv_file.close();
	ts[0]=stoul(start);
	ts[1]=stoul(end);
	return ts;
}

void initialize_match(Match &match,string filename)
{
	ifstream csv_file(filename);
	if(!csv_file.is_open())
    cout<<"error in opening file "<<filename<<endl;
	vector<tuple<string,string,string,string>> elements;
	string id,type,name,team;
	for(int i=0;!csv_file.eof();i++) {
		if(i==0) //Skip the first line
			getline(csv_file,id,'\n');
		else
		{
			getline(csv_file,id,';');
			getline(csv_file,type,';');
			getline(csv_file,name,';');
			getline(csv_file,team,'\n');
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

int main()
{
	unsigned long int * startend = new unsigned long int[2];
	Field field = initialize_field("files/field.csv");
	startend = read_time("files/time.csv");
	Match match(field,startend[0],startend[1],1);
	initialize_match(match,"files/metadata.csv");
	/*
	loop(ogni T){
	  read and create vector<Event> events;
	  read and create vector<TimeInterval> intervals;
	  match.simulateMatch(p.parse_file(),intervals);
	  for(auto &e: match.getPossessionStatistics())
	  	std::cout<<"Ball Possession "<<e.first<<" = "<<e.second*100<<"%"<< std::endl
	}
	*/
	unsigned long int beginMatch = 10629342490369879;
	int exit=0;
	Parser p("/home/riccardo/Desktop/middleware_projects/referee-events/referee-events/Game Interruption/1st Half.csv", 60);
	while(!exit){
		p.parse_interval_file(beginMatch);
		cin>>exit;
	}
	
}
