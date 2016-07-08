#include "GameState.h"

GameState* GameState::instance_ = 0;

GameState::GameState()
{
	state_ = gsMENU;
	game_ = 0;
}

GameState* GameState::Instance()
{
	if (instance_ == 0)
	{
		instance_ = new GameState();
	}

	return instance_;
}

GameState::~GameState()
{
}

void GameState::OfGame(Game* game)
{
	game_ = game;
}

GameState::GameStateType GameState::State()
{
	return state_;
}

void GameState::State(GameState::GameStateType state)
{
	state_ = state;
}

std::string GameState::StateName()
{
	std::string name;
	switch (state_)
	{
	case gsNONE:
		name = "NONE"; break;
	case gsMENU:
		name = "MENU"; break;
	case gsPAUSE:
		name = "PAUSE"; break;
	case gsPLAY:
		name = "PLAY"; break;
	case gsQUIT:
		name = "QUIT"; break;
	case gsSETTINGS:
		name = "SETTINGS"; break;
	case gsTEST:
		name = "TEST"; break;
	case gsINITGAME:
		name = "INIT GAME"; break;
	case gsLOADGAME:
		name = "LOAD GAME"; break;
	case gsSAVEGAME:
		name = "SAVE GAME"; break;
	case gsSAVESETTINGS:
		name = "SAVE SETTINGS"; break;
	default:
		name = "---"; break;
	}

	return name;
}

void GameState::SelectContinue()
{
	// Load saved game and go to gsPLAY state.
	game_->Load();
	state_ = gsPLAY;
}

void GameState::SelectNewGame()
{
	state_ = gsPLAY;
}

void GameState::SelectSettings()
{
	state_ = gsSETTINGS;
}

void GameState::SelectPause()
{
	state_ = gsPAUSE;
}

void GameState::SelectResume()
{

}

void GameState::SelectQuit()
{

}

void GameState::SelectMenu()
{

}
