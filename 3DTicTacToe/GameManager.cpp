/*
	Author: Francis Yuan
	Date: 4/14/2015
*/
#include "GameManager.h"


GameManager::GameManager() : board() {
}


GameManager::~GameManager() {
}

void GameManager::initialize() {
	board.zero();
	turnCounter = 1;
	currentTurn = PLAYER_X;
	gameState = GAME_COMMENCE;
	quitFlag = false;
}

void GameManager::introduction() const {
	std::cout <<
		"3D TicTacToe, by Francis Yuan\n"
		"Enter the number of human players.\n"
		"'1' to play against an AI.\n"
		"'2' to play against another local player.\n"
		"\n"
		"Other commands that can be entered at any time:\n"
		"'reset' to return to this menu.\n"
		"'quit' to quit the program.\n"
		"\n";
}

void GameManager::setup() {
	std::cout <<
		"Setup"
		"Enter the number of human players: (1, 2)";

	std::string s;
	while (std::cin >> s) {
		try {
			numberOfHumans = stoi(s);
		}
		catch (std::exception e) {
			std::cerr << "Input is either not a number or too large.\n";
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	// TODO: Fill the rest of the logic

}

void GameManager::update() {
	if (gameState == GAME_COMMENCE) {
		std::cout << board.printBoard();
		printTurn();
	}
	getInput();
}

bool GameManager::quit() const {
	return quitFlag;
}

void GameManager::printTurn() {
	std::cout << ((currentTurn == PLAYER_X) ? "Player X's turn:\n" : "Player O's turn:\n");
}

void GameManager::nextTurn() {
	currentTurn *= -1;
	turnCounter++;
}

void GameManager::getInput() {
	bool valid = false;
	std::string input;
	std::vector<std::string> tokens;

	while(!valid) {
		std::getline(std::cin, input);
		if (std::cin && !input.empty()) {		// Check to make sure input was recieved and it is not empty.
			split(input, ' ', tokens);
			switch (tokens.size()) {
				case 1:							// Only one input, check for valid commands.
					valid = readCommand(tokens);
					break;
				case 3:							// Three inputs, check for valid coordinates.
					valid = readCoords(tokens);
					break;
				default:
					std::cerr << "Invalid number of inputs.\n";
			}
		}
		else {
			std::cerr << "Missing input or possibly some other issue.\n";
		}
		std::cin.clear();
		tokens.clear();
	} 
}

bool GameManager::readCommand(const std::vector<std::string>& tokens) {
	assert(tokens.size() == 1);

	if (tokens[0].compare("reset") == 0) {
		std::cout << "Restarting game...\n\n";
		initialize();
		return true;
	}
	else if (tokens[0].compare("quit") == 0) {
		quitFlag = true;
		return true;
	}
	else {
		std::cout << '\'' << tokens[0] << '\'' << " was not a valid command.\n";
		return false;
	}
}

bool GameManager::readCoords(const std::vector<std::string>& tokens) {
	assert(tokens.size() == 3);

	IntVector3 coordinates;
	int coord;

	for (unsigned int i = 0; i < tokens.size(); i++) {
		try {									
			coord = stoi(tokens[i]);
		}
		catch (std::exception e) {				// Check if token is a number or readable (potentially too large for an int).
			std::cerr << "The entry "  << coord << " could not be read into an int.\n";
			return false;
		}

		if (coord < 1 || coord > 4) {			// Check if token in the board's range.
			std::cerr << "The entry " << coord << " is out of bounds. Valid coordinates go from 1 to 4.\n";
			return false;
		}

		coordinates[i] = coord - 1;
	}

	if (board(coordinates) != EMPTY) {			// Check that the given coordinates are empty.
		std::cerr << "The coordinate (" << (coordinates[0] + 1) << ' ' << (coordinates[1] + 1)<< ' ' << (coordinates[2] + 1)<< ") is already filled.\n";
		return false;
	}
	else {
		board(coordinates) = currentTurn;

		if (checkWinningMove(currentTurn, coordinates)) {
			gameState = PRE_GAME;
		}

		if (gameState == GAME_COMMENCE) {
			nextTurn();
		}
	}

	return true;
}

bool GameManager::checkWinningMove(const int& turn, const IntVector3& coords) {

	if (board.findLineOfFour(turn, coords)) {
		board.printBoard();
		std::string winner = (turn == PLAYER_X) ? "Player X" : "Player O";
		std::cout << winner << " is the winner! Type 'reset' to start a new game or 'quit' to close the program.\n";
		return true;
	}
	else if (turnCounter == MAX_TURNS) {
		board.printBoard();
		std::cout << "The game is a tie. Type 'reset' to start a new game or 'quit' to close the program.\n";
		return true;
	}
	return false;
}