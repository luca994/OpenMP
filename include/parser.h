#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>
#include "event.h"
#include "timeinterval.h"
#include "match.h"
#include <vector>

class Parser{
public:
	Parser(std::string file_name);
	Parser(std::string file_name, int interval);
	std::vector<Event> parse_event_file();
	std::vector<TimeInterval> parse_interval_file(unsigned long int beginMatch);
	void initialize_match(Match &match);
	Field initialize_field();
	unsigned long int * read_time();
	~Parser();
	void setFile(std::string file_name);
	void setInterval(int interv);
	unsigned long int convertTime(std::string time);
private:
	std::ifstream infile;
	int interval;
	unsigned long int lastEventTs;
};

#endif
