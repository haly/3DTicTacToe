/*
	Author: Francis Yuan
	Date: 4/14/2015
*/
#include "GameManager.h"


GameManager::GameManager() {
	board = CuboidArray();
}


GameManager::~GameManager() {
}

void GameManager::initialize() {
	board.zero();
	currentTurn = PLAYER_X;
	turnCounter = 1;
	isOver = false;
}

void GameManager::introduction() {
	std::cout <<
		"3D TicTacToe, by Francis Yuan\n"
		"How to play:\n"
		"   - X goes first, O goes second\n"
		"   - First to make 4 in a row, straight or diagonal, wins\n"
		"   - Take turns by entering three coordinates separated by spaces\n"
		"     E.g. 1, 2, 3\n"
		"     First coordinate is row, second is column, third is grid\n"
		"     Valid numbers are 1 - 4\n"
		"   - Enter 'reset' to begin a new game\n"
		"   - Enter 'quit' to terminate the program\n"
		"\n";
}

void GameManager::update() {
	board.printBoard();
	printTurn();
	getInput();
	nextTurn();
}

bool GameManager::quit() {
	return isOver;
}

void GameManager::printTurn() {
	switch (currentTurn) {
		case PLAYER_X:
			std::cout << "Player X's turn:\n";
			break;
		case PLAYER_O:
			std::cout << "Player O's turn:\n";
			break;
	}
}

void GameManager::getInput() {
	bool valid = false;
	std::string input;
	char front;

	while(!valid) {
		std::getline(std::cin, input);
		if (std::cin && !input.empty()) {		// Check to make sure input was recieved and it is not empty.
			front = input.front();
			if (front > 47 && front < 58) {		// If the first char is a digit, attempt to read in coordinates.
				valid = readNumbers(input);
			}
			else {								// Otherwise, attempt to read in a command.
				valid = readLetters(input);
			}
		}
		else {
			std::cerr <<
				"Missing input or possibly some other issue. Valid input is:\n"
				"   Three numbers between 1 and 4 separated by a space (e.g. 1 2 3)\n"
				"   'reset', without quotes, to begin a new game\n"
				"   'exit', without quotes, to terminate the program\n";
		}
		std::cin.clear();
	} 
}

bool GameManager::readNumbers(const std::string& s) {
	std::vector<std::string> tokens;
	std::vector<int> coordinates;
	int coord;

	split(s, ' ', tokens);						// Split the coordinates
	if (tokens.size() != 3) {					// Check that the number of coordinates is 3
		std::cerr << "Number of coordinates must be three.\n";
		return false;
	}

	for each (std::string s in tokens) {		// Check every coordinate
		try {									
			coord = stoi(s);
		}
		catch (std::exception e) {				// Check if it's a number or readable (potentially too large for an int)
			std::cerr << s << " could not be read into an int.\n"
				"Details: " << e.what();
			return false;
		}

		if (coord < 1 || coord > 4) {			// Check if it's in the board's rangfe
			std::cerr << coord << " is not a valid coordinate. Valid coordinates go from 1 to 4.\n";
			return false;
		}
	}

	if (board(coordinates) != EMPTY) {			// Check that the given coordinates are empty
		std::cerr << "The coordinate " << coordinates[0] << ' ' << coordinates[1] << ' ' << coordinates[2] << " is already filled.\n";
		return false;
	}

	return true;
}

bool GameManager::readLetters(const std::string& s) {
	if (s.compare("reset") == 0) {
		std::cout << "Restarting game...\n\n";
		return true;
	}
	else if (s.compare("exit") == 0) {
		isOver = true;
		return true;
	}
	else {
		std::cout << s + " was not valid input.\n";
		return false;
	}
}


void GameManager::nextTurn() {
	currentTurn *= -1;
	turnCounter++;
}