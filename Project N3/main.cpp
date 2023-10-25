#include <iostream>
#include "Parser.h"

int main()
{
	INI_Parser parser("filename.txt");
	auto value = parser.get_value<int>("section2", "var1");
	std::cout << value;
	return 0;
}