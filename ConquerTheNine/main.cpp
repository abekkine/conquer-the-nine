#include <iostream>

#include "Exception.h"
#include "ConquerTheNine.h"

int main(void)
{
	std::cout << "Conquer The Nine!" << std::endl;
	ConquerTheNine* game = new ConquerTheNine();

	try {
		game->Init();
		game->Run();
		game->Exit();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}