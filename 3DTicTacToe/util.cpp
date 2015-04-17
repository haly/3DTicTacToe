/*
	Author: Francis Yuan
	Date: 4/15/2015
*/
#include "util.h"

std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string>& tokens) {
	std::stringstream ss(s);
	std::string newToken;

	while (std::getline(ss, newToken, delim)) {
		if (newToken.length() > 0) {
			tokens.push_back(newToken);
		}
	}
	return tokens;
}