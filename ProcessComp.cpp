#include "ProcessComp.h"

void startProc()
try
{
	char firstChar;
	bool loopVar = true;

	while (loopVar)
	{
		std::cout << ">>";					// signifying the prompt

		std::cin >> firstChar;

		if (isalpha(firstChar))
		{
			std::cin.putback(firstChar);
			loopVar = processCommand();
		}
		else
		{
			std::cin.putback(firstChar);
			processArith();

		}
	}
}
catch (BadExpression& bex)
{
	std::cout << bex.message << '\n';
	startProc();
}

bool processCommand()
{
	std::string s;
	if (std::cin >> s && s._Equal("quit"))
		return false;

	std::cout << s << '\n';
	return true;
}

void processArith()
{
	double number = 0;
	unsigned int counter = 0;

	std::vector<Token> tokenVec;
	takeIn(tokenVec);
	
	for (Token v : tokenVec)
	{
		if (v.getType() == Type::number) std::cout << v.getValue().realVal << ' ';
		else std::cout << v.getValue().charVal << ' ';
	}

	number = add_sub(tokenVec, counter);

	std::cout << '\n' << number << '\n';	
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

		case'(':
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