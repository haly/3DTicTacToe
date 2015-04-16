/*
	Author: Francis Yuan
	Date: 4/12/2015
*/
#include <iostream>
#include <string>
#include "GameManager.h"

int main() {
	GameManager game = GameManager();
	game.initialize();
	game.introduction();
	while (!game.quit()) {
		game.update();
	}

	/*
	std::string dummy;
	std::cout << "Testing this input shit.\n";
	//std::cin >> dummy;
	std::getline(std::cin, dummy);
	std::cout << "The shit you just typed was: " + dummy + "\n";
	*/
}