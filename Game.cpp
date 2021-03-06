#include "Game.h"

Game::Game()
{
	_game_over = false;
	_game_won = false;
	_moves_round = 0;
	_moves_total = 0;

	_player = new Player;
	_grenade = new Player;
}

Game::~Game()
{
	delete _player;
	delete _grenade;
}

void Game::Initialize()
{
	system("color F0");

	_player->set_Cor(0, 0);
	_grenade->set_Cor(WIDTH / 2, HEIGHT / 2);

}

void Game::GameRules()
{
	int Key = GetKey();

	if (_moves_round == 5){
		_moves_round = 0;
	}

	MovePlayer(_player, Key);

	MoveGrenade(_grenade, Key);

	if (!EntityMovable(_player))
		_game_over = true;

	if (_moves_round == 0){
		if (!Enemy(_moves_total, true)){
			_game_won = true;
		}
	}
	else {
		if (!Enemy(_moves_total, false)){
			_game_won = true;
		}
	}
}

void Game::GameLoop()
{
	Initialize();

	for(;;){
		system("cls");

		GameRules();

		DrawMap(_grenade, _moves_total);

		if(_game_over || _game_won)
			break;

		system("pause>nul");

		_moves_round++;
		_moves_total++;
	}
	system("cls");
	
	if(_game_over){
		std::cout << "\t\tGAME OVER! :-(\n\n";
		if (restart(false)){
			_game_over = false;
			resetGame(&_moves_total, &_moves_round);
			GameLoop();
		}
	}
	if(_game_won){
		std::cout << "\t\tGAME WON! :-)\n\n";
		if (restart(true)){
			_game_won = false;
			resetGame(&_moves_total, &_moves_round);
			GameLoop();
		}
	}
}

int Game::GetKey()
{
	if (GetAsyncKeyState('W'))
		return 'W';
	if (GetAsyncKeyState('S'))
		return 'S';
	if (GetAsyncKeyState('A'))
		return 'A';
	if (GetAsyncKeyState('D'))
		return 'D';
	if (GetAsyncKeyState(VK_SPACE))
		return VK_SPACE;
	if (GetAsyncKeyState(VK_UP))
		return VK_UP;
	if (GetAsyncKeyState(VK_DOWN))
		return VK_DOWN;
	if (GetAsyncKeyState(VK_RIGHT))
		return VK_RIGHT;
	if (GetAsyncKeyState(VK_LEFT))
		return VK_LEFT;

	return 0;
}

bool Game::restart(bool game_won)
{
	char pre = '>';
	char suf = '<';
	std::string yes = "yes";
	std::string no = "no";
	bool choice = false;
	for(;;){
		system("cls");
		if (GetAsyncKeyState(VK_LEFT)){
			choice = false;
			std::cout << "\a";
		}
		if (GetAsyncKeyState(VK_RIGHT)){
			choice = true;
			std::cout << "\a";
		}
		if (GetAsyncKeyState(VK_RETURN)){
			std::cout << "\a";
			return choice;
		}
		 
		if (game_won){
			std::cout << "\t\tGAME WON! :-)\n\n";
		}
		else {
			std::cout << "\t\tGAME OVER! :-(\n\n";
		}
		std::cout << "Do you wanna restart the game?\n";
		if (!choice)
			std::cout << pre << no << suf << " " << yes;
		if (choice)
			std::cout << " " << no << " " << pre << yes << suf;
		system("pause>nul");
	}
}
