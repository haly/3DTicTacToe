/*
	Author: Francis Yuan
	Date: 4/20/2015
*/
#pragma once
#ifndef VECTORINT3_H
#define VECTORINT3_H

/*
	A limited vector, holding only 3 ints, for the sake of supporting certain vector arithmatic and
	providing increased coding convenience.
 */
class VectorInt3 {
public:
	inline VectorInt3() {}
	inline VectorInt3(int x, int y, int z) {
		triple[0] = x;
		triple[1] = y;
		triple[2] = z;
	}
	inline ~VectorInt3() {}

	int& operator[](int index) {
		assert(index >= 0 && index < 3);
		return triple[index];
	}

	const int& operator[](int index) const {
		assert(index >= 0 && index < 3);
		return triple[index];
	}

	inline VectorInt3 operator+(const VectorInt3& rhs) {
		return VectorInt3(triple[0] + rhs[0], triple[1] + rhs[1], triple[2] + rhs[2]);
	}

	inline VectorInt3 operator+=(const VectorInt3& rhs) {
		triple[0] += rhs[0];
		triple[1] += rhs[1];
		triple[2] += rhs[2];
		return *this;
	}

	inline VectorInt3 inverse() const {
		return VectorInt3(triple[0] * -1, triple[1] * -1, triple[2] * -1);
	}

	std::string toString() {
		std::string s = std::to_string(triple[0]) + ' ' + std::to_string(triple[1]) + ' ' + std::to_string(triple[2]);
		return s;
	}

private:
	int triple[3];
};

#endif