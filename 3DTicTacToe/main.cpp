/*
	Author: Francis Yuan
	Date: 4/12/2015
*/
#include <iostream>
#include <string>
#include "GameManager.h"
#include "Human.h"

int main() {
	GameManager game;
	game.initialize();
	game.introduction();
	game.setup();
	while (!game.quit()) {
		game.update();
	}
}