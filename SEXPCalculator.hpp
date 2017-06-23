/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
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

