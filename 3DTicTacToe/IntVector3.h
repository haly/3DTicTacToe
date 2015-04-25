/*
	Author: Francis Yuan
	Date: 4/20/2015
*/
#pragma once
#ifndef IntVector3_H
#define IntVector3_H

#include <string>
#include <assert.h>

/*
	A limited vector, holding only 3 ints, for the sake of supporting certain vector arithmatic and
	providing increased coding convenience.
 */
class IntVector3 {
public:
	IntVector3() {}
	IntVector3(int x, int y, int z) {
		triple[0] = x;
		triple[1] = y;
		triple[2] = z;
	}
	~IntVector3() {}

	int& operator[](int index) {
		assert(index >= 0 && index < 3);
		return triple[index];
	}

	const int& operator[](int index) const {
		assert(index >= 0 && index < 3);
		return triple[index];
	}

	IntVector3 operator+=(const IntVector3& rhs) {
		triple[0] += rhs[0];
		triple[1] += rhs[1];
		triple[2] += rhs[2];
		return *this;
	}

	IntVector3 operator+(const IntVector3& rhs) {
		return IntVector3(*this += rhs);
	}

	IntVector3 inverse() const {
		return IntVector3(triple[0] * -1, triple[1] * -1, triple[2] * -1);
	}

	std::string toString() {
		std::string s = std::to_string(triple[0]) + ' ' + std::to_string(triple[1]) + ' ' + std::to_string(triple[2]);
		return s;
	}

private:
	int triple[3];
};

#endif