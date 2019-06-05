#include <iostream>
#include "game.h"

using namespace std;

int main()
{
	Game* newgame = new Game();
	newgame->PlayGame();
	delete newgame;
}