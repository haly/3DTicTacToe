/* 
	Author: Francis Yuan
	Date: 4/14/2015
 */
#pragma once
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <cassert>
#include <string>
#include <iostream>
#include <vector>

#include "util.h"
#include "IntVector3.h"
#include "CuboidArray.h"
#include "Player.h"
#include "Human.h"

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
		Prints game instructions to the console.
	*/
	void introduction() const;

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
	// END TEMPORARY VARIABLES

	// Variables for turn tracking
	int turnCounter;
	int currentTurn;

	// Variables for state tracking
	int gameState;
	bool quitFlag;

	// Board and players
	CuboidArray board;
	Player* playerX;
	Player* playerO;

	/*
		Resets the board and the turn trackers
	*/
	void initialize();

	/*
		Prints the current player's turn in the console.
	 */
	void printTurn();

	/*
		Alternates between player turns.
	 */
	void nextTurn();

	/*
		Handles input to set up a game.
	*/
	void preGame();

	/*
		Handles input for a game being played.
	 */
	void inGame();

	/*
		Handles input after a game is done.
	*/
	void postGame();

	/*
		Checks if a winning move was just made, or if the entire board was just filled
	*/

	bool checkWinningMove(const int& turn, const IntVector3& coords);

	/*
		Recieves and sanitizes input from the console.

	void getInput();


		Helper function to read single commands and inform the user of any syntatical errors.

	bool readCommand(const std::vector<std::string>& tokens);


		Helper function to read three sequential numbers representing coordinates and inform the user of any syntatical errors.

	bool readCoords(const std::vector<std::string>& tokens);
	*/

	
};

enum GAME_STATE {
	PRE_GAME = 0,
	IN_GAME,
	POST_GAME
};

#endif

