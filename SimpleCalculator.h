// SimpleCalculator.h
#ifndef SIMPLECALCULATOR_H
#define SIMPLECALCULATOR_H

#include <string>
#include "Stackt.h"

using namespace std;

class SimpleCalculator {
public:
    SimpleCalculator();
    string infixToPostfix(const string& infix);
    double evaluatePostfix(const string& postfix);
    void calculate(const string& infix);

private:
    bool isOperator(char ch);
    int precedence(char op);
    double applyOperation(double a, double b, char op);
};

#endif // SIMPLECALCULATOR_H