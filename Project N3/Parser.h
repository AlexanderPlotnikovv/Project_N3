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
	template<class T>
	T get_value(std::string section, std::string value);
	int section_in(std::string str);
	std::vector<std::vector<std::pair<std::string, std::string>>> answers;
	INI_Parser(std::string file);

	std::string trim(std::string str, int i, int j);

	void cut_out(std::string& str);

};