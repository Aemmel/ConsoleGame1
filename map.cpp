#include "map.h"

map::map()
{
	_Player = '@';
	_Grenade = '*';
	_DestroyedField = 'X';
	_Enemy = 'O';

	_Field = '-';

	for (int y = 0; y < HEIGHT; y++){
		for (int x = 0; x < WIDTH; x++){
			_map[y][x] = _Field;
		}
	}
}

void map::DrawMap(Player *grenade, int moves)
{
	for(Uint it = 0; it != _DestroyedFieldsY.size() && it != _DestroyedFieldsX.size(); ++it){
		_map[_DestroyedFieldsY[it]][_DestroyedFieldsX[it]] = _DestroyedField;
	}

	if(moves > 5){
		for (Uint it = 0; it < _EnemysY.size(); ++it){
			_map[_EnemysY[it]][_EnemysX[it]] = _Enemy;
		}
	}

	int PosGreX = grenade->get_X_Cor();
	int PosGreY = grenade->get_Y_Cor();
	_map[PosGreY][PosGreX] = _Grenade;

	for (int y = 0; y<HEIGHT; y++){
		for (int x = 0; x<WIDTH; x++){
			std::cout << _map[y][x];
		}
		std::cout << std::endl;
	}
}

bool map::MovePlayer(Player *player)
{
	int PosPlayerX = player->get_X_Cor();
	int PosPlayerY = player->get_Y_Cor();
	int PosGreX = PosPlayerX;
	int PosGreY = PosPlayerY;
	bool FieldBroken = false;

	_map[PosPlayerY][PosPlayerX] = _Player;

	//move up:
	if (GetAsyncKeyState('W') && PosPlayerY > 0 && _map[PosGreY -1][PosGreX] != _Grenade){
		for(Uint it = 0; it < _DestroyedFieldsY.size() && it < _DestroyedFieldsX.size(); ++it){
				if(PosPlayerY -1 == _DestroyedFieldsY[it] && PosPlayerX == _DestroyedFieldsX[it]){
					FieldBroken = true;
					break;
				}
		}

		if (!FieldBroken){
			_map[PosPlayerY][PosPlayerX] = _Field;
			PosPlayerY--;
			_map[PosPlayerY][PosPlayerX] = _Player;
			player->set_Y_Cor(PosPlayerY);
			return true;
		}
		FieldBroken = false;
	}
	//move down:
	if (GetAsyncKeyState('S') && PosPlayerY < HEIGHT -1 && _map[PosGreY +1][PosGreX] != _Grenade){
		for(Uint it = 0; it<_DestroyedFieldsY.size() && it < _DestroyedFieldsX.size(); ++it){
				if(PosPlayerY +1 == _DestroyedFieldsY[it] && PosPlayerX == _DestroyedFieldsX[it]){
					FieldBroken = true;
					break;
			}
		}

		if(!FieldBroken){
			_map[PosPlayerY][PosPlayerX] = _Field;
			PosPlayerY++;
			_map[PosPlayerY][PosPlayerX] = _Player;
			player->set_Y_Cor(PosPlayerY);
			return true;
		}
		FieldBroken = false;
	}
	//move right:
	if (GetAsyncKeyState('D') && PosPlayerX < WIDTH -1 && _map[PosGreY][PosGreX +1] != _Grenade){
		for(Uint it = 0; it<_DestroyedFieldsY.size() && it < _DestroyedFieldsX.size(); ++it){
				if(PosPlayerY == _DestroyedFieldsY[it] && PosPlayerX +1 == _DestroyedFieldsX[it]){
					FieldBroken = true;
					break;
			}
		}

		if(!FieldBroken){
			_map[PosPlayerY][PosPlayerX] = _Field;
			PosPlayerX++;
			_map[PosPlayerY][PosPlayerX] = _Player;
			player->set_X_Cor(PosPlayerX);
			return true;
		}
		FieldBroken = false;
	}
	//move left:
	if (GetAsyncKeyState('A') && PosPlayerX > 0 && _map[PosGreY][PosGreX -1] != _Grenade){
		for(Uint it = 0; it<_DestroyedFieldsY.size() && it < _DestroyedFieldsX.size(); ++it){
				if(PosPlayerY == _DestroyedFieldsY[it] && PosPlayerX -1 == _DestroyedFieldsX[it]){
					FieldBroken = true;
					break;
			}
		}

		if(!FieldBroken){
			_map[PosPlayerY][PosPlayerX] = _Field;
			PosPlayerX--;
			_map[PosPlayerY][PosPlayerX] = _Player;
			player->set_X_Cor(PosPlayerX);
			return true;
		}
		FieldBroken = false;
	}

	return false;
}

bool map::MoveGrenade(Player *grenade)
{
	int PosGrenadeX = grenade->get_X_Cor();
	int PosGrenadeY = grenade->get_Y_Cor();
	int PosPlayX = PosGrenadeX;
	int PosPlayY = PosGrenadeY;

	_map[PosGrenadeY][PosGrenadeX] = _Grenade;

	//move up:
	if (GetAsyncKeyState(VK_UP) && PosGrenadeY > 0 && _map[PosPlayY -1][PosPlayX] != _Player){
		_map[PosGrenadeY][PosGrenadeX] = _Field;
		PosGrenadeY--;
		_map[PosGrenadeY][PosGrenadeX] = _Grenade;
		grenade->set_Y_Cor(PosGrenadeY);
		return false;
	}
	//move down:
	if (GetAsyncKeyState(VK_DOWN) && PosGrenadeY < HEIGHT -1 && _map[PosPlayY +1][PosPlayX] != _Player){
		_map[PosGrenadeY][PosGrenadeX] = _Field;
		PosGrenadeY++;
		_map[PosGrenadeY][PosGrenadeX] = _Grenade;
		grenade->set_Y_Cor(PosGrenadeY);
		return false;
	}
	//move right:
	if (GetAsyncKeyState(VK_RIGHT) && PosGrenadeX < WIDTH -1 && _map[PosPlayY][PosPlayX +1] != _Player){
		_map[PosGrenadeY][PosGrenadeX] = _Field;
		PosGrenadeX++;
		_map[PosGrenadeY][PosGrenadeX] = _Grenade;
		grenade->set_X_Cor(PosGrenadeX);
		return false;
	}
	//move left:
	if (GetAsyncKeyState(VK_LEFT) && PosGrenadeX > 0 && _map[PosPlayY][PosPlayX -1] != _Player){
		_map[PosGrenadeY][PosGrenadeX] = _Field;
		PosGrenadeX--;
		_map[PosGrenadeY][PosGrenadeX] = _Grenade;
		grenade->set_X_Cor(PosGrenadeX);
		return false;
	}

	bool FieldBroken = false;
	int PosDestroyedFieldX = PosGrenadeX;
	int PosDestroyedFieldY = PosGrenadeY;

	//destroy field:
	if(GetAsyncKeyState(VK_SPACE)){
		for(Uint it = 0; it<_DestroyedFieldsY.size() && it < _DestroyedFieldsX.size(); ++it){
				if(PosDestroyedFieldY == _DestroyedFieldsY[it] && PosDestroyedFieldX == _DestroyedFieldsX[it]){
					FieldBroken = true;
					break;
				}
		}

		if (!FieldBroken){
			_DestroyedFieldsX.push_back(PosDestroyedFieldX);
			_DestroyedFieldsY.push_back(PosDestroyedFieldY);

			//set grenade over, under, left or right of the destroyed field: 
			PosPlayX = grenade->get_X_Cor();
			PosPlayY = grenade->get_Y_Cor();
			//left, if end of the map on Y-and X-axis AND the player is above: 
			if (PosGrenadeY == HEIGHT -1 && PosGrenadeX == WIDTH -1 && _map[PosPlayY -1][PosPlayX] == _Player){
				PosGrenadeX--;
				_map[PosGrenadeY][PosGrenadeX] = _Grenade;
				grenade->set_X_Cor(PosGrenadeX);
			}
			//right, if end of the map on Y-axis AND the player is above: 
			else if(PosGrenadeY == HEIGHT -1 && _map[PosPlayY -1][PosPlayX] == _Player){
				PosGrenadeX++;
				_map[PosGrenadeY][PosGrenadeX] = _Grenade;
				grenade->set_X_Cor(PosGrenadeX);
			}
			//up, if end of the map on Y-axis: 
			else if(PosGrenadeY == HEIGHT -1){
				PosGrenadeY--;
				_map[PosGrenadeY][PosGrenadeX] = _Grenade;
				grenade->set_Y_Cor(PosGrenadeY);
			}
			//right, if beginning of the map on Y-and X-axis AND player is below: 
			else if(PosGrenadeY == 0 && PosGrenadeX == 0 && _map[PosPlayY +1][PosPlayX] == _Player){
				PosGrenadeX++;
				_map[PosGrenadeY][PosGrenadeX] = _Grenade;
				grenade->set_X_Cor(PosGrenadeX);
			}
			//left, if beginning of the map on Y-axis AND player is below:
			else if(PosGrenadeY == 0 && _map[PosPlayY +1][PosPlayX] == _Player){
				PosGrenadeX--;
				_map[PosGrenadeY][PosGrenadeX] = _Grenade;
				grenade->set_X_Cor(PosGrenadeX);
			}
			//up, if player is below:
			else if(_map[PosPlayY +1][PosPlayX] == _Player){
				PosGrenadeY--;
				_map[PosGrenadeY][PosGrenadeX] = _Grenade;
				grenade->set_Y_Cor(PosGrenadeY);
			}
			//down, if below is free:
			else {
				PosGrenadeY++;
				_map[PosGrenadeY][PosGrenadeX] = _Grenade;
				grenade->set_Y_Cor(PosGrenadeY);
			}

			return true;
		}
		FieldBroken = false;
	}
	return false;
}

bool map::EntityMovable(Player *entity)
{
	int PosEntX = entity->get_X_Cor();
	int PosEntY = entity->get_Y_Cor();

	//check corners:
	if (PosEntY == 0 && PosEntX == 0){
		bool B1, B2;	//These variables are responsible, to check if the fields are destroyed(each for one field), they are only valid in the respective if-statement
		for (Uint it = 0; it<_DestroyedFieldsY.size() && it < _DestroyedFieldsX.size(); ++it){
			if (PosEntY +1 == _DestroyedFieldsY[it] && PosEntX == _DestroyedFieldsX[it]){
				B1 = true;
			}
			if (PosEntY == _DestroyedFieldsY[it] && PosEntX +1 == _DestroyedFieldsX[it]){
				B2 = true;
			}
		}
		if(B1 && B2) 
			return false;
	}
	else if (PosEntY == 0 && PosEntX == WIDTH -1){
		bool B1, B2;
		for (Uint it = 0; it<_DestroyedFieldsY.size() && it < _DestroyedFieldsX.size(); ++it){
			if(PosEntY +1 == _DestroyedFieldsY[it] && PosEntX == _DestroyedFieldsX[it]){
				B1 = true;
			}
			if (PosEntY == _DestroyedFieldsY[it] && PosEntX -1 == _DestroyedFieldsX[it]){
				B2 = true;
			}
		}
		if (B1 && B2)
			return false;
	}
	else if (PosEntY == HEIGHT -1 && PosEntX == 0){
		bool B1, B2;
		for (Uint it = 0; it<_DestroyedFieldsY.size() && it < _DestroyedFieldsX.size(); ++it){
			if(PosEntY -1 == _DestroyedFieldsY[it] && PosEntX == _DestroyedFieldsX[it]){
				B1 = true;
			}
			if (PosEntY == _DestroyedFieldsY[it] && PosEntX +1 == _DestroyedFieldsX[it]){
				B2 = true;
			}
		}
		if(B1 && B2)
			return false;
	}
	else if (PosEntY == HEIGHT -1 && PosEntX == WIDTH -1){
		bool B1, B2;
		for (Uint it = 0; it<_DestroyedFieldsY.size() && it < _DestroyedFieldsX.size(); ++it){
			if(PosEntY -1 == _DestroyedFieldsY[it] && PosEntX == _DestroyedFieldsX[it]){
				B1 = true;
			}
			if (PosEntY == _DestroyedFieldsY[it] && PosEntX -1 == _DestroyedFieldsX[it]){
				B2 = true;
			}
		}
		if(B1 && B2)
			return false;
	}

	//check borders:
	else if (PosEntY == 0){
		bool B1, B2, B3;
		for (Uint it = 0; it<_DestroyedFieldsY.size() && it < _DestroyedFieldsX.size(); ++it){
			if(PosEntY +1 == _DestroyedFieldsY[it] && PosEntX == _DestroyedFieldsX[it]){
				B1 = true;	
			}
			if (PosEntY == _DestroyedFieldsY[it] && PosEntX +1 == _DestroyedFieldsX[it]){
				B2 = true;
			}
			if (PosEntY == _DestroyedFieldsY[it] && PosEntX -1 == _DestroyedFieldsX[it]){
				B3 = true;
			}
		}
		if(B1 && B2 && B3)
			return false;
	}
	else if (PosEntY == HEIGHT -1){
		bool B1, B2, B3;
		for (Uint it = 0; it<_DestroyedFieldsY.size() && it < _DestroyedFieldsX.size(); ++it){
			if(PosEntY -1 == _DestroyedFieldsY[it] && PosEntX == _DestroyedFieldsX[it]){
				B1 = true;
			}
			if (PosEntY == _DestroyedFieldsY[it] && PosEntX +1 == _DestroyedFieldsX[it]){
				B2 = true;
			}
			if (PosEntY == _DestroyedFieldsY[it] && PosEntX -1 == _DestroyedFieldsX[it]){
				B3 = true;
			}
		}
		if (B1 && B2 && B3)
			return false;
	}
	else if (PosEntX == 0){
		bool B1, B2, B3;
		for (Uint it = 0; it<_DestroyedFieldsY.size() && it < _DestroyedFieldsX.size(); ++it){
			if(PosEntY -1 == _DestroyedFieldsY[it] && PosEntX == _DestroyedFieldsX[it]){
				B1 = true;
			}
			if (PosEntY +1 == _DestroyedFieldsY[it] && PosEntX == _DestroyedFieldsX[it]){
				B2 = true;
			}
			if (PosEntY == _DestroyedFieldsY[it] && PosEntX +1 == _DestroyedFieldsX[it]){
				B3 = true;
			}
		}
		if (B1 && B2 && B3)
			return false;
	}
	else if (PosEntX == WIDTH -1){
		bool B1, B2, B3;
		for (Uint it = 0; it<_DestroyedFieldsY.size() && it < _DestroyedFieldsX.size(); ++it){
			if(PosEntY -1 == _DestroyedFieldsY[it] && PosEntX == _DestroyedFieldsX[it]){
				B1 = true;
			}
			if (PosEntY +1 == _DestroyedFieldsY[it] && PosEntX == _DestroyedFieldsX[it]){
				B2 = true;
			}
			if (PosEntY == _DestroyedFieldsY[it] && PosEntX -1 == _DestroyedFieldsX[it]){
				B3 = true;
			}
		}
		if (B1 && B2 && B3)
			return false;
	}
	//check middle:
	else {
		bool B1, B2, B3, B4;
		for (Uint it = 0; it<_DestroyedFieldsY.size() && it < _DestroyedFieldsX.size(); ++it){
			if(PosEntY -1 == _DestroyedFieldsY[it] && PosEntX == _DestroyedFieldsX[it]){
				B1 = true;
			}
			if (PosEntY +1 == _DestroyedFieldsY[it] && PosEntX == _DestroyedFieldsX[it]){
				B2 = true;
			}
			if (PosEntY == _DestroyedFieldsX[it] && PosEntX -1 == _DestroyedFieldsX[it]){
				B3 = true;
			}
			if (PosEntY == _DestroyedFieldsY[it] && PosEntX +1 == _DestroyedFieldsX[it]){
				B4 = true;
			}
		}
		if (B1 && B2 && B3 && B4)
			return false;
	}

	return true;
}

bool map::Enemy(int moves)
{
	_moves = moves;
	std::cout << _moves << "  " << moves << "\n\n";
	for (Uint itE = 0; itE < _EnemysY.size(); ++itE){
		for (Uint it = 0; it<_DestroyedFieldsY.size() && it < _DestroyedFieldsX.size(); ++it){
			if (_EnemysY[itE] == _DestroyedFieldsY[it] && _EnemysX[itE] == _DestroyedFieldsX[it]){
				_EnemysY.erase(_EnemysY.begin()+(itE-1));
				_EnemysX.erase(_EnemysX.begin()+(itE-1));
			}
		}
	}

	if(moves == 0){
		int randomNum1 = (rand() % HEIGHT)+1;
		int randomNum2 = (rand() % WIDTH)+1;
		std::cout << "randomNum1: " << randomNum1 << " randomNum2: " << randomNum2 << std::endl;
		_EnemysY.push_back(randomNum1);
		_EnemysX.push_back(randomNum2);
	}

	std::cout << "EnemysX[1]: " << _EnemysX[0] << " EnemysY[1]: " << _EnemysY[0] << std::endl;

	if (moves > 3){
		_EnemysX.push_back(12);

		std::cout << "X1: " << _EnemysX.at(0) << " X2: " << _EnemysX.at(1) << std::cout << " Y: " << _EnemysY.at(0) << std::endl;

		//save Enemys at the border here (those who can move)
		std::vector<int> topX;
		std::vector<int> topY;
		std::vector<int> botX;
		std::vector<int> botY;
		std::vector<int> rigX;
		std::vector<int> rigY;
		std::vector<int> lefX;
		std::vector<int> lefY;

		for (Uint it = 0; it < _EnemysY.size(); it++){			
			std::cout << "sizeof _EnemysX: " << _EnemysX.size() << std::endl;
			Sleep(1000);

			std::cout << "X1: " << _EnemysX.at(0) << " X2: " << _EnemysX.at(1) << std::cout << " Y: " << _EnemysY.at(it) << std::endl;
			Sleep(2000);
			if (_map[_EnemysY[it]-1][_EnemysX[it]] == _Grenade || _map[_EnemysY[it]-1][_EnemysX[it]] == _Field){
				topY.push_back(_EnemysY[it]);
				topX.push_back(_EnemysX[it]);
			}
			if (_map[_EnemysY[it]+1][_EnemysX[it]] == _Grenade || _map[_EnemysY[it]+1][_EnemysX[it]] == _Field){
				botY.push_back(_EnemysY[it]);
				botX.push_back(_EnemysX[it]);
			}
			if (_map[_EnemysY[it]][_EnemysX[it]-1] == _Grenade || _map[_EnemysY[it]][_EnemysX[it]-1] == _Field){
				lefX.push_back(_EnemysX[it]);
				lefY.push_back(_EnemysY[it]);
			}
			if (_map[_EnemysY[it]][_EnemysX[it]+1] == _Grenade || _map[_EnemysY[it]][_EnemysX[it]+1] == _Field){
				rigX.push_back(_EnemysX[it]);
				rigY.push_back(_EnemysY[it]);
			}
			std::cout << "X: " << _EnemysX[it] << std::cout << " Y: " << _EnemysY[it] << std::endl;
			Sleep(2000);
		}


		for (;;){
			int ranDir = (rand() % 4)+1;
			std::cout << "ranDir:" << ranDir << std::endl;
			Sleep(500);
			if (ranDir == 1 && !topY.empty()){
				int temp = (rand() % topY.size())+1;
				std::cout << "temp:" << temp << std::endl;
				Sleep(2000);
				std::cout << "topY[temp]: " << topY[temp] << std::endl;
				std::cout << "topX[temp]: " << topX[temp] << std::endl;
				Sleep(2000);
				_EnemysY.push_back(topY[temp]);
				_EnemysX.push_back(topX[temp]);
				return true;
			}
			if (ranDir == 2 && !botY.empty()){
				int temp = (rand() % botY.size())+1;
				std::cout << "temp:" << temp << std::endl;
				Sleep(2000);
				std::cout << "botY[temp]: " << botY[temp] << std::endl;
				std::cout << "botX[temp]: " << botX[temp] << std::endl;
				Sleep(2000);
				_EnemysY.push_back(botY[temp]);
				_EnemysX.push_back(botX[temp]);
				return true;
			}
			if (ranDir == 3 && !lefY.empty()){
				int temp = (rand() % lefY.size())+1;
				std::cout << "temp:" << temp << std::endl;
				Sleep(2000);
				std::cout << "lefY[temp]: " << lefY[temp] << std::endl;
				std::cout << "lefX[temp]: " << lefX[temp] << std::endl;
				Sleep(2000);
				_EnemysY.push_back(lefY[temp]);
				_EnemysX.push_back(lefX[temp]);
				return true;
			}
			if (ranDir == 4 && !rigY.empty()){
				int temp = (rand() % rigY.size())+1;
				std::cout << "temp:" << temp << std::endl;
				Sleep(2000);
				std::cout << "rigY[temp]: " << rigY[temp] << std::endl;
				std::cout << "rigX[temp]: " << rigX[temp] << std::endl;
				Sleep(2000);
				_EnemysY.push_back(rigY[temp]);
				_EnemysX.push_back(rigX[temp]);
				return true;
			}
		}
	}// moves > 3

	return false;
} 
