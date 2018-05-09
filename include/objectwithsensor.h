#ifndef OBJ_SENS_H_
#define OBJ_SENS_H_
#include <list>
#include <string>
#include <memory>

class ObjectWithSensor{
public:
  virtual std::string getType() const=0;
  std::list<int> getSid()
  {
    return sids;
  }
private:
  std::list<int> sids;
};
#endif
