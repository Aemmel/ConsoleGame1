#ifndef MAP_H
#define MAP_H

#include "Player.h"
#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>

#pragma comment (lib, "winmm.lib")

typedef unsigned int Uint;

class map
{
public:
	map();

	void DrawMap(Player *grenade, int moves);

	bool MovePlayer(Player *player);
	bool MoveGrenade(Player *grenade);
	bool EntityMovable(Player *entity);
	bool Enemy(int moves);

private:
	char _map[HEIGHT][WIDTH];
	int _moves;

	/*save all destroyed Fields here: */
	std::vector<int>_DestroyedFieldsX;
	std::vector<int>_DestroyedFieldsY;

	/*save all fields taken by the enemy here: */
	std::vector<int>_EnemysX;
	std::vector<int>_EnemysY;

	/*Fields: */
	char _Player;
	char _Grenade;
	char _DestroyedField;
	char _Field;
	char _Enemy;
};

#endif
