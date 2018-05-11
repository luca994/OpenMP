#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>
#include "event.h"
#include <vector>
#include "timeinterval.h"

class Parser{
public:
	Parser(std::string file_name, int interval);
	std::vector<Event> parse_event_file();
	std::vector<TimeInterval> parse_interval_file(unsigned long int beginMatch);
	~Parser();
	void setFile(std::string file_name);
private:
	std::ifstream infile;
	int interval;
	unsigned long int convertTime(std::string time);
};

#endif
