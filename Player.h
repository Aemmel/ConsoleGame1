#ifndef PLAYER_H
#define PLAYER_H

static const int WIDTH = 15;
static const int HEIGHT = 10;

class Player
{
public:
	int get_X_Cor();
	int get_Y_Cor();
	void set_X_Cor(int newXPos);
	void set_Y_Cor(int newYPos);
	void set_Cor(int newXPos, int newYPos);
	
private:
	int _PosX;
	int _PosY;

};

#endif
