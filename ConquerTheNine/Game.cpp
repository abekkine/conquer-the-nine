#include "Game.h"

#include <iostream>

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
}

void Game::Exit()
{
	std::cout << "Game::Exit()" << std::endl;
}

void Game::Run()
{
	std::cout << "Game::Run()" << std::endl;
}