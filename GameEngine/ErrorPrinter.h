#pragma once

#include<iostream>

namespace errorPrinter
{
	void error(const char* message)
	{
		std::cout << "ERROR :: " << message << "\n";
		exit(EXIT_FAILURE);
	}
}