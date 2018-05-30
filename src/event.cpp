#include "event.h"

/**
*
*Constructor of class Event, initializes the sensor id, the timestamp (in picoseconds) and the position
*of the sensor for that event
*
*/
Event::Event(int sid,unsigned long int timestamp, Position actualPosition){
	this->sid=sid;
	this->timestamp=timestamp;
	position=actualPosition;
}

/**
*
*Returns the sensor id
*
*/
int Event::getSid(){
	return sid;
}

/**
*
*Returns the timestamp of the event (in picoseconds)
*
*/
unsigned long int Event::getTimestamp(){
	return timestamp;
}

/**
*
*Returns the position of the sensor of the event
*
*/
Position Event::getPosition(){
	return position;
}

/**
*
*Sets the position of the sensor of the event
*
*/
void Event::setPosition(Position pos){
	position=pos;
}

/**
*
*Sets the timestamp of the event (in picoseconds)
*
*/
void Event::setTimestamp(unsigned long int ts){
	timestamp=ts;
}

/**
*
*Sets the sensor id of the events
*
*/
void Event::setSid(int id){
	sid=id;
}
