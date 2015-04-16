/*
	Author: Francis Yuan
	Date: 4/15/2015
 */
#pragma once
#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>
#include <sstream>

/*
	Tokenizes a string along a delimiter and inputs the resulting tokens into a vector. Also returns that vector.
 */
std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string>& tokens);

#endif