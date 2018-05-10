#include "event.h"

Event::Event(int sid,unsigned long int timestamp, Position actualPosition)
{
  this->sid=sid;
  this->timestamp=timestamp;
  position=actualPosition;
}

int Event::getSid()
{
  return sid;
}

unsigned long int Event::getTimestamp()
{
  return timestamp;
}

Position Event::getPosition()
{
    return position;
}

void Event::setPosition(Position pos)
{
  position=pos;
}

void Event::setTimestamp(unsigned long int ts)
{
  timestamp=ts;
}

void Event::setSid(int id)
{
  sid=id;
}
