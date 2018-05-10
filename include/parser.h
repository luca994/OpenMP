#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>
#include "event.h"
#include <vector>

class Parser{
public:
	Parser(std::string file_name, int interval);
	std::vector<Event> parse_file();
	~Parser();
private:
	std::ifstream infile;
	int interval;
};

#endif
