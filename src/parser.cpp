#include "parser.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int Parser::parse_file(string file_name){
	int end=1;
	ifstream infile;
	infile.open(file_name, ios::in);
	string data;
	while(end!=0){	
		std::getline(infile, data);
		cout<<data<<endl;
		cin>>end;
	}
}

