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
    T get_value(std::string section, std::string value)
    {
        static_assert(sizeof(T) > 0, "not implemented type for get_value");
        try
        {
            T result;
            std::string answer = "Section or value doesn't exist!";
            for (const auto& pair : answers[section_in(section)])
            {
                if (pair.first == value)
                {
                    answer = pair.second;
                    break;
                }
            }
            if (std::is_same<T, int>::value)
            {
                result = std::stoi(answer);
            }
            else if (std::is_same<T, double>::value)
            {
                result = std::stod(answer);
            }
            return result;
        }
        catch (const std::exception&)
        {
            throw std::runtime_error("Type of value can't be given to your type");
        }
    }
    template<>
    std::string get_value(std::string section, std::string value)
    {
        std::string answer = "Section or value doesn't exist!";
        for (const auto& pair : answers[section_in(section)])
        {
            if (pair.first == value)
            {
                answer = pair.second;
                break;
            }
        }
        if (answer == "")
        {
            return "Empty value";
        }
        return answer;
    }
	INI_Parser(std::string file);
private:
    int section_in(std::string str);
    std::vector<std::vector<std::pair<std::string, std::string>>> answers;
	std::string trim(std::string str, int i, int j);
	void cut_out(std::string& str);
};