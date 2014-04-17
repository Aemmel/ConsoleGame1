#include "Field.h"

Field::Field()
{
	_Player = '@';
	_Grenade = '*';
	_DestroyedField = 'X';
	_Enemy = 'O';
	_Field = '-';
	_erase = false;

	for (int y = 0; y < HEIGHT; y++){
		for (int x = 0; x < WIDTH; x++){
			_map[y][x] = _Field;
		}
	}
}

void Field::DrawMap(Player *grenade, int moves)
{
	if(moves > 5){
		for (Uint it = 0; it < _Enemys.Y.size() && it < _Enemys.X.size(); ++it){
			std::cout << "DrawMap: " << "X: " << _Enemys.X.at(it) << " Y: " << _Enemys.Y.at(it) << std::endl;
			if (_Enemys.Y.at(it) <= HEIGHT && _Enemys.X.at(it) <= WIDTH){
				_map[_Enemys.Y.at(it)][_Enemys.X.at(it)] = _Enemy;
			}
		}
	}

	for(Uint it = 0; it != _DestroyedFields.Y.size() && it != _DestroyedFields.X.size(); ++it){
		if (_DestroyedFields.Y.at(it) <= HEIGHT && _DestroyedFields.X.at(it) <= WIDTH)
			_map[_DestroyedFields.Y.at(it)][_DestroyedFields.X.at(it)] = _DestroyedField;
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

bool Field::MovePlayer(Player *player, int Key)
{
	int PosPlayerX = player->get_X_Cor();
	int PosPlayerY = player->get_Y_Cor();
	int PosGreX = PosPlayerX;
	int PosGreY = PosPlayerY;
	bool FieldBroken = false;

	_map[PosPlayerY][PosPlayerX] = _Player;

	//move up:
	if (Key == 'W' && PosPlayerY > 0 && _map[PosGreY -1][PosGreX] != _Grenade){
		for(Uint it = 0; it < _DestroyedFields.Y.size() && it < _DestroyedFields.X.size(); ++it){
			if (_DestroyedFields.Y.at(it) <= HEIGHT && _DestroyedFields.X.at(it) <= WIDTH){
				if(PosPlayerY -1 == _DestroyedFields.Y.at(it) && PosPlayerX == _DestroyedFields.X.at(it)){
					FieldBroken = true;
					break;
				}
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
	if (Key == 'S' && PosPlayerY < HEIGHT -1 && _map[PosGreY +1][PosGreX] != _Grenade){
		for(Uint it = 0; it<_DestroyedFields.Y.size() && it < _DestroyedFields.X.size(); ++it){
			if (_DestroyedFields.Y.at(it) <= HEIGHT && _DestroyedFields.X.at(it) <= WIDTH){
				if(PosPlayerY +1 == _DestroyedFields.Y.at(it) && PosPlayerX == _DestroyedFields.X.at(it)){
					FieldBroken = true;
					break;
				}
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
	if (Key == 'D' && PosPlayerX < WIDTH -1 && _map[PosGreY][PosGreX +1] != _Grenade){
		for(Uint it = 0; it<_DestroyedFields.Y.size() && it < _DestroyedFields.X.size(); ++it){
			if (_DestroyedFields.Y.at(it) <= HEIGHT && _DestroyedFields.X.at(it) <= WIDTH){
				if(PosPlayerY == _DestroyedFields.Y.at(it) && PosPlayerX +1 == _DestroyedFields.X.at(it)){
					FieldBroken = true;
					break;
				}
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
	if (Key == 'A' && PosPlayerX > 0 && _map[PosGreY][PosGreX -1] != _Grenade){
		for(Uint it = 0; it<_DestroyedFields.Y.size() && it < _DestroyedFields.X.size(); ++it){
			if (_DestroyedFields.Y.at(it) <= HEIGHT && _DestroyedFields.X.at(it) <= WIDTH){
				if(PosPlayerY == _DestroyedFields.Y.at(it) && PosPlayerX -1 == _DestroyedFields.X.at(it)){
					FieldBroken = true;
					break;
				}
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

bool Field::MoveGrenade(Player *grenade, int Key)
{
	int PosGrenadeX = grenade->get_X_Cor();
	int PosGrenadeY = grenade->get_Y_Cor();
	int PosPlayX = PosGrenadeX;
	int PosPlayY = PosGrenadeY;

	_map[PosGrenadeY][PosGrenadeX] = _Grenade;

	//move up:
	if (Key == VK_UP && PosGrenadeY > 0 && _map[PosPlayY -1][PosPlayX] != _Player){
		_map[PosGrenadeY][PosGrenadeX] = _Field;
		PosGrenadeY--;
		_map[PosGrenadeY][PosGrenadeX] = _Grenade;
		grenade->set_Y_Cor(PosGrenadeY);
		return false;
	}
	//move down:
	if (Key == VK_DOWN && PosGrenadeY < HEIGHT -1 && _map[PosPlayY +1][PosPlayX] != _Player){
		_map[PosGrenadeY][PosGrenadeX] = _Field;
		PosGrenadeY++;
		_map[PosGrenadeY][PosGrenadeX] = _Grenade;
		grenade->set_Y_Cor(PosGrenadeY);
		return false;
	}
	//move right:
	if (Key == VK_RIGHT && PosGrenadeX < WIDTH -1 && _map[PosPlayY][PosPlayX +1] != _Player){
		_map[PosGrenadeY][PosGrenadeX] = _Field;
		PosGrenadeX++;
		_map[PosGrenadeY][PosGrenadeX] = _Grenade;
		grenade->set_X_Cor(PosGrenadeX);
		return false;
	}
	//move left:
	if (Key == VK_LEFT && PosGrenadeX > 0 && _map[PosPlayY][PosPlayX -1] != _Player){
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
	if(Key == VK_SPACE){
		for(Uint it = 0; it<_DestroyedFields.Y.size() && it < _DestroyedFields.X.size(); ++it){
			if(PosDestroyedFieldY == _DestroyedFields.Y.at(it) && PosDestroyedFieldX == _DestroyedFields.X.at(it)){
				FieldBroken = true;
				break;
			}
		}

		if (!FieldBroken){
			_erase = true;

			std::cout << "PosDestroyedFieldX: " << PosDestroyedFieldX << " PosDestroyed FieldY: " << PosDestroyedFieldY << std::endl;
			_DestroyedFields.X.push_back(PosDestroyedFieldX);
			_DestroyedFields.Y.push_back(PosDestroyedFieldY);

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

bool Field::EntityMovable(Player *entity)
{
	int PosEntX = entity->get_X_Cor();
	int PosEntY = entity->get_Y_Cor();

	//check corners:
	if (PosEntY == 0 && PosEntX == 0){
		bool B1 = false;	//These variables are responsible, to check if the fields are destroyed(each for one field), they are only valid in the respective if-statement
		bool B2 = false;

		for (Uint it = 0; it<_DestroyedFields.Y.size() && it < _DestroyedFields.X.size(); ++it){
			if (_DestroyedFields.Y.at(it) <= HEIGHT && _DestroyedFields.X.at(it) <= WIDTH){
				if (PosEntY +1 == _DestroyedFields.Y.at(it) && PosEntX == _DestroyedFields.X.at(it)){
					B1 = true;
				}
				if (PosEntY == _DestroyedFields.Y.at(it) && PosEntX +1 == _DestroyedFields.X.at(it)){
					B2 = true;
				}
			}
		}
		if(B1 && B2) 
			return false;
	}
	else if (PosEntY == 0 && PosEntX == WIDTH -1){
		bool B1 = false;
		bool B2 = false;

		for (Uint it = 0; it<_DestroyedFields.Y.size() && it < _DestroyedFields.X.size(); ++it){
			if (_DestroyedFields.Y.at(it) <= HEIGHT && _DestroyedFields.X.at(it) <= WIDTH){
				if (PosEntY +1 == _DestroyedFields.Y.at(it) && PosEntX == _DestroyedFields.X.at(it)){
					B1 = true;
				}
				if (PosEntY == _DestroyedFields.Y.at(it) && PosEntX -1 == _DestroyedFields.X.at(it)){
					B2 = true;
				}
			}
		}
		if (B1 && B2)
			return false;
	}
	else if (PosEntY == HEIGHT -1 && PosEntX == 0){
		bool B1 = false;
		bool B2 = false;

		for (Uint it = 0; it<_DestroyedFields.Y.size() && it < _DestroyedFields.X.size(); ++it){
			if (_DestroyedFields.Y.at(it) <= HEIGHT && _DestroyedFields.X.at(it) <= WIDTH){
				if (PosEntY -1 == _DestroyedFields.Y.at(it) && PosEntX == _DestroyedFields.X.at(it)){
					B1 = true;
				}
				if (PosEntY == _DestroyedFields.Y.at(it) && PosEntX +1 == _DestroyedFields.X.at(it)){
					B2 = true;
				}
			}
		}
		if(B1 && B2)
			return false;
	}
	else if (PosEntY == HEIGHT -1 && PosEntX == WIDTH -1){
		bool B1 = false;
		bool B2 = false;

		for (Uint it = 0; it<_DestroyedFields.Y.size() && it < _DestroyedFields.X.size(); ++it){
			if (_DestroyedFields.Y.at(it) <= HEIGHT && _DestroyedFields.X.at(it) <= WIDTH){
				if (PosEntY -1 == _DestroyedFields.Y.at(it) && PosEntX == _DestroyedFields.X.at(it)){
					B1 = true;
				}
				if (PosEntY == _DestroyedFields.Y.at(it) && PosEntX -1 == _DestroyedFields.X.at(it)){
					B2 = true;
				}
			}
		}
		if(B1 && B2)
			return false;
	}

	//check borders:
	else if (PosEntY == 0){
		bool B1 = false;
		bool B2 = false;
		bool B3 = false;

		for (Uint it = 0; it<_DestroyedFields.Y.size() && it < _DestroyedFields.X.size(); ++it){
				if (_DestroyedFields.Y.at(it) <= HEIGHT && _DestroyedFields.X.at(it) <= WIDTH){
				if (PosEntY +1 == _DestroyedFields.Y.at(it) && PosEntX == _DestroyedFields.X.at(it)){
					B1 = true;	
				}
				if (PosEntY == _DestroyedFields.Y.at(it) && PosEntX +1 == _DestroyedFields.X.at(it)){
					B2 = true;
				}
				if (PosEntY == _DestroyedFields.Y.at(it) && PosEntX -1 == _DestroyedFields.X.at(it)){
					B3 = true;
				}
			}
		}
		if(B1 && B2 && B3)
			return false;
	}
	else if (PosEntY == HEIGHT -1){
		bool B1 = false;
		bool B2 = false;
		bool B3 = false;

		for (Uint it = 0; it<_DestroyedFields.Y.size() && it < _DestroyedFields.X.size(); ++it){
			if (_DestroyedFields.Y.at(it) <= HEIGHT && _DestroyedFields.X.at(it) <= WIDTH){
				if (PosEntY -1 == _DestroyedFields.Y.at(it) && PosEntX == _DestroyedFields.X.at(it)){
					B1 = true;
				}
				if (PosEntY == _DestroyedFields.Y.at(it) && PosEntX +1 == _DestroyedFields.X.at(it)){
					B2 = true;
				}
				if (PosEntY == _DestroyedFields.Y.at(it) && PosEntX -1 == _DestroyedFields.X.at(it)){
					B3 = true;
				}
			}
		}
		if (B1 && B2 && B3)
			return false;
	}
	else if (PosEntX == 0){
		bool B1 = false;
		bool B2 = false;
		bool B3 = false;
		for (Uint it = 0; it<_DestroyedFields.Y.size() && it < _DestroyedFields.X.size(); ++it){
			if (_DestroyedFields.Y.at(it) <= HEIGHT && _DestroyedFields.X.at(it) <= WIDTH){
				if(PosEntY -1 == _DestroyedFields.Y.at(it) && PosEntX == _DestroyedFields.X.at(it)){
					B1 = true;
				}
				if (PosEntY +1 == _DestroyedFields.Y.at(it) && PosEntX == _DestroyedFields.X.at(it)){
					B2 = true;
				}
				if (PosEntY == _DestroyedFields.Y.at(it) && PosEntX +1 == _DestroyedFields.X.at(it)){
					B3 = true;
				}
			}
		}
		if (B1 && B2 && B3)
			return false;
	}
	else if (PosEntX == WIDTH -1){
		bool B1 = false;
		bool B2 = false;
		bool B3 = false;

		for (Uint it = 0; it<_DestroyedFields.Y.size() && it < _DestroyedFields.X.size(); ++it){
			if (_DestroyedFields.Y.at(it) <= HEIGHT && _DestroyedFields.X.at(it) <= WIDTH){
				if(PosEntY -1 == _DestroyedFields.Y.at(it) && PosEntX == _DestroyedFields.X.at(it)){
					B1 = true;
				}
				if (PosEntY +1 == _DestroyedFields.Y.at(it) && PosEntX == _DestroyedFields.X.at(it)){
					B2 = true;
				}
				if (PosEntY == _DestroyedFields.Y.at(it) && PosEntX -1 == _DestroyedFields.X.at(it)){
					B3 = true;
				}
			}
		}
		if (B1 && B2 && B3)
			return false;
	}
	//check middle:
	else {
		bool B1 = false;
		bool B2 = false;
		bool B3 = false;
		bool B4 = false; 

		for (Uint it = 0; it<_DestroyedFields.Y.size() && it < _DestroyedFields.X.size(); ++it){
			if (_DestroyedFields.Y.at(it) <= HEIGHT && _DestroyedFields.X.at(it) <= WIDTH){
				if(PosEntY -1 == _DestroyedFields.Y.at(it) && PosEntX == _DestroyedFields.X.at(it)){
					B1 = true;
				}
				if (PosEntY +1 == _DestroyedFields.Y.at(it) && PosEntX == _DestroyedFields.X.at(it)){
					B2 = true;
				}
				if (PosEntY == _DestroyedFields.X.at(it) && PosEntX -1 == _DestroyedFields.X.at(it)){
					B3 = true;
				}
				if (PosEntY == _DestroyedFields.Y.at(it) && PosEntX +1 == _DestroyedFields.X.at(it)){
					B4 = true;
				}
			}
		}
		if (B1 && B2 && B3 && B4)
			return false;
	}

	return true;
}

bool Field::Enemy(int moves, bool spread)
{
	_moves = moves;
	std::cout << _moves << "  " << moves << "\n\n";
	std::cout << "sizeof _Enemys.X: " << _Enemys.X.size() << " sizeof _Enemys.Y: " << _Enemys.Y.size() << std::endl;
	if (_erase){
		//for (Uint itE = 0; itE < _Enemys.Y.size() && itE < _Enemys.X.size(); ++itE){
		for (std::vector<int>::iterator itEX = _Enemys.X.begin(), itEY = _Enemys.Y.begin(); itEX != _Enemys.X.end() && itEY != _Enemys.Y.end(); ++itEX, ++itEY){
			std::cout << "X: " << *itEX << " Y: " << *itEY << std::endl;
			for (Uint it = 0; it<_DestroyedFields.Y.size() && it < _DestroyedFields.X.size(); ++it){
				if (_DestroyedFields.Y.at(it) == *itEY && _DestroyedFields.X.at(it) == *itEX){
					std::cout << "Erase function called\n";
				//	Sleep(1000);
					itEY = _Enemys.Y.erase(itEY);
					itEX = _Enemys.X.erase(itEX);
					std::cout << "Erase function called\n";
					//
					//does not work properly yet, must fix.......
					//
				}
			/*	else {
					itEY++;
					itEX++;
					std::cout << "Erase function calledfghdvbf\n";
				}*/
			}
		}
	}

	if(moves == 0){
		int randomNum1 = (rand() % HEIGHT);
		int randomNum2 = (rand() % WIDTH);
		_Enemys.Y.push_back(randomNum1);
		_Enemys.X.push_back(randomNum2);
	}

	std::cout << "sizeof _Enemys.X: " << _Enemys.X.size() << " sizeof _Enemys.Y: " << _Enemys.Y.size() << std::endl;
	if (_Enemys.X.size() == 0 || _Enemys.Y.size() == 0){
		return false;
	}

	if (moves > 3 && spread){
		std::cout << "X1: " << _Enemys.X.at(0)  << " Y: " << _Enemys.Y.at(0) << std::endl;

		//save Enemys at the border here (those who can move)
		std::vector<int> topX;
		std::vector<int> topY;
		std::vector<int> botX;
		std::vector<int> botY;
		std::vector<int> rigX;
		std::vector<int> rigY;
		std::vector<int> lefX;
		std::vector<int> lefY;

		for (Uint it = 0; it < _Enemys.Y.size() && it < _Enemys.X.size(); ++it){
			//up:
			if (_map[_Enemys.Y.at(it)-1][_Enemys.X.at(it)] == _Grenade || _map[_Enemys.Y.at(it)-1][_Enemys.X.at(it)] == _Field && _Enemys.Y.at(it) > 0){
				std::cout << "up\n";
				topY.push_back(_Enemys.Y.at(it)-1);
				topX.push_back(_Enemys.X.at(it));
			}
			//down:
			if (_map[_Enemys.Y.at(it)+1][_Enemys.X.at(it)] == _Grenade || _map[_Enemys.Y.at(it)+1][_Enemys.X.at(it)] == _Field && _Enemys.Y.at(it) < HEIGHT -1){
				std::cout << "down\n";
				botY.push_back(_Enemys.Y.at(it)+1);
				botX.push_back(_Enemys.X.at(it));
			}
			//left:
			if (_map[_Enemys.Y.at(it)][_Enemys.X.at(it)-1] == _Grenade || _map[_Enemys.Y.at(it)][_Enemys.X.at(it)-1] == _Field && _Enemys.X.at(it) > 0){
				std::cout << "left\n";
				lefX.push_back(_Enemys.X.at(it)-1);
				lefY.push_back(_Enemys.Y.at(it));
			}
			//right
			if (_map[_Enemys.Y.at(it)][_Enemys.X.at(it)+1] == _Grenade || _map[_Enemys.Y.at(it)][_Enemys.X.at(it)+1] == _Field && _Enemys.X.at(it) < WIDTH -1){
				std::cout << "right\n";
				rigX.push_back(_Enemys.X.at(it)+1);
				rigY.push_back(_Enemys.Y.at(it));
			}	
		}


		for (;;){
			int ranDir = (rand() % 4)+1;
			std::cout << "randir: " << ranDir << std::endl;
			//up:
			if (ranDir == 1 && !topY.empty()){
				int temp = (rand() % topY.size());
				_Enemys.Y.push_back(topY.at(temp));
				_Enemys.X.push_back(topX.at(temp));
				return true;
			}
			//down:
			if (ranDir == 2 && !botY.empty()){
				int temp = (rand() % botY.size());
				_Enemys.Y.push_back(botY.at(temp));
				_Enemys.X.push_back(botX.at(temp));
				return true;
			}
			//left:
			if (ranDir == 3 && !lefY.empty()){
				int temp = (rand() % lefY.size());
				_Enemys.Y.push_back(lefY.at(temp));
				_Enemys.X.push_back(lefX.at(temp));
				return true;
			}
			//right:
			if (ranDir == 4 && !rigY.empty()){
				int temp = (rand() % rigY.size());
				_Enemys.Y.push_back(rigY.at(temp));
				_Enemys.X.push_back(rigX.at(temp));
				return true;
			}
		}
	}// moves > 3
	return true;
} 
