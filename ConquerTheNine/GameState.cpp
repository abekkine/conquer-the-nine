#include "GameState.h"

#include <iostream>

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
	PreProcess();

	state_ = state;

	PostProcess();
}

void GameState::PreProcess()
{
	// TODO : Tasks before leaving the state.
}

void GameState::PostProcess()
{
	// TODO : Tasks after setting the state.
	switch (state_)
	{
	case gsINITGAME:
		State(gsPLAY);
		break;
	case gsLOADGAME:
		break;
	case gsSAVEGAME:
		game_->Save();
		State(gsMENU);
		break;
	case gsPAUSE:
		break;
	case gsSAVESETTINGS:
		break;
	}
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

