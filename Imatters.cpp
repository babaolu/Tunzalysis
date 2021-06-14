#include "Imatters.h"

void takeIn(std::vector<Token>& tokenVec)
{
	char charVal;
	double numVal;
	while (std::cin >> charVal)
	{
		if (charVal == ';')
		{
			tokenVec.push_back(Token{ charVal });
			break;
		}

		if (isdigit(charVal))			// If at the beginning of a number
		{
			std::cin.putback(charVal);
			std::cin >> numVal;
			tokenVec.push_back(Token{ numVal });
		}
		else
			tokenVec.push_back(Token{ charVal });
	}
}