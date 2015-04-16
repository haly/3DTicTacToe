/*
	Author: Francis Yuan
	Date: 4/12/2015
 */
#pragma once
#ifndef CUBOIDARRAY_H
#define CUBOIDARRAY_H

#include <cassert>
#include <string>
#include <iostream>
#include <vector>

/*
	CuboidArray is a 3D array (4*4*4) of ints representing the game board for a game of 3D TicTacToe.

	Terminology:
		-	Every item in the CuboidArray is called an element.
		-	Row and col correspond to the equivalent terms for a 0-indexed 2D matrix. The coordinates (0,1) indicate
			the element in the second column of the first row.
		-	Slice describes to the third dimension of the CuboidArray. Imagining a cuboid as a stack of matrices, 
			any single matrix is called a slice. The coordinates (0,1,2) thus describe the second column of the first row
			of the third slice. Visually, for a 2*2*3 3D array:

			[ ][ ]	[ ][ ]	[ ][x] <- (0,1,2)
			[ ][ ]	[ ][ ]	[ ][ ]

	Though CuboidArray represents a 3D array, internally it uses a 1D array of length 64 for storage of 
	all the elements.
 */
class CuboidArray {
public:
	/*
		Creates a new instance of CuboidArray, a 4*4*4 3D array with all elements set to 0.
	 */
	CuboidArray();		
	~CuboidArray();

	/*
		Allows read/write access to a single element using 3 coordinates.
	 */
	int& CuboidArray::operator()(const int row, const int col, const int slice);

	/*
		Allows read/write access to a single element using a <vector> of ints. The length must be 3.
	*/
	int& CuboidArray::operator()(const std::vector<int>& coords);

	/* 
		Prints the raw contents of the CuboidArray to a stream.
		The format is:

		[0][1][2][3]  [16][17][18][19]  [32][33][34][35]  [48][49][50][51]
		[4][5][6][7]  ...               ...               ...

		Where the numbers indicate the corresponding index of the internal array.
	 */
	friend std::ostream& operator<<(std::ostream& out, const CuboidArray& ca);

	/*
	Sets all elements to 0.
	*/
	void zero();

	/*
		Prints the game board to the console. The layout is the same as that of the overloaded << operator.
		1 is displayed as X.
		-1 is displayed as O.
		All other numbers are displayed as blank spaces.
	*/
	void printBoard();

	/*
		Checks to see if there are four of a number in a straight or diagonal row.
	 */
	bool isRowOfFour(int x);

private:
	static const size_t SIZE = 64;
	static const int LENGTH = 4;
	static const int LENGTH_SQUARE = 16;
	int elements[SIZE];						
};

#endif