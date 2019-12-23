#include <iostream>
#include "Application.h"

int main()
{
	try
	{
		Application app;
		app.run();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION : " << e.what() << std::endl;
		std::cin.get();

		return EXIT_FAILURE;
	}
}