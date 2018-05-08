#ifndef EVENT_H_
#define EVENT_H_
#include "position.h"

class Event {
public:
  Event(int sid,unsigned long int timestamp, Position actualPosition);
  int getSid();
  unsigned long int getTimestamp();
  Position getPosition();
  void setSid(int id);
  void setTimestamp(unsigned long int ts);
  void setPosition(Position pos);
private:
  int sid;
  Position position;
  unsigned long int timestamp;
  double speed;
  double speedX;
  double speedY;
  double speedZ;
  double acceleration;
  double accelerationX;
  double accelerationY;
  double accelerationZ;
};
#endif
