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
 * File:   SEXPCalculator.hpp
 * Author: syafiq
 *
 * Created on June 23, 2017, 4:22 PM
 */

#ifndef SEXPCALCULATOR_HPP
#define SEXPCALCULATOR_HPP

#include <string>
#include <vector>
#include <map>
#include <functional>

namespace SYAFIQ
{
    //Unary Functions
    double ERRORFUNCTION(double op1);
    double LN(double op1);
    double LOG(double op1);
    double SQRT(double op1);
    double CBRT(double op1);
    double TGAMMA(double op1);
    double LGAMMA(double op1);
    double ABS(double op1);
    double SINE(double op1);
    double COSINE(double op1);
    double EXPONENT(double op1);
    
    //Binary Functions
    double ADD(double op1, double op2);
    double SUB(double op1, double op2);
    double MUL(double op1, double op2);
    double DIV(double op1, double op2);
    double HYPOT(double op1, double op2);
    double POWER(double op1, double op2);
    

    class SEXPCalculator 
    {
    public:
        SEXPCalculator();
        SEXPCalculator(const SEXPCalculator& orig);
        double evaluateExpression(const std::string& expression, std::map<std::string, double> &row);

        virtual ~SEXPCalculator();
    private:
        std::map<std::string, std::function<double(double)>> UnaryFunctions;
	std::map<std::string, std::function<double(double, double)>> BinaryFunctions;

    };

}

#endif /* SEXPCALCULATOR_HPP */

