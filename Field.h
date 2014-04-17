#ifndef FIELD_H
#define FIELD_H

#include "Player.h"
#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>

#pragma comment (lib, "winmm.lib")

typedef unsigned int Uint;

struct Entity {
	std::vector<int> X;
	std::vector<int> Y;
};

class Field
{
public:
	Field();

	void DrawMap(Player *grenade, int moves);

	bool MovePlayer(Player *player, int Key);
	bool MoveGrenade(Player *grenade, int Key);
	bool EntityMovable(Player *entity);
	bool Enemy(int moves, bool spread);

private:
	char _map[HEIGHT][WIDTH];
	int _moves;

	/*save all destroyed Fields here: */
	Entity _DestroyedFields;

	/*save all fields taken by the enemy here: */
	Entity _Enemys;

	/*Fields: */
	char _Player;
	char _Grenade;
	char _DestroyedField;
	char _Field;
	char _Enemy;

	bool _erase;
};

#endif
