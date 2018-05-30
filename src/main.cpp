#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <time.h>
#include "position.h"
#include "field.h"
#include "parser.h"
#include "match.h"

using namespace std;

/**
*
*Computes the ball possession of player with playerName as name
*using the data from the possession files (possesion already computed elsewhere)
*
*/
unsigned long int computeRealPossession(string playerName){
	unsigned long int totTimePoss=0;
	string filename1 = "files/possession1st/"+playerName+".csv";
	string filename2 = "files/possession2nd/"+playerName+".csv";
	Parser pPoss1(filename1);
	Parser pPoss2(filename2);
	vector<TimeInterval> tposs;
	tposs = pPoss1.parse_interval_file(0);
	for(auto &i: tposs){
		totTimePoss+=(i.getEnd()-i.getStart());
	}
	tposs = pPoss2.parse_interval_file(0);
	for(auto &i: tposs){
		totTimePoss+=(i.getEnd()-i.getStart());
	}
	return totTimePoss;
}

/**
*
*Prints the statistics of the players and of the teams (both real and computed) related to the match taken as input to stdout
*
*/
void printStats(Match & m){
	float realtot=0,calctot=0;
	for(auto &e:m.getPlayersName()){
		realtot+=computeRealPossession(e)/pow(10,12);
		calctot+=m.getPlayerBallPossession(e)/pow(10,12);
	}
	for(auto &e:m.getPlayersName()){
		cout<<"Real     "<<e<<" time possession: "<<computeRealPossession(e)/pow(10,12)<<" seconds"<<endl;
	 	cout<<"Computed "<<e<<" time possession: "<<m.getPlayerBallPossession(e)/pow(10,12)<<" seconds"<<endl;
	}
	cout << "PERCENTAGE" <<endl;
	cout << "--------------------------------------------------------------------------" <<endl;
	for(auto &e:m.getPlayersName()){
		cout<<"Real     "<<e<<" possession percentage: "<<((computeRealPossession(e)/pow(10,12))/(double)realtot)*100<<"%"<<endl;
	 	cout<<"Computed "<<e<<" possession percentage: "<<((m.getPlayerBallPossession(e)/pow(10,12))/(double)calctot)*100<<"%"<<endl;
	}
	cout << "--------------------------------------------------------------------------" <<endl;
	cout << "Team A: "<<((m.getTeamBallPossession("Team A")/pow(10,12))/(double)calctot)*100<<"%"<<endl;
	cout << "Team B: "<<((m.getTeamBallPossession("Team B")/pow(10,12))/(double)calctot)*100<<"%"<<endl;
}

/**
*
*Main methods that initializes the match and the fields and takes the data by parsing all the files.
*Call simulateMatch of the class Match each interval time T. Take as argv the maximumDistanceFromTheBall
*and the interval T. It prints also the statistics of the ball possession.
*
*/
int main(int argc,char *argv[]){
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
	vector<Event> events;
	time_t timer1,timer2;
	if(argc>=4){
		cout<<"[INFO] K="<<k<<" parsing all the events..."<<endl;
		initializator.setInterval(1);
		initializator.parse_event_file();
		initializator.setInterval(100000);
		events = initializator.parse_event_file();
		time(&timer1);
//		int user;
//		cout<<"Parsed file: press 1 to continue ";
//		cin>>user;
//		if(user==1)
		match.simulateMatch(events,intervals);
		time(&timer2);
		cout<<"Execution time: "<<timer2-timer1<<" s"<<endl;
	}
	else{
		initializator.setInterval(interval);
		cout<<"[INFO] K="<<k<<" T="<<interval<<endl;
		while(match.getCurrentTime()<=match.getEndTime()){
			events = initializator.parse_event_file();
			time(&timer1);
			match.simulateMatch(events,intervals);
			time(&timer2);
		}
	}
	printStats(match);
	cout<<"Execution time: "<<timer2-timer1<<" s"<<endl;
}
