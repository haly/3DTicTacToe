/*
	Author: Francis Yuan
	Date: 4/12/2015
*/
#include "CuboidArray.h"


CuboidArray::CuboidArray() {
}


CuboidArray::~CuboidArray() {
}

int& CuboidArray::operator()(const int row, const int col, const int slice) {
	assert(row >= 0 && row < LENGTH);
	assert(col >= 0 && col < LENGTH);
	assert(slice >= 0 && slice < LENGTH);
	return elements[(row * LENGTH) + (col) + (slice * LENGTH_SQUARE)];
}

int& CuboidArray::operator()(const std::vector<int>& coords) {
	assert(coords.size() == 3);
	
	int row = coords[0];
	int col = coords[1];
	int slice = coords[2];

	assert(row >= 0 && row < LENGTH);
	assert(col >= 0 && col < LENGTH);
	assert(slice >= 0 && slice < LENGTH);
	return elements[(row * LENGTH) + (col) + (slice * LENGTH_SQUARE)];
}

void CuboidArray::zero() {
	for (int i = 0; i < SIZE; i++) {
		elements[i] = 0;
	}
}

// See overloaded << operator for loop explanation.
void CuboidArray::printBoard() const{
	int sliceOffset, index;
	char convertedChar;

	for (int i = 0; i < 4; i++) {								
		sliceOffset = 0;												

		for (int j = 0; j < 16; j++) {									
			index = i * LENGTH + j + sliceOffset;					

			switch (elements[index]) {		// Determine the correct char to print based on the element.
				case 1:
					convertedChar = 'X';
					break;
				case -1:
					convertedChar = 'O';
					break;
				default:
					convertedChar = ' ';
			}

			std::cout << '[' << convertedChar << ']';	
			if ((j + 1) % 4 == 0) {										
				std::cout << "   ";										
				sliceOffset += 12;										
			}
		}
		std::cout << '\n';											
	}
	std::cout << '\n';
}

std::ostream& operator<<(std::ostream& out, const CuboidArray& ca) {
	int sliceOffset, index;

	for (int i = 0; i < 4; i++) {										// Loops through the rows.
		sliceOffset = 0;												// Resets the sliceOffset

		for (int j = 0; j < 16; j++) {									// Loops through the 16 elements of each row of the formatted string
			index = i * ca.LENGTH + j + sliceOffset;					// Calculate the corresponding index using the row i, the column j, and the sliceOffset
			out << '[' << std::to_string(ca.elements[index]) << ']';	// Append the element to the stream between square brackets
			if ((j + 1) % 4 == 0) {										// At the end of every 4 elements
				out << "   ";											// Include some space for visual clarity
				sliceOffset += 12;										// Add 12 to the offset, since there are 16 elements per slice, 4 of which were printed already
			}
		}
		out << '\n';													// Start on a new line for the next row
	}

	return out;
}