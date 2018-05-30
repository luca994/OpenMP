#include "timeinterval.h"

/**
*
*Constructor of the TimeIntervak class.
*Takes as input the begin and the end of the interval (in picoseconds) and a boolean pause that is true
*if the game during this interval is in pause.
*
*/
TimeInterval::TimeInterval(unsigned long int start,unsigned long int end,bool pause){
	this->start=start;
	this->end=end;
	this->pause=pause;
}

/**
*
*Takes as input the timestamp (in picoseconds) to check.
*Returns true if the timestamp belongs to this interval and the game
*during this interval is in pause, false otherwise
*
*/
bool TimeInterval::isInPause(unsigned long int timestamp){
  if(timestamp>=start && (timestamp<=end || end==0) && pause)
    return true;
  else
    return false;
}

/**
*
*Sets the timestamp of the begin of the interval to the value taken as input (in picoseconds)
*
*/
void TimeInterval::setStart(unsigned long int s){
  start=s;
}

/**
*
*Sets the timestamp of the end of the interval to the value taken as input (in picoseconds)
*
*/
void TimeInterval::setEnd(unsigned long int e){
  end=e;
}

/**
*
*Returns the timestamp of the begin of the interval in picoseconds
*
*/
unsigned long int TimeInterval::getStart(){
	return start;
}

/**
*
*Returns the timestamp of the end of the interval in picoseconds
*
*/
unsigned long int TimeInterval::getEnd(){
	return end;
}
