#include "Parser.h"

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
		answers.resize(20, std::vector<std::pair<std::string, std::string>>(20));
		std::string line;
		std::vector<int>valuevec(20,0);
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
		for (int i = 0; i < text.size(); ++i)
		{
			if (text[i][0] == '[')
			{
				section = section_in(text[i]);
			}
			else
			{
				if (text[i][0] != ' ' && text[i][0] != ';')
				{
					for (int j = 0; j < text[i].size(); ++j)
					{
						if (text[i][j] == '=')
						{
							answers[section][valuevec[section]].first = trim(text[i], 0, j);
							answers[section][valuevec[section]].second = trim(text[i], j + 1, text[i].size());
							valuevec[section]++;
						}
					}
				}
			}
		}
	}
}