#include "ProcessComp.h"

void startProc()
try
{
	char firstChar;
	bool loopVar = true;

	while (loopVar)
	{
		std::vector<Token> tokenVec;		// tokens for a single operation are held here

		std::cout << "\n>>";					// signifying the prompt

		std::cin >> firstChar;

		if (isalpha(firstChar))
		{
			std::cin.putback(firstChar);
			loopVar = processCommand(tokenVec);
		}
		else
		{								// direct arithmetic evaluation
			std::cin.putback(firstChar);
			processArith(tokenVec);

		}
	}
}
catch (BadExpression& bex)
{
	std::cout << bex.message << '\n';
	startProc();
}

bool processCommand(std::vector<Token>& tokVec)
{
	std::string s;
	char charVal;
	while (std::cin >> charVal && isalnum(charVal))		// an identifier must be alphanumeric
	{
		s += charVal;
	}

	//if (s._Equal("quit"))			// quit to exit the program
	if (s == std::string{"quit"})			// quit to exit the program
		return false;

	switch (charVal)
	{
	case ':':
		std::cout << s << '\n';
		break;

	case '=':						// assigning value to variable
		add_to_var(s, processArith(tokVec));
		break;
		
	default:						// most probably when a variable appears first during an evaluation
		tokVec.push_back(Token{ s });
		std::cin.putback(charVal);
		processArith(tokVec);
		break;

	}

	return true;
}

double processArith(std::vector<Token>& tokVec)
{
	double number = 0;
	unsigned int counter = 0;

	takeIn(tokVec);
	
	/*for (Token v : tokVec)
	{
		if (v.getType() == Type::number) std::cout << v.getValue().realVal << ' ';
		else std::cout << v.getValue().charVal << ' ';
	}*/

	number = add_sub(tokVec, counter);

	std::cout << '\n' << number << '\n';

	return number;
}

double add_sub(std::vector<Token>& tokVec, unsigned int& i)
{
	double val = div_mult(tokVec, i);
	static int brack = 0;
	
	while (i < (tokVec.size() - 1))					// excluding the terminator (;)
	{
		switch (tokVec[i].getValue().charVal)
		{
		case '+':	case '-':
			val += div_mult(tokVec, i);
			break;

		case ')':
			bracket_check(val, "Opening bracket '(' missing");

		default:
			//return val;
			expression_error("Unknown identifier(s)");
		}
	}
	return val;
}

double div_mult(std::vector<Token>& tokVec, unsigned int& i)
{
	double val = primary(tokVec, i);

	while (i < (tokVec.size() - 1))					// excluding the terminator (;)
	{
		switch (tokVec[i].getValue().charVal)
		{
		case '*':
			val *= primary(tokVec, ++i);
			break;

		case '/':
			val /= primary(tokVec, ++i);
			break;

		case '%':
			val = (int) val % (int) primary(tokVec, ++i);
			break;

		case'(':						// bracket without any sign added infront automatically evaluates as multipication
			val *= primary(tokVec, i);
			break;

		default:
			return val;
		}
			//val = primary(tokVec, i);
	}
	return val;
}

double primary(std::vector<Token>& tokVec, unsigned int& i)
{
	double val;
	if (i < (tokVec.size() - 1))					// excluding the terminator (;)
	{
		if ((tokVec[i].getType() == Type::oprator))
		{
			switch (tokVec[i].getValue().charVal)
			{
			case '+':
				val = primary(tokVec, ++i);
				return val;

			case '-':
				val = -primary(tokVec, ++i);
				return val;

			case '(':
				try
				{
					add_sub(tokVec, ++i);
				}
				catch (BracketCheck& bc)
				{
					++i;
					return bc.val;
				}
				//if (tokVec[i].getValue().charVal == ')') ++i;
				expression_error("Enclosing bracket ')' missing");
				//return val;

			default:
				expression_error("Incorrect expression");
			}
		}
		else
		{
			val = tokVec[i].getValue().realVal;
			++i;
		}
	}
	return val;
}

































