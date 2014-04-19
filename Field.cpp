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
		for (unsigned it = 0; it < _Enemys.size() ; ++it){
			if (_Enemys.at(it).Y <= HEIGHT && _Enemys.at(it).X <= WIDTH){
				_map[_Enemys.at(it).Y][_Enemys.at(it).X] = _Enemy;
			}
		}
	}

	for(unsigned it = 0; it != _DestroyedFields.size(); ++it){
		if (_DestroyedFields.at(it).Y <= HEIGHT && _DestroyedFields.at(it).X <= WIDTH)
			_map[_DestroyedFields.at(it).Y][_DestroyedFields.at(it).X] = _DestroyedField;
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
	Entity PosPlayer;
	PosPlayer.X = player->get_X_Cor();
	PosPlayer.Y = player->get_Y_Cor();
	bool FieldBroken = false;

	_map[PosPlayer.Y][PosPlayer.X] = _Player;

	//move up:
	if (Key == 'W' && PosPlayer.Y > 0 && _map[PosPlayer.Y -1][PosPlayer.X] != _Grenade){
		for(unsigned it = 0; it < _DestroyedFields.size(); ++it){
			if (_DestroyedFields.at(it).Y <= HEIGHT && _DestroyedFields.at(it).X <= WIDTH){
				if(PosPlayer.Y -1 == _DestroyedFields.at(it).Y && PosPlayer.X == _DestroyedFields.at(it).X){
					FieldBroken = true;
					break;
				}
			}
		}

		if (!FieldBroken){
			_map[PosPlayer.Y][PosPlayer.X] = _Field;
			PosPlayer.Y--;
			_map[PosPlayer.Y][PosPlayer.X] = _Player;
			player->set_Y_Cor(PosPlayer.Y);
			return true;
		}
		FieldBroken = false;
	}
	//move down:
	if (Key == 'S' && PosPlayer.Y < HEIGHT -1 && _map[PosPlayer.Y +1][PosPlayer.X] != _Grenade){
		for(unsigned it = 0; it<_DestroyedFields.size(); ++it){
			if (_DestroyedFields.at(it).Y <= HEIGHT && _DestroyedFields.at(it).X <= WIDTH){
				if(PosPlayer.Y +1 == _DestroyedFields.at(it).Y && PosPlayer.X == _DestroyedFields.at(it).X){
					FieldBroken = true;
					break;
				}
			}
		}

		if(!FieldBroken){
			_map[PosPlayer.Y][PosPlayer.X] = _Field;
			PosPlayer.Y++;
			_map[PosPlayer.Y][PosPlayer.X] = _Player;
			player->set_Y_Cor(PosPlayer.Y);
			return true;
		}
		FieldBroken = false;
	}
	//move right:
	if (Key == 'D' && PosPlayer.X < WIDTH -1 && _map[PosPlayer.Y][PosPlayer.X +1] != _Grenade){
		for(unsigned it = 0; it<_DestroyedFields.size(); ++it){
			if (_DestroyedFields.at(it).Y <= HEIGHT && _DestroyedFields.at(it).X <= WIDTH){
				if(PosPlayer.Y == _DestroyedFields.at(it).Y && PosPlayer.X +1 == _DestroyedFields.at(it).X){
					FieldBroken = true;
					break;
				}
			}
		}

		if(!FieldBroken){
			_map[PosPlayer.Y][PosPlayer.X] = _Field;
			PosPlayer.X++;
			_map[PosPlayer.Y][PosPlayer.X] = _Player;
			player->set_X_Cor(PosPlayer.X);
			return true;
		}
		FieldBroken = false;
	}
	//move left:
	if (Key == 'A' && PosPlayer.X > 0 && _map[PosPlayer.Y][PosPlayer.X -1] != _Grenade){
		for(unsigned it = 0; it<_DestroyedFields.size(); ++it){
			if (_DestroyedFields.at(it).Y <= HEIGHT && _DestroyedFields.at(it).X <= WIDTH){
				if(PosPlayer.Y == _DestroyedFields.at(it).Y && PosPlayer.X -1 == _DestroyedFields.at(it).X){
					FieldBroken = true;
					break;
				}
			}
		}

		if(!FieldBroken){
			_map[PosPlayer.Y][PosPlayer.X] = _Field;
			PosPlayer.X--;
			_map[PosPlayer.Y][PosPlayer.X] = _Player;
			player->set_X_Cor(PosPlayer.X);
			return true;
		}
		FieldBroken = false;
	}

	return false;
}

bool Field::MoveGrenade(Player *grenade, int Key)
{
	Entity PosGrenade;
	PosGrenade.X = grenade->get_X_Cor();
	PosGrenade.Y = grenade->get_Y_Cor();
	//int PosPlayX = PosGrenadeX;
	//int PosPlayY = PosGrenadeY;

	_map[PosGrenade.Y][PosGrenade.X] = _Grenade;

	//move up:
	if (Key == VK_UP && PosGrenade.Y > 0 && _map[PosGrenade.Y -1][PosGrenade.X] != _Player){
		_map[PosGrenade.Y][PosGrenade.X] = _Field;
		PosGrenade.Y--;
		_map[PosGrenade.Y][PosGrenade.X] = _Grenade;
		grenade->set_Y_Cor(PosGrenade.Y);
		return false;
	}
	//move down:
	if (Key == VK_DOWN && PosGrenade.Y < HEIGHT -1 && _map[PosGrenade.Y +1][PosGrenade.X] != _Player){
		_map[PosGrenade.Y][PosGrenade.X] = _Field;
		PosGrenade.Y++;
		_map[PosGrenade.Y][PosGrenade.X] = _Grenade;
		grenade->set_Y_Cor(PosGrenade.Y);
		return false;
	}
	//move right:
	if (Key == VK_RIGHT && PosGrenade.X < WIDTH -1 && _map[PosGrenade.Y][PosGrenade.X +1] != _Player){
		_map[PosGrenade.Y][PosGrenade.X] = _Field;
		PosGrenade.X++;
		_map[PosGrenade.Y][PosGrenade.X] = _Grenade;
		grenade->set_X_Cor(PosGrenade.X);
		return false;
	}
	//move left:
	if (Key == VK_LEFT && PosGrenade.X > 0 && _map[PosGrenade.Y][PosGrenade.X -1] != _Player){
		_map[PosGrenade.Y][PosGrenade.X] = _Field;
		PosGrenade.X--;
		_map[PosGrenade.Y][PosGrenade.X] = _Grenade;
		grenade->set_X_Cor(PosGrenade.X);
		return false;
	}

	bool FieldBroken = false;

	//destroy field:
	if(Key == VK_SPACE){
		for(unsigned it = 0; it<_DestroyedFields.size(); ++it){
			if(PosGrenade.Y == _DestroyedFields.at(it).Y && PosGrenade.X == _DestroyedFields.at(it).X){
				FieldBroken = true;
				break;
			}
		}

		if (!FieldBroken){
			_erase = true;

			_DestroyedFields.push_back(PosGrenade);

			//set grenade over, under, left or right of the destroyed field: 

			//left, if end of the map on Y-and X-axis AND the player is above: 
			if (PosGrenade.Y == HEIGHT -1 && PosGrenade.X == WIDTH -1 && _map[PosGrenade.Y -1][PosGrenade.X] == _Player){
				PosGrenade.X--;
				_map[PosGrenade.Y][PosGrenade.X] = _Grenade;
				grenade->set_X_Cor(PosGrenade.X);
			}
			//right, if end of the map on Y-axis AND the player is above: 
			else if(PosGrenade.Y == HEIGHT -1 && _map[PosGrenade.Y -1][PosGrenade.X] == _Player){
				PosGrenade.X++;
				_map[PosGrenade.Y][PosGrenade.X] = _Grenade;
				grenade->set_X_Cor(PosGrenade.X);
			}
			//up, if end of the map on Y-axis: 
			else if(PosGrenade.Y == HEIGHT -1){
				PosGrenade.Y--;
				_map[PosGrenade.Y][PosGrenade.X] = _Grenade;
				grenade->set_Y_Cor(PosGrenade.Y);
			}
			//right, if beginning of the map on Y-and X-axis AND player is below: 
			else if(PosGrenade.Y == 0 && PosGrenade.X == 0 && _map[PosGrenade.Y +1][PosGrenade.X] == _Player){
				PosGrenade.X++;
				_map[PosGrenade.Y][PosGrenade.X] = _Grenade;
				grenade->set_X_Cor(PosGrenade.X);
			}
			//left, if beginning of the map on Y-axis AND player is below:
			else if(PosGrenade.Y == 0 && _map[PosGrenade.Y +1][PosGrenade.X] == _Player){
				PosGrenade.X--;
				_map[PosGrenade.Y][PosGrenade.X] = _Grenade;
				grenade->set_X_Cor(PosGrenade.X);
			}
			//up, if player is below:
			else if(_map[PosGrenade.Y +1][PosGrenade.X] == _Player){
				PosGrenade.Y--;
				_map[PosGrenade.Y][PosGrenade.X] = _Grenade;
				grenade->set_Y_Cor(PosGrenade.Y);
			}
			//down, if below is free:
			else {
				PosGrenade.Y++;
				_map[PosGrenade.Y][PosGrenade.X] = _Grenade;
				grenade->set_Y_Cor(PosGrenade.Y);
			}

			return true;
		}
		FieldBroken = false;
	}
	return false;
}

bool Field::EntityMovable(Player *entity)
{
	Entity PosEnt;
	PosEnt.X = entity->get_X_Cor();
	PosEnt.Y = entity->get_Y_Cor();

	for (unsigned it = 0; it<_Enemys.size(); ++it){
		if (PosEnt.X == _Enemys.at(it).X && PosEnt.Y == _Enemys.at(it).Y){
			return false;
		}
	}

	//check corners:
	if (PosEnt.Y == 0 && PosEnt.X == 0){
		bool B1 = false;	//These variables are responsible, to check if the fields are destroyed(each for one field), they are only valid in the respective if-statement
		bool B2 = false;

		for (unsigned it = 0; it<_DestroyedFields.size(); ++it){
			if (_DestroyedFields.at(it).Y <= HEIGHT && _DestroyedFields.at(it).X <= WIDTH){
				if (PosEnt.Y +1 == _DestroyedFields.at(it).Y && PosEnt.X == _DestroyedFields.at(it).X){
					B1 = true;
				}
				if (PosEnt.Y == _DestroyedFields.at(it).Y && PosEnt.X +1 == _DestroyedFields.at(it).X){
					B2 = true;
				}
			}
		}
		if(B1 && B2) 
			return false;
	}
	else if (PosEnt.Y == 0 && PosEnt.X == WIDTH -1){
		bool B1 = false;
		bool B2 = false;

		for (unsigned it = 0; it<_DestroyedFields.size(); ++it){
			if (_DestroyedFields.at(it).Y <= HEIGHT && _DestroyedFields.at(it).X <= WIDTH){
				if (PosEnt.Y +1 == _DestroyedFields.at(it).Y && PosEnt.X == _DestroyedFields.at(it).X){
					B1 = true;
				}
				if (PosEnt.Y == _DestroyedFields.at(it).Y && PosEnt.X -1 == _DestroyedFields.at(it).X){
					B2 = true;
				}
			}
		}
		if (B1 && B2)
			return false;
	}
	else if (PosEnt.Y == HEIGHT -1 && PosEnt.X == 0){
		bool B1 = false;
		bool B2 = false;

		for (unsigned it = 0; it<_DestroyedFields.size(); ++it){
			if (_DestroyedFields.at(it).Y <= HEIGHT && _DestroyedFields.at(it).X <= WIDTH){
				if (PosEnt.Y -1 == _DestroyedFields.at(it).Y && PosEnt.X == _DestroyedFields.at(it).X){
					B1 = true;
				}
				if (PosEnt.Y == _DestroyedFields.at(it).Y && PosEnt.X +1 == _DestroyedFields.at(it).X){
					B2 = true;
				}
			}
		}
		if(B1 && B2)
			return false;
	}
	else if (PosEnt.Y == HEIGHT -1 && PosEnt.X == WIDTH -1){
		bool B1 = false;
		bool B2 = false;

		for (unsigned it = 0; it<_DestroyedFields.size(); ++it){
			if (_DestroyedFields.at(it).Y <= HEIGHT && _DestroyedFields.at(it).X <= WIDTH){
				if (PosEnt.Y -1 == _DestroyedFields.at(it).Y && PosEnt.X == _DestroyedFields.at(it).X){
					B1 = true;
				}
				if (PosEnt.Y == _DestroyedFields.at(it).Y && PosEnt.X -1 == _DestroyedFields.at(it).X){
					B2 = true;
				}
			}
		}
		if(B1 && B2)
			return false;
	}

	//check borders:
	else if (PosEnt.Y == 0){
		bool B1 = false;
		bool B2 = false;
		bool B3 = false;

		for (unsigned it = 0; it<_DestroyedFields.size(); ++it){
				if (_DestroyedFields.at(it).Y <= HEIGHT && _DestroyedFields.at(it).X <= WIDTH){
				if (PosEnt.Y +1 == _DestroyedFields.at(it).Y && PosEnt.X == _DestroyedFields.at(it).X){
					B1 = true;	
				}
				if (PosEnt.Y == _DestroyedFields.at(it).Y && PosEnt.X +1 == _DestroyedFields.at(it).X){
					B2 = true;
				}
				if (PosEnt.Y == _DestroyedFields.at(it).Y && PosEnt.X -1 == _DestroyedFields.at(it).X){
					B3 = true;
				}
			}
		}
		if(B1 && B2 && B3)
			return false;
	}
	else if (PosEnt.Y == HEIGHT -1){
		bool B1 = false;
		bool B2 = false;
		bool B3 = false;

		for (unsigned it = 0; it<_DestroyedFields.size(); ++it){
			if (_DestroyedFields.at(it).Y <= HEIGHT && _DestroyedFields.at(it).X <= WIDTH){
				if (PosEnt.Y -1 == _DestroyedFields.at(it).Y && PosEnt.X == _DestroyedFields.at(it).X){
					B1 = true;
				}
				if (PosEnt.Y == _DestroyedFields.at(it).Y && PosEnt.X +1 == _DestroyedFields.at(it).X){
					B2 = true;
				}
				if (PosEnt.Y == _DestroyedFields.at(it).Y && PosEnt.X -1 == _DestroyedFields.at(it).X){
					B3 = true;
				}
			}
		}
		if (B1 && B2 && B3)
			return false;
	}
	else if (PosEnt.X == 0){
		bool B1 = false;
		bool B2 = false;
		bool B3 = false;
		for (unsigned it = 0; it<_DestroyedFields.size(); ++it){
			if (_DestroyedFields.at(it).Y <= HEIGHT && _DestroyedFields.at(it).X <= WIDTH){
				if(PosEnt.Y -1 == _DestroyedFields.at(it).Y && PosEnt.X == _DestroyedFields.at(it).X){
					B1 = true;
				}
				if (PosEnt.Y +1 == _DestroyedFields.at(it).Y && PosEnt.X == _DestroyedFields.at(it).X){
					B2 = true;
				}
				if (PosEnt.Y == _DestroyedFields.at(it).Y && PosEnt.X +1 == _DestroyedFields.at(it).X){
					B3 = true;
				}
			}
		}
		if (B1 && B2 && B3)
			return false;
	}
	else if (PosEnt.X == WIDTH -1){
		bool B1 = false;
		bool B2 = false;
		bool B3 = false;

		for (unsigned it = 0; it<_DestroyedFields.size(); ++it){
			if (_DestroyedFields.at(it).Y <= HEIGHT && _DestroyedFields.at(it).X <= WIDTH){
				if(PosEnt.Y -1 == _DestroyedFields.at(it).Y && PosEnt.X == _DestroyedFields.at(it).X){
					B1 = true;
				}
				if (PosEnt.Y +1 == _DestroyedFields.at(it).Y && PosEnt.X == _DestroyedFields.at(it).X){
					B2 = true;
				}
				if (PosEnt.Y == _DestroyedFields.at(it).Y && PosEnt.X -1 == _DestroyedFields.at(it).X){
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

		for (unsigned it = 0; it<_DestroyedFields.size(); ++it){
			if (_DestroyedFields.at(it).Y <= HEIGHT && _DestroyedFields.at(it).X <= WIDTH){
				if(PosEnt.Y -1 == _DestroyedFields.at(it).Y && PosEnt.X == _DestroyedFields.at(it).X){
					B1 = true;
				}
				if (PosEnt.Y +1 == _DestroyedFields.at(it).Y && PosEnt.X == _DestroyedFields.at(it).X){
					B2 = true;
				}
				if (PosEnt.Y == _DestroyedFields.at(it).X && PosEnt.X -1 == _DestroyedFields.at(it).X){
					B3 = true;
				}
				if (PosEnt.Y == _DestroyedFields.at(it).Y && PosEnt.X +1 == _DestroyedFields.at(it).X){
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
	if (_erase){
		for (unsigned itE = 0; itE < _Enemys.size(); ++itE){
			for (unsigned it = 0; it<_DestroyedFields.size(); ++it){
				if (_Enemys.at(itE).Y == _DestroyedFields.at(it).Y && _Enemys.at(itE).X == _DestroyedFields.at(it).X){
					_Enemys.erase(_Enemys.begin()+itE);
					break;
				}
			}
		}
	}

	if(moves == 0){
		Entity randomNum;
		randomNum.Y = (rand() % HEIGHT);
		randomNum.X = (rand() % WIDTH);
		if (randomNum.Y <= HEIGHT && randomNum.X <= WIDTH){
			_Enemys.push_back(randomNum);
		}
	}

	if (_Enemys.size() == 0 && moves > 0){
		return false;
	}

	//save Enemys at the border here (those who can move)
	std::vector<Entity> top;
	std::vector<Entity> bot;
	std::vector<Entity> rig;
	std::vector<Entity> lef;

	for (unsigned it = 0; it < _Enemys.size(); ++it){
		//up:
		if (_map[_Enemys.at(it).Y -1][_Enemys.at(it).X] == _Grenade || _map[_Enemys.at(it).Y-1][_Enemys.at(it).X] == _Field 
			|| _map[_Enemys.at(it).Y-1][_Enemys.at(it).X] == _Player){
			if (_Enemys.at(it).Y > 0){
				top.push_back(_Enemys.at(it));//Y-1
			}
		}
		//down:
		if (_map[_Enemys.at(it).Y+1][_Enemys.at(it).X] == _Grenade || _map[_Enemys.at(it).Y+1][_Enemys.at(it).X] == _Field 
			|| _map[_Enemys.at(it).Y+1][_Enemys.at(it).X] == _Player){
			if (_Enemys.at(it).Y < HEIGHT -1){
				bot.push_back(_Enemys.at(it));//Y+1
			}
		}
		//left:
		if (_map[_Enemys.at(it).Y][_Enemys.at(it).X-1] == _Grenade || _map[_Enemys.at(it).Y][_Enemys.at(it).X-1] == _Field 
			|| _map[_Enemys.at(it).Y][_Enemys.at(it).X-1] == _Player && _Enemys.at(it).X > 0){
			if (_Enemys.at(it).X > 0){
				lef.push_back(_Enemys.at(it));//X-1
			}		
		}
		//right
		if (_map[_Enemys.at(it).Y][_Enemys.at(it).X+1] == _Grenade || _map[_Enemys.at(it).Y][_Enemys.at(it).X+1] == _Field 
			|| _map[_Enemys.at(it).Y][_Enemys.at(it).X+1] == _Player){
			if (_Enemys.at(it).X < WIDTH -1){
				rig.push_back(_Enemys.at(it));//X+1
			}
		}	
	}

	if (top.empty() && bot.empty() && rig.empty() && lef.empty()){
		return false;
	}

		
	if (moves >= 3 && spread){
		for (;;){
			int ranDir = (rand() % 4)+1;
			//up:
			if (ranDir == 1 && !top.empty()){
				int temp = (rand() % top.size());
				top.at(temp).Y -= 1;
				_Enemys.push_back(top.at(temp));
				return true;
			}
			//down:
			if (ranDir == 2 && !bot.empty()){
				int temp = (rand() % bot.size());
				bot.at(temp).Y += 1;
				_Enemys.push_back(bot.at(temp));
				return true;
			}
			//left:
			if (ranDir == 3 && !lef.empty()){
				int temp = (rand() % lef.size());
				lef.at(temp).X -= 1;
				_Enemys.push_back(lef.at(temp));
				return true;
			}
			//right:
			if (ranDir == 4 && !rig.empty()){
				int temp = (rand() % rig.size());
				rig.at(temp).X += 1;
				_Enemys.push_back(rig.at(temp));
				return true;
			}
		}
	}// moves > 3
	return true;
} 

void Field::resetGame(int *movesT, int *movesR)
{
	_moves = 0;
	*movesT = 0;
	*movesR = 0;
	_DestroyedFields.clear();
	_Enemys.clear();
	for (int y = 0; y < HEIGHT; y++){
		for (int x = 0; x < WIDTH; x++){
			_map[y][x] = _Field;
		}
	}
}
