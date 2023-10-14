#include "Parser.h"

template<typename T>
T INI_Parser::get_value(std::string section, std::string value)
{
	try
	{
		T result;
		std::string answer;
		for (int i = 0; i < answers[section_in(section)].size(); ++i)
		{
			if (answers[section_in(section)][i].first == value)
			{
				answer = answers[section_in(section)][i].second;
			}
		}
		if (std::is_same<int, T>)
		{
			result = std::stoi(answer);
		}
		else if (std::is_same<double, T>) {
			result = std::stod(answer);
		}
		else if (std::is_same<std::string, T>) {
			result = answer;
		}
	}
	catch
	{
		std::cout << "Type of value doesn't match type which you entered or type doesn't exist"
	}
}

std::string INI_Parser::trim(std::string str, int i, int j)
{
	std::string strhelp = "";
	for (int h = i; h < j; ++h)
	{
		if (str[h] != ' ')
		{
			strhelp += str[h];
		}
	}
	return strhelp;
}

void INI_Parser::cut_out(std::string& str)
{
	std::string strhelp = "";
	for (int i = 0; i < str.size(); ++i)
	{
		if (str[i] == ';')
		{
			break;
		}
		if (static_cast<int>(str[i]) > 0)
		{
			strhelp += str[i];
		}
	}
	str = strhelp;
}

int INI_Parser::section_in(std::string str)
{
	std::string strhelp = "";
	for (int i = 0; i < str.size(); ++i)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			strhelp += str[i];
		}
	}
	return std::stoi(strhelp);
}

INI_Parser::INI_Parser(std::string file)
{
	std::ifstream File(file);
	if (!File.is_open())
	{
		throw std::runtime_error("Failed to open file");
	}
	else
	{
		std::vector <std::string> text;
		answers.resize(100, std::vector<std::pair<std::string, std::string>>(100));
		std::string line;
		int section;
		while (std::getline(File, line))
		{
			text.push_back(line);
		}
		File.close();
		for (int i = 0; i < text.size(); ++i)
		{
			cut_out(text[i]);
		}
		for (auto elem : text) {
			for (auto txt : elem)
			{
				std::cout << txt;
			}
			std::cout << std::endl;
		}
		//std::cout << static_cast<int>(text[0][0]) << std::endl;
		for (int i = 0; i < text.size(); ++i)
		{
			if (text[i][0] == '[')
			{
				section = section_in(text[i]);
			}
			else
			{
				int value = 0;
				if (text[i][0] != ' ' && text[i][0] != ';')
				{
					int k = 0;
					for (int j = 0; j < text[i].size(); ++j)
					{
						if (text[i][j] == '=')
						{
							answers[section][value].first = trim(text[i], 0, j);
							answers[section][value].second = trim(text[i], j + 1, text[i].size());
							value++;
						}
					}
				}
			}
		}
		
	}
}