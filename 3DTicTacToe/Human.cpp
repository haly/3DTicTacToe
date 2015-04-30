#include "Human.h"

Human::Human() : Player("Human") {
}

Human::Human(std::string name) : Player(name){
}

Human::~Human() {
}

IntVector3 Human::getMove(const int& myTurn, const CuboidArray& ca) {
	std::cout << "Enter three coordinates. (e.g. 1 2 3)\n";

	std::string s;
	std::vector<std::string> tokens;
	IntVector3 coordinates;

	while (std::getline(std::cin, s)) {					// Get input from stream.
		std::cin.clear();
		tokens.clear();

		split(s, ' ', tokens);							// Tokenize input.
			
		if (tokens.size() != 3) {						// Check input for right number of coordinates.
			std::cerr << "Wrong number of inputs.\n";
			continue;
		}
		else {
			bool validCoords = true;							

			for (unsigned int i = 0; i < tokens.size(); i++) {	
				try {
					coordinates[i] = stoi(tokens[i]) - 1;	// Attempt integer conversion.
				}
				catch (std::exception e) {	
					std::cerr << "The entry " << tokens[i] << " could not be read.\n";
					validCoords = false;
					continue;
				}

				if (!ca.checkBounds(coordinates[i])) {		// Check that input is within bounds of the board.
					std::cerr << "The entry " << coordinates[i] << " is out of bounds.\n";
					validCoords = false;
					continue;
				}
			}

			if (!validCoords) {
				continue;
			}
			else if (ca(coordinates) != EMPTY) {		// Check that the coordinate is empty.
				std::cerr << "The coordinate (" << coordinates.toStringOffset() << ") is already filled.\n";
				continue;
			}

			return coordinates;
		}
	}
	return{ -1, -1, -1 };
}