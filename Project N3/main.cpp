#include <iostream>
#include "Parser.h"
#include <iomanip>

int main()
{
	try
	{
		INI_Parser parser("filename.txt");
		auto value = parser.get_value<double>("section1", "var1");
		if (typeid(value) == typeid(double) && static_cast<int>(value) == value)
		{
			std::cout << std::fixed << std::setprecision(1) << value;
		}
		else
		{
			std::cout << value;
		}
	}
	catch (const std::exception&)
	{
		std::cerr << "Some mistake!";
	}
	return 0;
}