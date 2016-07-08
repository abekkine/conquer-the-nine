#ifndef GAME_STATE_H_
#define GAME_STATE_H_

#include <string>

#include "Game.h"

class GameState
{
public:
	typedef enum {
		gsNONE,
		gsMENU,
		gsINITGAME,
		gsLOADGAME,
		gsSAVEGAME,
		gsPLAY,
		gsPAUSE,
		gsSETTINGS,
		gsSAVESETTINGS,
		gsQUIT,
		gsTEST
	} GameStateType;

private:
	GameState();
	static GameState* instance_;
	GameStateType state_;
	Game* game_;

public:
	static GameState* Instance();
	~GameState();
	void OfGame(Game* game);
	GameStateType State();
	void State(GameStateType state);
	std::string StateName();
};

#endif // GAME_STATE_H_
