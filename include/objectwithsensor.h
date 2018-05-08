#ifndef OBJ_SENS_H_
#define OBJ_SENS_H_
#include <list>
#include <string>

class ObjectWithSensor{
public:
  virtual std::string getType()=0;
private:
  std::list<int> sids;
};
#endif
