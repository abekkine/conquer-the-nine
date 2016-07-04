#include <stdio.h>

#include "ConquerTheNine.h"

int main(void)
{
	puts("Conquer The Nine!");
	ConquerTheNine* game = new ConquerTheNine();

	game->Init();
	game->Run();
	game->Exit();

	return 0;
}