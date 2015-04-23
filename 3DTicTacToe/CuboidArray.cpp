/*
	Author: Francis Yuan
	Date: 4/12/2015
*/
#include "CuboidArray.h"


CuboidArray::CuboidArray() {
	fillDirections();
}


CuboidArray::~CuboidArray() {
}

const int& CuboidArray::operator()(const int row, const int col, const int slice) const {
	assert(row >= 0 && row < LENGTH);
	assert(col >= 0 && col < LENGTH);
	assert(slice >= 0 && slice < LENGTH);
	return elements[(row * LENGTH) + (col)+(slice * LENGTH_SQUARE)];
}

// This is a trick from Effective C++ to avoid code duplication for const and non-const overloaded operators
int& CuboidArray::operator()(const int row, const int col, const int slice) {
	return
		const_cast<int&>(
			static_cast<const CuboidArray&>(*this).operator()(row, col, slice)
		);
}

const int& CuboidArray::operator()(const IntVector3& coords) const {
	int row = coords[0];
	int col = coords[1];
	int slice = coords[2];

	assert(row >= 0 && row < LENGTH);
	assert(col >= 0 && col < LENGTH);
	assert(slice >= 0 && slice < LENGTH);
	return elements[(row * LENGTH) + (col)+(slice * LENGTH_SQUARE)];
}

// See above for explanation of this function's wretched existence.
int& CuboidArray::operator()(const IntVector3& coords)  {
	return
		const_cast<int&>(
			static_cast<const CuboidArray&>(*this).operator()(coords)
		);
}


std::ostream& operator<<(std::ostream& out, const CuboidArray& ca) {
	int sliceOffset, index;

	for (int i = 0; i < ca.LENGTH; ++i) {									// Loops through the rows.
		sliceOffset = 0;												// Resets the sliceOffset

		for (int j = 0; j < 16; ++j) {									// Loops through the 16 elements of each row of the formatted string
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

void CuboidArray::zero() {
	for (int i = 0; i < SIZE; ++i) {
		elements[i] = 0;
	}
}

// See overloaded << operator for loop explanation.
std::string CuboidArray::printBoard() const{
	std::string output;
	int sliceOffset, index;
	char convertedChar;

	for (int i = 0; i < LENGTH; ++i) {								
		sliceOffset = 0;												

		for (int j = 0; j < LENGTH_SQUARE; ++j) {									
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

			output += {'[', convertedChar, ']'};
			if ((j + 1) % LENGTH == 0) {										
				output += "   ";										
				sliceOffset += 12;										
			}
		}
		output += '\n';
	}
	output += '\n';
	return output;
}


bool CuboidArray::findLineOfFour(const int x, const IntVector3& coords) const {
	int sum;
	for (auto const& dir : directions) {	
		sum = 1;

		sum += sumInDirection(x, coords, dir);
		sum += sumInDirection(x, coords, dir.inverse());

		if (sum == 4) {
			return true;
		}
	}
	return false;
}

int CuboidArray::sumInDirection(const int x, const IntVector3& coords, const IntVector3& dir) const {
	bool inBounds = true;
	IntVector3 position(coords);
	int sum = 0;

	while (inBounds) {
		position += dir;

		for (int i = 0; i < 3; ++i) {			// First check if the position is moving out of bounds.
			if (position[i] < 0 || position[i] >= LENGTH) {
				return sum;
			}
		}

		if (this->operator()(position) == x) {	// Then increment the sum if this position gives a match.
			++sum;
		}
	}

	return sum;
}

void CuboidArray::fillDirections() {
	directions.emplace_back(IntVector3{ 1, 0, 0 });
	directions.emplace_back(IntVector3{ 0, 1, 0 });
	directions.emplace_back(IntVector3{ 0, 0, 1 });
	directions.emplace_back(IntVector3{-1, 1, 0 });
	directions.emplace_back(IntVector3{ 1, 1, 0 });
	directions.emplace_back(IntVector3{ 0, 1,-1 });
	directions.emplace_back(IntVector3{ 0, 1, 1 });
	directions.emplace_back(IntVector3{-1, 0, 1 });
	directions.emplace_back(IntVector3{ 1, 0, 1 });
	directions.emplace_back(IntVector3{-1, 1, 1 });
	directions.emplace_back(IntVector3{ 1, 1, 1 });
	directions.emplace_back(IntVector3{-1, 1,-1 });
	directions.emplace_back(IntVector3{ 1, 1,-1 });
}
