#include <iostream>
#include "Parser.h"

int main()
{
	INI_Parser parser("filename.txt");
	auto value = parser.get_value<int>("Section2", "var1");
	std::cout << value;
	return 0;
}