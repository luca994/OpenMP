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
#include <math.h>

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
	unsigned long int * ts=new unsigned long int[4];
	if(!csv_file.is_open())
		cout<<"error in opening file "<<filename<<endl;
	string start,end;
	getline(csv_file,start,'\n');
	getline(csv_file,start,';');
	getline(csv_file,end,'\n');
	ts[0]=stoul(start);
	ts[1]=stoul(end);
	getline(csv_file,start,';');
	getline(csv_file,end,'\n');
	ts[2]=stoul(start);
	ts[3]=stoul(end);
	csv_file.close();
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

int main(int argc,char *argv[])
{
	int k=1;
	unsigned long int * startend = new unsigned long int[4];
	Field field = initialize_field("files/field.csv");
	startend = read_time("files/time.csv");
	Match match(field,startend[0],startend[3],k);
	initialize_match(match,"files/metadata.csv");
	Parser events_generator("files/full-game",30);
	Parser intervals_generator("files/1st Half.csv",0);
	vector<TimeInterval> intervals = intervals_generator.parse_interval_file(startend[0]);
	intervals_generator.setFile("files/2nd Half.csv");
	intervals.push_back(TimeInterval(startend[1],startend[2],true));
	vector<TimeInterval> intervals2 = intervals_generator.parse_interval_file(startend[2]);
	intervals.insert(intervals.end(),intervals2.begin(),intervals2.end());
	while(match.getCurrentTime()<=startend[3])
	{
		match.simulateMatch(events_generator.parse_event_file(),intervals);
	//	cout<<match.getCurrentTime()<<endl;
	//	for(auto &e:match.getPossessionStatistics())
	//		cout<<"Possession "<<e.first<<" = "<<e.second<<endl;
	}
	Parser pPoss("files/Ben Müller.csv", 0);
	vector<TimeInterval> tposs = pPoss.parse_interval_file(0);
	unsigned long int totTimePoss=0;
	for(auto &i: tposs){
		totTimePoss+=(i.getEnd()-i.getStart());
	}
	cout<<"Real Muller time: "<<totTimePoss<<endl;
	cout<<"Calc Muller time: "<<match.getPlayerBallPossession("Ben Mueller")<<endl;
	/*
	loop(ogni T){
	  read and create vector<Event> events;
	  read and create vector<TimeInterval> intervals;
	  match.simulateMatch(p.parse_file(),intervals);
	  for(auto &e: match.getPossessionStatistics())
	  	std::cout<<"Ball Possession "<<e.first<<" = "<<e.second*100<<"%"<< std::endl
	}
	unsigned long int beginMatch = startend[0];
		int exit=0;
		Parser p("/home/riccardo/Desktop/middleware_projects/referee-events/referee-events/Game Interruption/1st Half.csv", 60);
		while(!exit){
			p.parse_interval_file(beginMatch);
			cin>>exit;
}	*/
}
