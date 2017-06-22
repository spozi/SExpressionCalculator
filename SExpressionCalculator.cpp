//Copyright 2017 Muhammad Syafiq Mohd Pozi

//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <stack>
#include <map>
#include <functional>
#include <cstdarg>
#include <cctype>


using namespace std;

//Split into token
template<typename Out>
void split(const std::string &s, char delim, Out result)
{
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) 
	{
		*(result++) = item;
	}
}

std::vector<std::string> split(const std::string &s, char delim) 
{
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}

//Unary
double ERRORFUNCTION(double op1)
{
	return std::erf(op1);
}

double LN(double op1)
{
	return std::log(op1);
}

double LOG(double op1)
{
	return std::log10(op1);
}

double SQRT(double op1)
{
	return std::sqrt(op1);
}

double CBRT(double op1)
{
	return std::cbrt(op1);
}

double TGAMMA(double op1)
{
	return std::tgamma(op1);
}

double LGAMMA(double op1)
{
	return std::lgamma(op1);
}

double ABS(double op1)
{
	return std::abs(op1);
}

double SINE(double op1)
{
	return std::sin(op1);
}

double COSINE(double op1)
{
	return std::cos(op1);
}

double EXPONENT(double op1)
{
	return std::exp(op1);
}


//Binary
double ADD(double op1, double op2)
{
	return op1 + op2;
}

double SUB(double op1, double op2)
{
	return op1 - op2;
}

double MUL(double op1, double op2)
{
	return op1 * op2;
}

double DIV(double op1, double op2)
{
	if (std::fabs(op2) < 0.001) return 1.0;
	else return (double)op1 / (double)op2;
}

double HYPOT(double op1, double op2)
{
	return std::hypot(op1, op2);
}

double POWER(double op1, double op2)
{
	return std::pow(op1, op2);
}

bool isNumeric(const std::string& input)
{
	double x;
	std::stringstream ss(input);
	ss >> x;
	if (ss.fail())
		return false;
	else
		return true;
}


int main(int argc, char **argv)
{

	//Initialize functions
	std::map<std::string, std::function<double(double)>> UnaryFunctions;
	std::map<std::string, std::function<double(double, double)>> BinaryFunctions;

	UnaryFunctions["ERRORFUNCTION"] = ERRORFUNCTION;
	UnaryFunctions["LN"] = LN;
	UnaryFunctions["LOG"] = LOG;
	UnaryFunctions["SQRT"] = SQRT;
	UnaryFunctions["CBRT"] = CBRT;
	UnaryFunctions["TGAMMA"] = TGAMMA;
	UnaryFunctions["LGAMMA"] = LGAMMA;
	UnaryFunctions["ABS"] = ABS;
	UnaryFunctions["SINE"] = SINE;
	UnaryFunctions["COSINE"] = COSINE;
	UnaryFunctions["EXPONENT"] = EXPONENT;



	BinaryFunctions["ADD"] = ADD;
	BinaryFunctions["SUB"] = SUB;
	BinaryFunctions["MUL"] = MUL;
	BinaryFunctions["DIV"] = DIV;
	BinaryFunctions["HYPOT"] = HYPOT;
	BinaryFunctions["POWER"] = POWER;


	std::cout << "Finish initializing function\n";






	double X1 = -2.4;
	double X2 = 3.6;

	std::vector<std::vector<std::pair<std::string, double>>> data; //row x column
	std::vector<std::pair<std::string, double>> row; //data consists of multiple rows
	row.push_back(std::make_pair("X1", X1));
	row.push_back(std::make_pair("X2", X2));
	data.push_back(row);
	//std::cout << data.size() << "\n";

	std::string expr = "(MUL X1 X2)";	//This is a test
	expr.erase(std::remove(expr.begin(), expr.end(), '('), expr.end());
	expr.erase(std::remove(expr.begin(), expr.end(), ')'), expr.end());
	std::vector<std::string> results = split(expr, ' ');



	//Replace results vector
	for (int i = 0; i < data.size(); ++i)
	{
		//Initialize substitute vector
		std::vector<std::string> substitute(results);

		//Replace every variable
		for (unsigned int j = 0; j < data[i].size(); ++j)
		{
			//Get the value
			std::pair<std::string, double> X = data[i][j];
			std::replace(substitute.begin(), substitute.end(), X.first, to_string(X.second));	//Replace
		}

		//Evaluate the substitute expression
		std::stack<double> operands;
		for(int j = substitute.size() - 1; j >= 0; --j) //unsigned int on this loop break
		{
			if (isNumeric(substitute[j]))
			{
				//std::cout << substitute[j] << "\n";
				double operand = 0.0;
				std::stringstream(substitute[j]) >> operand;
				operands.push(operand);
			}
			else
			{
				unsigned int numArguments = 0;
				double result = 0.0;
				//Is it in unary function?
				if (UnaryFunctions.find(substitute[j]) == UnaryFunctions.end())		numArguments = 2;		//If reach end, it is binary function
				else    numArguments = 1;

				if (numArguments == 1)
				{
					//retrieve the first value
					double op1 = operands.top();
					operands.pop();
					result = UnaryFunctions[substitute[j]](op1);
				}
				else
				{
					//retrieve the first and second value
					double op1 = operands.top();
					operands.pop();
					double op2 = operands.top();
					operands.pop();
					result = BinaryFunctions[substitute[j]](op1, op2);
				}

				if (std::isinf(result) || std::isnan(result))
					result = 0.001;
				operands.push(result);
			}
		}

		double finalResult = operands.top();
		std::cout << "Final Result: " << finalResult << "\n";
		break;
	}
	return 0;
}
