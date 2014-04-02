#include "Player.h"

int Player::get_X_Cor()
{
	return _PosX;
}

int Player::get_Y_Cor()
{
	return _PosY;
}

void Player::set_X_Cor(int newXPos)
{
	_PosX = newXPos;
}

void Player::set_Y_Cor(int newYPos)
{
	_PosY = newYPos;
}

void Player::set_Cor(int newXPos, int newYPos)
{
	set_X_Cor(newXPos);
	set_Y_Cor(newYPos);
}
