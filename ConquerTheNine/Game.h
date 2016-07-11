#ifndef GAME_H_
#define GAME_H_

#include "GameSaveManager.h"

class Game
{
private:
	GameSaveManager* saveManager_;
public:
	Game();
	virtual ~Game();
	void Init();
	void Exit();
	void Run();
	void New();
	void Load();
	void Save();
};

#endif // GAME_H_


