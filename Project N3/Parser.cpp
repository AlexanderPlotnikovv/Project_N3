#include "Parser.h"

const std::type_info& is_T(const std::string& s) {
	try {
		std::stoi(s);
	}
	catch (const std::invalid_argument&) {
		try
		{
			std::stod(s);
		}
		catch (const std::invalid_argument&) {

		}
	}
	return typeid(s);
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

INI_Parser::INI_Parser(std::string file)
{
	std::ifstream File(file);
	if (!File.is_open())
	{
		throw std::runtime_error("Failed to open file");
	}
	else
	{
		std::vector<std::string> text;
		answers.resize(100, std::vector<std::pair<std::string, std::string>>(100));
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
					if (text[i][j] >= '0' && text[i][j] <= '9')
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

template<typename T>
T INI_Parser::get_value(int section)
{
	try
	{
		T result;
		for (int i = 0; i < answers[section].size(); ++i)
		{
			auto s = is_T(answers[section][i].second);
			if (std::is_same<typeid(s), T>::result)
			{
				result = s;
				break;
			}
		}
		return result;
	}
	catch (const std::invalid_argument&)
	{
		std::runtime_error("We can't find value with this type in this section");
	}
}