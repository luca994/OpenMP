#include <iostream>
#include <string>
#include <math.h>
#include "position.h"
#include "field.h"
#include "parser.h"
#include "match.h"

using namespace std;

unsigned long int computeRealPossession(string playerName)
{
	unsigned long int totTimePoss=0;
	string filename1 = "files/possession1st/"+playerName+".csv";
	string filename2 = "files/possession2nd/"+playerName+".csv";
	Parser pPoss1(filename1);
	Parser pPoss2(filename2);
	vector<TimeInterval> tposs;
	tposs = pPoss1.parse_interval_file(0);
	for(auto &i: tposs)
	{
		totTimePoss+=(i.getEnd()-i.getStart());
	}
	tposs = pPoss2.parse_interval_file(0);
	for(auto &i: tposs)
	{
		totTimePoss+=(i.getEnd()-i.getStart());
	}
	return totTimePoss;
}

void printStats(Match & m)
{
		float realtot=0,calctot=0;
		for(auto &e:m.getPlayersName())
		{
			realtot+=computeRealPossession(e)/pow(10,12);
			calctot+=m.getPlayerBallPossession(e)/pow(10,12);
		}
		for(auto &e:m.getPlayersName())
		{
			cout<<"Real     "<<e<<" time possession: "<<computeRealPossession(e)/pow(10,12)<<" seconds"<<endl;
		 	cout<<"Computed "<<e<<" time possession: "<<m.getPlayerBallPossession(e)/pow(10,12)<<" seconds"<<endl;
		}
		cout << "PERCENTAGE" <<endl;
		cout << "--------------------------------------------------------------------------" <<endl;
		for(auto &e:m.getPlayersName())
		{
			cout<<"Real     "<<e<<" possession percentage: "<<((computeRealPossession(e)/pow(10,12))/(double)realtot)*100<<"%"<<endl;
		 	cout<<"Computed "<<e<<" possession percentage: "<<((m.getPlayerBallPossession(e)/pow(10,12))/(double)calctot)*100<<"%"<<endl;
		}
		cout << "--------------------------------------------------------------------------" <<endl;
		cout << "Team A: "<<((m.getTeamBallPossession("Team A")/pow(10,12))/(double)calctot)*100<<"%"<<endl;
		cout << "Team B: "<<((m.getTeamBallPossession("Team B")/pow(10,12))/(double)calctot)*100<<"%"<<endl;
}

int main(int argc,char *argv[])
{
	int interval=30;
	double k=1;
	unsigned long int * startend = new unsigned long int[4];
	Parser initializator("files/field.csv");
	Field field = initializator.initialize_field();
	initializator.setFile("files/time.csv");
	startend = initializator.read_time();
	if(argc>=2)
		k=stod(argv[1]);
	if(argc>=3)
		interval=stoi(argv[2]);
	Match match(field,startend[0],startend[3],k);
	initializator.setFile("files/metadata.csv");
	initializator.initialize_match(match);
	initializator.setFile("files/1st Half.csv");
	vector<TimeInterval> intervals = initializator.parse_interval_file(startend[0]);
	initializator.setFile("files/2nd Half.csv");
	intervals.push_back(TimeInterval(startend[1],startend[2],true));
	vector<TimeInterval> intervals2 = initializator.parse_interval_file(startend[2]);
	intervals.insert(intervals.end(),intervals2.begin(),intervals2.end());
	initializator.setFile("files/full-game");
	initializator.setInterval(interval);
	cout<<"[INFO] K="<<k<<" T="<<interval<<endl;
	while(match.getCurrentTime()<=startend[3])
	{
		match.simulateMatch(initializator.parse_event_file(),intervals);
	}
	printStats(match);
}
