#pragma once

#include <iostream>
#include <vector>


enum class Type { number, oprator };	// Either a number of an operator

class Token
{
	union Value					// Either a number or an operator
	{
		double realVal;
		char charVal;
	};
	Value val;

	Type typ;

public:
	Token(double d) : typ{ Type::number } { val.realVal = d; }
	Token(char c) : typ{ Type::oprator } { val.charVal = c; }

	Type getType() { return typ; }
	Value getValue(){ return val; }
};

void takeIn(std::vector<Token>&);			// Take in input and convert to Tokens
