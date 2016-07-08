#ifndef GAME_H_
#define GAME_H_

class Game
{
public:
	Game();
	virtual ~Game();
	void Init();
	void Exit();
	void Run();
	void Load();
	void Save();
};

#endif // GAME_H_


