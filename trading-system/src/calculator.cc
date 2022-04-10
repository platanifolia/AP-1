#include "calculator.h"

#include <cctype>
#include <iostream>

TokenType Evaluator::TokenGet() {
    if (iter == expressionlength)
        return TokenType::kEnd;

    char ch = expr[iter];

    switch (ch) {
    case 0:
        return TokenType::kEnd;
    case '(':
    case ')':
    case '*':
    case '/':
    case '+':
    case '-':
        iter++;
        return static_cast< TokenType >(ch);
    case '.':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        // be careful with the iter should be plused after the return
        return TokenType::kNumber;
    case ' ':
        iter++;
        return TokenGet();
    default:
        // TODO: finish error handling
        return TokenType::kError;
    }
}

double Evaluator::Number() {
    double value{ 0 };
    string numberbuffer;
    while (isdigit(expr[iter]) || expr[iter] == '.') {
        numberbuffer.push_back(expr[iter]);
        iter++;
        current = TokenGet();
    }
    value = stod(numberbuffer);
    return value;
}

double Evaluator::Primary(bool get) {
    if (get)
        current = TokenGet();

    switch (current) {
    case TokenType::kNumber: {
        double value = Number();
        // current = TokenGet();
        return value;
    }
    case TokenType::kLp: {
        double value = Expression(true);
        if (current != TokenType::kRp) {
            // TODO: finish error handling
            cerr << "\033[91mError: missing )\033[0m" << endl;
        }
        current = TokenGet();
        return value;
    }
    case TokenType::kMinus:
        return -Primary(true);
    default:
        // TODO: finish error handling
        cerr << "\033[91mError: Some bad\033[0m" << endl;
        return 0;
    }
}

double Evaluator::Term(bool get) {
    double value = Primary(get);
    // TokenType current = TokenGet();

    while (true) {
        switch (current) {
        case TokenType::kMul:
            value *= Primary(true);
            break;
        case TokenType::kDiv: {
            double divisor = Primary(true);
            if (divisor == 0) {
                // TODO: finish error handling
                cerr << "\033[91mError: Division by zero\033[0m" << endl;
            }
            value /= divisor;
            break;
        }
        default:
            return value;
        }
    }
}

double Evaluator::Expression(bool get) {
    double value = Term(get);
    // TokenType current = TokenGet();

    while (true) {
        switch (current) {
        case TokenType::kPlus:
            value += Term(true);
            break;
        case TokenType::kMinus:
            value -= Term(true);
            break;
        default:
            return value;
        }
    }
}

double Evaluator::Calculate() {
    if (expressionlength == 0)
        return 0;
    // cout << "Calculate: " << expr << endl;
    current = TokenGet();
    return Expression(false);
}