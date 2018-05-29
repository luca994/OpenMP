#include "timeinterval.h"

TimeInterval::TimeInterval(unsigned long int start,unsigned long int end,bool pause){
this->start=start;
this->end=end;
this->pause=pause;
}

bool TimeInterval::isInPause(unsigned long int timestamp){
  if(timestamp>=start && (timestamp<=end || end==0) && pause)
    return true;
  else
    return false;
}

void TimeInterval::setStart(unsigned long int s){
  start=s;
}

void TimeInterval::setEnd(unsigned long int e){
  end=e;
}

unsigned long int TimeInterval::getStart(){
	return start;
}

unsigned long int TimeInterval::getEnd(){
	return end;
}
