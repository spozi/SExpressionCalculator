/*
 MIT License
Copyright (c) 2017 Muhammad Syafiq Mohd Pozi
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

/* 
 * File:   SEXPCalculator.cpp
 * Author: syafiq
 * 
 * Created on June 23, 2017, 4:22 PM
 */

#include "SEXPCalculator.hpp"
#include <cstdarg>
#include <cctype>
#include <sstream>
#include <stack>
#include <cmath>
#include <functional>
#include <algorithm>
#include <string>
#include <iostream>

SYAFIQ::SEXPCalculator::SEXPCalculator() 
{
    UnaryFunctions["ERF"] = ERRORFUNCTION;
    UnaryFunctions["LN"] = LN;
    UnaryFunctions["LOG"] = LOG;
    UnaryFunctions["SQRT"] = SQRT;
    UnaryFunctions["CBRT"] = CBRT;
    UnaryFunctions["TGAMMA"] = TGAMMA;
    UnaryFunctions["LGAMMA"] = LGAMMA;
    UnaryFunctions["ABS"] = ABS;
    UnaryFunctions["SIN"] = SINE;
    UnaryFunctions["COS"] = COSINE;
    UnaryFunctions["EXP"] = EXPONENT;

    BinaryFunctions["ADD"] = ADD;
    BinaryFunctions["SUB"] = SUB;
    BinaryFunctions["MUL"] = MUL;
    BinaryFunctions["DIV"] = DIV;
    BinaryFunctions["HYPOT"] = HYPOT;
    BinaryFunctions["POWER"] = POWER; 
}

SYAFIQ::SEXPCalculator::SEXPCalculator(const SEXPCalculator& orig) 
{
    
}

SYAFIQ::SEXPCalculator::~SEXPCalculator() 
{
    
}

double SYAFIQ::SEXPCalculator::evaluateExpression(const std::string& expression, std::map<std::string, double> &row) //Data consists of a multiple rows of std::map<std::string, double>
{
    auto split = [](const std::string &s, char delim, auto result){
        std::stringstream ss;
        ss.str(s);
        std::string item;
        while (std::getline(ss, item, delim)) 
        {
            *(result++) = item;
        }
    };

    auto splitToVector = [&split](const std::string &s, char delim) {
        std::vector<std::string> elems;
        split(s, delim, std::back_inserter(elems));
        return elems;
    };
    
    auto isNumeric = [](const std::string& input){
	double x;
	std::stringstream ss(input);
	ss >> x;
	if (ss.fail())
            return false;
	else
            return true;
    };
    
    std::string expr(expression);
    expr.erase(std::remove(expr.begin(), expr.end(), '('), expr.end());
    expr.erase(std::remove(expr.begin(), expr.end(), ')'), expr.end());
    std::vector<std::string> results = splitToVector(expr, ' ');
    
    //Replace variable with values (in string)
    auto replaceVariableInExpressionWithValues = [](std::vector<std::string> &expression, std::map<std::string, double> row){
        for(int i = 0; i < expression.size(); ++i)
        {
            //Check if it inside row
            if(row.find(expression[i]) == row.end())
                continue;
            else
                expression[i] = std::to_string(row[expression[i]]);
        }
    };
    
    replaceVariableInExpressionWithValues(results, row);
    
    //Calculating
    //Evaluate from behind
    std::stack<double> operands;
    for(int j = results.size() - 1; j >= 0; --j) //unsigned int on this loop break
    {
        if (isNumeric(results[j]))
        {
            double operand = 0.0;
            std::stringstream(results[j]) >> operand;
            operands.push(operand);
        }
        else
        {
            unsigned int numArguments = 0;
            double result = 0.0;
            //Is it in unary function?
            if (UnaryFunctions.find(results[j]) == UnaryFunctions.end())    
                numArguments = 2;		//If reach end, it is binary function
            else    
                numArguments = 1;

            if (numArguments == 1)
            {
                //retrieve the first value
                double op1 = operands.top();
                operands.pop();
                result = UnaryFunctions[results[j]](op1);
            }
            else
            {
                //retrieve the first and second value
                double op1 = operands.top();
                operands.pop();
                double op2 = operands.top();
                operands.pop();
                result = BinaryFunctions[results[j]](op1, op2);
            }

            if (std::isinf(result) || std::isnan(result))
                result = 0.001;
            operands.push(result);
        }
    }
    
    double finalResult = operands.top();
    return finalResult;
}


//Unary
double SYAFIQ::ERRORFUNCTION(double op1)
{
    return std::erf(op1);
}

double SYAFIQ::LN(double op1)
{
    return std::log(op1);
}

double SYAFIQ::LOG(double op1)
{
    return std::log10(op1);
}

double SYAFIQ::SQRT(double op1)
{
    return std::sqrt(op1);
}

double SYAFIQ::CBRT(double op1)
{
    return std::cbrt(op1);
}

double SYAFIQ::TGAMMA(double op1)
{
    return std::tgamma(op1);
}

double SYAFIQ::LGAMMA(double op1)
{
    return std::lgamma(op1);
}

double SYAFIQ::ABS(double op1)
{
    return std::abs(op1);
}

double SYAFIQ::SINE(double op1)
{
    return std::sin(op1);
}

double SYAFIQ::COSINE(double op1)
{
    return std::cos(op1);
}

double SYAFIQ::EXPONENT(double op1)
{
    return std::exp(op1);
}


//Binary
double SYAFIQ::ADD(double op1, double op2)
{
    return op1 + op2;
}

double SYAFIQ::SUB(double op1, double op2)
{
    return op1 - op2;
}

double SYAFIQ::MUL(double op1, double op2)
{
    return op1 * op2;
}

double SYAFIQ::DIV(double op1, double op2)
{
    if (std::fabs(op2) < 0.001) return 1.0;
    else return (double)op1 / (double)op2;
}

double SYAFIQ::HYPOT(double op1, double op2)
{
    return std::hypot(op1, op2);
}

double SYAFIQ::POWER(double op1, double op2)
{
    return std::pow(op1, op2);
}
