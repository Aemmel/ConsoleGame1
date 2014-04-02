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
	MovePlayer(_player);
	std::cout << "X-Cor Pl: " << _player->get_X_Cor() << "\nY-Cor Pl: " << _player->get_Y_Cor() << std::endl;


	MoveGrenade(_grenade);
	std::cout << "X-Cor Gr: " << _grenade->get_X_Cor() << "\nY-Cor Gr: " << _grenade->get_Y_Cor() << std::endl;

	if(EntityMovable(_player))
		std::cout << "Movable\n";

	Enemy(_moves_total);
}

int Game::GameLoop()
{
	Initialize();

	for(;;){
		system("cls");
		if (_moves_round == 3)
			_moves_round = 0;

		GameRules();

		DrawMap(_grenade, _moves_total);

		if(_game_over || _game_won)
			break;

		system("pause>nul");

		_moves_round++;
		_moves_total++;
	}
	system("cls");
	
	if(_game_over)
		std::cout << "\t\tGAME OVER! :-(\n\n";
	if(_game_won)
		std::cout << "\t\tGAME WON! :-)\n\n";

	system("pause");
	return 0;
}
