#pragma once

#include <fstream>
#include <iostream>
#include <algorithm>

#include <vector>
#include <list>
#include <map>
#include <set>
#include <string>

#include <stdexcept>

class INI_Parser
{
public:
	INI_Parser(std::string file);

	std::string trim(std::string str, int i, int j);

	void cut_out(std::string& str);
	
	std::vector<std::vector<std::pair<std::string, std::string>>> parsing(INI_Parser parser, std::ifstream File);

	template<class T>
	T get_value(int section, int value);
};