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
	currentTurn = PLAYER_X;
	turnCounter = 1;
	gameOver = false;
	quitFlag = false;
}

void GameManager::introduction() const {
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
	if (!gameOver) {
		board.printBoard();
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
			std::cerr <<
				"Missing input or possibly some other issue. Valid input is:\n"
				"   Three numbers between 1 and 4 separated by a space (e.g. 1 2 3).\n"
				"   'reset', without quotes, to begin a new game.\n"
				"   'quit', without quotes, to terminate the program.\n";
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

	VectorInt3 coordinates;
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
		checkGameOver(currentTurn, coordinates);
		if (!gameOver) {
			nextTurn();
		}
	}

	return true;
}

void GameManager::checkGameOver(const int& turn, const VectorInt3& coords) {

	if (board.findLineOfFour(turn, coords)) {
		gameOver = true;
		std::string winner = (turn == PLAYER_X) ? "Player X" : "Player O";
		std::cout << winner << " is the winner! Type 'reset' to start a new game or 'quit' to close the program.\n";
	}
	else if (turnCounter == MAX_TURNS) {
		gameOver = true;
		std::cout << "The game is a tie. Type 'reset' to start a new game or 'quit' to close the program.\n";
	}
}