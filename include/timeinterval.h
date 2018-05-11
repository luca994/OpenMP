#ifndef TINTERV_H_
#define TINTERV_H_

class TimeInterval{
public:
  TimeInterval(unsigned long int start,unsigned long int end,bool pause);
  bool isInPause(unsigned long int timestamp);
  void setStart(unsigned long int s);
  void setEnd(unsigned long int e);
  unsigned long int getStart();
  unsigned long int getEnd();
private:
  unsigned long int start;
  unsigned long int end;
  bool pause;
};
#endif
