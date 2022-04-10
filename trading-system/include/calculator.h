#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include <string>

using namespace std;

enum class TokenType : char {
    kNumber,
    kEnd,
    kError,
    kLp    = '(',
    kRp    = ')',
    kPlus  = '+',
    kMinus = '-',
    kMul   = '*',
    kDiv   = '/',
};

class Evaluator {
private:
    string    expr;
    size_t    iter;
    size_t    expressionlength;
    TokenType current;

    TokenType TokenGet();

    double Primary(bool get);
    double Term(bool get);
    double Expression(bool get);
    double Number();

public:
    Evaluator(const string expression) : expr(expression), iter(0), expressionlength(expression.length()), current(TokenType::kEnd) {}
    double Calculate();
};

#endif  // !CALCULATOR_H_