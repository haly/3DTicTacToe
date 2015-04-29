/*
	Author: Francis Yuan
	Date: 4/22/2015
*/
#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include "IntVector3.h"
#include "CuboidArray.h"

class Player {
public:
	Player(std::string name);
	~Player();

	/*
		Asks this player for a move.
	 */
	virtual IntVector3 getMove(const CuboidArray& ca) = 0;

	friend std::ostream& operator<<(std::ostream& out, const Player& p);
protected:
	std::string name;
};

#endif