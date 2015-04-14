#include "CuboidArray.h"


CuboidArray::CuboidArray() {
	toZero();
}


CuboidArray::~CuboidArray() {
}

void CuboidArray::toZero() {
	for (int i = 0; i < SIZE; i++) {
		elements[i] = 0;
	}
}

const int& CuboidArray::operator()(const int row, const int col, const int slice) {
	assert(row >= 0 && row < LENGTH);
	assert(col >= 0 && col < LENGTH);
	assert(slice >= 0 && slice < LENGTH);
	return elements[(row * LENGTH) + (col)+(slice * LENGTH_SQUARE)];
}

std::ostream& operator<<(std::ostream& out, const CuboidArray& ca) {
	int sliceOffset, index;

	for (int i = 0; i < 4; i++) {										// Loops through the rows.
		sliceOffset = 0;												// Resets the sliceOffset

		for (int j = 0; j < 16; j++) {									// Loops through the 16 elements of each row of the formatted string
			index = i * ca.LENGTH + j + sliceOffset;					// Calculate the index using the row i, the column j, and the sliceOffset
			out << '[' << std::to_string(ca.elements[index]) << ']';	// Append the element to the stream

			if ((j + 1) % 4 == 0) {										// At the end of every 4 elements
				out << "  ";											// Include two blank spaces for visual clarity
				sliceOffset += 12;										// Add 12 to the offset, since there are 16 elements per slice, 4 of which were printed already
			}
		}
		out << std::endl;												// Start on a new line for the next row
	}

	return out;
}