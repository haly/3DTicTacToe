/*
	Author: Francis Yuan
	Date: 4/24/2015
*/
#pragma once
#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"

class Human :
	public Player {
public:
	Human(std::string name);
	~Human();

	/*
		A Human will request input via the console
	 */
	IntVector3 getMove(const CuboidArray& ca);
};
#endif

