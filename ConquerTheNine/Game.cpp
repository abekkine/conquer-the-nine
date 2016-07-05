#include "Game.h"

#include <iostream>
#include <exception>

#include "Display.h"

Game::Game()
{
	std::cout << "Game::Game()" << std::endl;
}

Game::~Game()
{
	std::cout << "Game::~Game()" << std::endl;
}

void Game::Init()
{
	std::cout << "Game::Init()" << std::endl;
	try
	{
		Display::Instance()->InitDisplay();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}

void Game::Exit()
{
	std::cout << "Game::Exit()" << std::endl;
}

void Game::Run()
{
	std::cout << "Game::Run()" << std::endl;

	Display::Instance()->Run();
}