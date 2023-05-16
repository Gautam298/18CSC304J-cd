#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

// Function to check if the character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to generate postfix expression from infix expression
std::string infixToPostfix(const std::string& infix) {
    std::string postfix;
    std::stack<char> operators;

    for (char c : infix) {
        if (c == ' ') {
            continue; // Skip spaces
        }
        else if (isOperator(c)) {
            while (!operators.empty() && operators.top() != '(' && ((c != '*' && c != '/') || (operators.top() != '+' && operators.top() != '-'))) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(c);
        }
        else if (c == '(') {
            operators.push(c);
        }
        else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                operators.pop();
            }
            operators.pop(); // Discard '('
        }
        else {
            postfix += c;
        }
    }

    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }

    return postfix;
}

// Function to generate prefix expression from infix expression
std::string infixToPrefix(const std::string& infix) {
    std::string reversedInfix(infix.rbegin(), infix.rend());
    std::string prefix;
    std::stack<char> operators;

    for (char c : reversedInfix) {
        if (c == ' ') {
            continue; // Skip spaces
        }
        else if (isOperator(c)) {
            while (!operators.empty() && operators.top() != ')' && ((c != '*' && c != '/') || (operators.top() != '+' && operators.top() != '-'))) {
                prefix += operators.top();
                operators.pop();
            }
            operators.push(c);
        }
        else if (c == ')') {
            operators.push(c);
        }
        else if (c == '(') {
            while (!operators.empty() && operators.top() != ')') {
                prefix += operators.top();
                operators.pop();
            }
            operators.pop(); // Discard ')'
        }
        else {
            prefix += c;
        }
    }

    while (!operators.empty()) {
        prefix += operators.top();
        operators.pop();
    }

    std::reverse(prefix.begin(), prefix.end());

    return prefix;
}

int main() {
    std::string infixExpression;

    std::cout << "Enter an infix expression: ";
    std::getline(std::cin, infixExpression);

    std::string postfixExpression = infixToPostfix(infixExpression);
    std::string prefixExpression = infixToPrefix(infixExpression);

    std::cout << "Postfix Expression: " << postfixExpression << std::endl;
    std::cout << "Prefix Expression: " << prefixExpression << std::endl;

    return 0;
}
