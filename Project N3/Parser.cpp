#include "Parser.h"

INI_Parser::INI_Parser(std::string file)
{
	std::ifstream File(file);
	if (!File.is_open())
	{
		throw std::runtime_error("Failed to open file");
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
	int i = 0;
	while (str[i] != ';')
	{
		strhelp += str[i];
		++i;
	}
	str = strhelp;
}



std::vector<std::vector<std::pair<std::string, std::string>>> INI_Parser::parsing(INI_Parser parser, std::ifstream File)
{
	std::vector<std::string> text;
	std::vector<std::vector<std::pair<std::string, std::string>>> answers(100, std::vector<std::pair<std::string, std::string>>(100));
	std::string line;
	int section;
	std::string num;
	while (std::getline(File, line))
	{
		text.push_back(line);
	}
	File.close();
	for (int i = 0; i < text.size(); ++i)
	{
		cut_out(text[i]);
		if (text[i][0] == '[')
		{
			for (int j = 0; j < text[i].size(); ++i)
			{
				if (text[i][j] > '0' && text[i][j] < '9')
				{
					num += text[i][j];
				}
			}
		}
		else
		{
			section = std::stoi(num);
			int value = 0;
			if (text[i][0] != ' ' && text[i][0] != ';')
			{
				int k = 0;
				for (int j = 0; j < text[i].size(); ++j)
				{
					if (text[i][j] = '=')
					{
						answers[section][value].first = trim(text[i], 0, j);
						answers[section][value].second = trim(text[i], j+1, text[i].size());
						value++;
					}
				}
			}
		}
	}
	return answers;
}

std::pair<std::string, std::string> INI_Parser::get_value(int section, int value)
{
	std::vector<std::vector<std::pair<std::string, std::string>>> answers = parsing();
	return answers[section][value];
}