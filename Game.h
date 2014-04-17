#ifndef GAME_H
#define GAME_H

#include "Field.h"

class Game : public Field
{
public:
	Game();
	~Game();

	void Initialize();
	void GameRules();
	int GameLoop();
	int GetKey();
	bool restart(bool game_won);

private:
	Player *_player;
	Player *_grenade;
	Player *_enemy;

	int _moves_round;
	int _moves_total;
	bool _game_over;
	bool _game_won;
};

#endif
