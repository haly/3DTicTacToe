/*
	Author: Francis Yuan
	Date: 4/22/2015
*/
#include "Player.h"


Player::Player(std::string name) : name(name) {
}


Player::~Player() {
}

std::ostream& operator<<(std::ostream& out, const Player& p) {
	out << p.name;
	return out;
}

