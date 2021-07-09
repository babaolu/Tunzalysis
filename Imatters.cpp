#include "Imatters.h"
#include "ErrorHandle.h"

std::map<std::string, double> varList;

Token::Token(std::string s)
	: typ{ Type::number }
{
	auto Var = varList.find(s);
	if (Var != varList.end())
		val.realVal = Var->second;
	else 
		expression_error("Nonexisting identifier: '" + s + "'");
}

void add_to_var(std::string s, double varVal)
{
	//double varVal;
	//std::cin >> varVal;

	auto ins_or_up = varList.insert_or_assign(s, varVal);
	std::cout << s << (ins_or_up.second ? " inserted!" : " updated!") << std::endl;
}

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
		else if (isalpha(charVal))
		{										// get the identifier name
			std::string varVal{ charVal };
			while (std::cin >> charVal && isalnum(charVal))		// identifier can only be alphanumeric
			{
				varVal += charVal;
			}
			std::cin.putback(charVal);
			tokenVec.push_back(Token{ varVal });
		}
		else
			tokenVec.push_back(Token{ charVal });
	}
}