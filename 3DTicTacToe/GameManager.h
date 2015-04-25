/* 
	Author: Francis Yuan
	Date: 4/14/2015
 */
#pragma once
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <string>
#include <iostream>
#include <vector>

#include "CuboidArray.h"
#include "util.h"
#include "IntVector3.h"
/*
	GameManager is an instance of 3D TicTacToe and is responsible for flow control.

	3DTicTacToe is a game played between two players, X and O, referred to in code as PLAYER_X and PLAYER_O.
	
	Players alterante turns placing X or O in empty spaces on a 4*4*4 3D array, beginning with PLAYER_X. 
	
	The first player to have four of their pieces in a row (whether straight from side to side or diagonal from corner to corner) wins the game. 
	
	The game is a tie when the game board runs out of empty spaces.
 */
class GameManager {
public:
	/*
		Creates a new instance of GameManager, which represents a game of 3D TicTacToe.
	 */
	GameManager();
	~GameManager();

	/*
		Sets initial values for a new game.
	 */
	void initialize();

	/*
		Prints game instructions to the console.
	*/
	void introduction() const;

	// TEMPORARY FUNCTIONS THAT WILL BE REPLACED WITH A PROPER MENU SYSTEM
	/*
		Begins a long chain of input requests to sdetermine the initial state of the game.
	*/
	void setup();
	// END TEMPORARY FUNCTIONS

	/*
		Cycles through game logic.
	 */
	void update();

	/*
		Returns quitFlag for exiting the program.
	 */
	bool quit() const;

private:
	static const int MAX_TURNS = 64;

	// TEMPORARY VARIABLES THAT WILL BE REPLACED WITH THE PLAYER SYSTEM
	int numberOfHumans = 0;
	int difficultyX = 0;
	int difficultyY = 0;
	// END TEMPORARY VARIABLES

	// Variables for in-game use
	int turnCounter;
	int currentTurn;

	// Variables for state tracking
	int gameState;
	bool quitFlag;

	CuboidArray board;

	/*
		Prints the current player's turn in the console.
	 */
	void printTurn();

	/*
		Alternates between player turns.
	 */
	void nextTurn();

	/*
		Recieves and sanitizes input from the console.
	 */
	void getInput();

	/*
		Helper function to read single commands and inform the user of any syntatical errors.
	*/
	bool readCommand(const std::vector<std::string>& tokens);

	/*
		Helper function to read three sequential numbers representing coordinates and inform the user of any syntatical errors.
	 */
	bool readCoords(const std::vector<std::string>& tokens);

	/*
		Checks if a winning move was just made, or if the entire board was just filled
	 */
	bool checkWinningMove(const int& turn, const IntVector3& coords);
};

enum BOARD_SPACES { 
	EMPTY = 0,
	PLAYER_X = 1, 
	PLAYER_O = -1,
};

enum GAME_STATE {
	PRE_GAME = 0,
	GAME_COMMENCE,
};

#endif

