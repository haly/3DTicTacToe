/*
	Author: Francis Yuan
	Date: 4/24/2015
*/
#pragma once
#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"
#include "util.h"

class Human :
	public Player {
public:
	Human();
	Human(std::string name);
	~Human();

	/*
		A Human will request input from the console
	 */
	IntVector3 getMove(const int& myTurn, const CuboidArray& ca);
};
#endif

