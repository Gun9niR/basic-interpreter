#ifndef TOKEN_H
#define TOKEN_H

#include "consts.h"
#include "QDebug"

class Token {
public:
    TokenType type;
    QString lexeme;
    int value;

public:
    Token(TokenType t, QString l, int v = std::numeric_limits<int>::quiet_NaN());

    friend QDebug operator<<(QDebug dbg, const Token & token);
};

typedef shared_ptr<Token> TokenPtr;
#endif // TOKEN_H
