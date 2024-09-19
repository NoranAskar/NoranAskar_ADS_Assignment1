// SimpleCalculator.cpp
#include "SimpleCalculator.h"
#include "Stackt.h"
#include <iostream>
#include <cctype>  // for isdigit function
#include <sstream> // for istringstream
#include <stdexcept> // for exception handling

using namespace std;

SimpleCalculator::SimpleCalculator() {}

//function to return true if ch is an arithmetic operator
bool SimpleCalculator::isOperator(char ch) {
    // Student Task: Implement the isOperator function
    // This function should return true if the character 'ch' is one of the arithmetic operators.
    // Supported operators are: +, -, *, /, %
    // Use a simple comparison to check if 'ch' matches any of these operators.
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%';
}

//function to declare precedence of different arithmetic operators
int SimpleCalculator::precedence(char op) {
    // Student Task: Implement the precedence function
    // This function should return the precedence of the operator 'op'.
    // Precedence rules:
    // - Return 1 for + and -
    // - Return 2 for *, /, and %
    // - Return 0 for any other character (default case)
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/' || op == '%')
        return 2;
    return 0;
}

//function to perform the operation mentioned
double SimpleCalculator::applyOperation(double a, double b, char op) {
    // Student Task: Implement the applyOperation function
    // This function should perform arithmetic operations based on the operator 'op'.
    // Steps:
    // - Use a switch statement to handle each operator: +, -, *, /, %
    // - For each case, perform the corresponding arithmetic operation on 'a' and 'b'
    // - If 'op' is '/', check if 'b' is 0 to prevent division by zero; if so, throw a runtime_error
    // - If 'op' is '%', convert 'a' and 'b' to integers before applying the modulus operation
    // - Return the result of the operation
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) throw runtime_error("Division by 0");
        return a / b;
        case '%':
            if (b == 0) throw runtime_error("Division by 0");
        return static_cast<int>(a) % static_cast<int>(b);
        default: throw runtime_error("Not an operator");
    }
}

//function to create the postfix expression from the entered infix one
string SimpleCalculator::infixToPostfix(const string& infix) {
    // Student Task: Implement the infixToPostfix function
    // This function should convert an infix expression (e.g., "5+3*2") into a postfix expression (e.g., "5 3 2 * +").
    // Steps:
    // - Use a stack to store operators and parentheses during the conversion
    // - Iterate over each character in the input string 'infix'
    // - If the character is a digit, append it to the postfix string
    // - If the character is '(', push it onto the stack
    // - If the character is ')', pop from the stack to the postfix string until '(' is found
    // - If the character is an operator, pop from the stack to the postfix string while the top of the stack has higher or equal precedence
    // - After the loop, pop any remaining operators in the stack to the postfix string
    Stackt<char> operators(100); // Use Stackt here instead of Stack
    string postfix;
    string multidigit; //bonus
    for (size_t i = 0; i < infix.length(); ++i) {
        char ch = infix[i];
        if (isdigit(ch)) {
            multidigit += ch;
            while (i + 1 < infix.length() && isdigit(infix[i + 1])) {
                multidigit += infix[++i];
            }
            postfix += multidigit + ' ';
            multidigit.clear(); //assuming there'll be new numbers, this step is to clear before next number
        }
        else if (ch == '(') {
            operators.push(ch);
        }
        else if (ch == ')') {
            while (!operators.isEmpty() && operators.peek() != '(') {
                postfix += operators.pop();
                postfix += ' ';
            }
            operators.pop();
        }
        else if (isOperator(ch)) {
            while (!operators.isEmpty() && precedence(operators.peek()) >= precedence(ch)) {
                postfix += operators.pop();
                postfix += ' ';
            }
            operators.push(ch);
        }
    }
    while (!operators.isEmpty()) {
        postfix += operators.pop();
        postfix += ' ';
    }

    return postfix;
}

//function to solve the postfix expression created by the previous function
double SimpleCalculator::evaluatePostfix(const string& postfix) {
    // Student Task: Implement the evaluatePostfix function
    // This function should evaluate a postfix expression and return its result.
    // Steps:
    // - Use a stack to store numerical values during evaluation
    // - Split the postfix string into tokens using a string stream
    // - For each token:
    //   - If it is a number, convert it to double and push it onto the stack
    //   - If it is an operator, pop two numbers from the stack, apply the operator, and push the result back onto the stack
    // - The final result should be the only number left on the stack
    Stackt<double> values(100); // Use Stackt here instead of Stack
    stringstream ss(postfix);
    string token;

    while (ss >> token) {
        // If the token is a number, push it to the stack
        if (isdigit(token[0])) {
            values.push(stod(token));
        }
        // If the token is an operator, pop two values and apply the operation
        else if (isOperator(token[0])) {
            if (values.isEmpty())
                throw runtime_error("Invalid postfix expression");

            double b = values.pop();
            double a = values.pop();

            values.push(applyOperation(a, b, token[0]));
        }
    }

    if (values.isEmpty())
        throw runtime_error("Invalid postfix evaluation");

    return values.peek();
}

//function to show results (input, output, conversion, and final result)
void SimpleCalculator::calculate(const string& infix) {
    // This function is already implemented for you.
    // It handles input/output and coordinates the conversion from infix to postfix and the evaluation of the postfix expression.
    try {
        cout << "Input infix expression: " << infix << endl;
        string postfix = infixToPostfix(infix);
        cout << "Postfix: " << postfix << endl;
        double result = evaluatePostfix(postfix);
        cout << "Result: " << result << endl;
    } catch (const runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }
}