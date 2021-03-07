#include "Parser.h"

Parser::Parser(): source(), current(), end() {}

shared_ptr<LetStmt> Parser::getLetStmt() {
    TokenPtr name;

    // get the identifier
    if (match(TokenType::IDENTIFIER)) {
        name = advance();
    } else {
        error("Expect variable name");
    }

    // get '='
    consume(TokenType::EQUAL, "Expect assignment symbol '='");

    // get expression
    ExprPtr initializer = expression();

    checkEnd();

    return make_shared<LetStmt>(name, initializer);
}

shared_ptr<PrintStmt> Parser::getPrintStmt() {
    ExprPtr expr = expression();

    checkEnd();

    return make_shared<PrintStmt>(expr);
}

shared_ptr<InputStmt> Parser::getInputStmt() {
    TokenPtr name;

    if (match(TokenType::IDENTIFIER)) {
        name = advance();
    } else {
        error("Expect variable name");
    }

    checkEnd();

    return make_shared<InputStmt>(name);
}

shared_ptr<GotoStmt> Parser::getGotoStmt() {
    int lineNum;
    if (match(TokenType::NUMBER)) {
        lineNum = static_cast<int>(advance()->value);
    } else {
        error("Expect line number");
    }

    checkEnd();

    return make_shared<GotoStmt>(lineNum);
}

shared_ptr<IfStmt> Parser::getIfStmt() {
    TokenPtr op;
    ExprPtr expr1;
    ExprPtr expr2;
    int lineNum;

    expr1 = expression();

    if (match({TokenType::LESS, TokenType::GREATER, TokenType::EQUAL})) {
        op = advance();
    } else {
        error("Expect comparator in if condition");
    }

    expr2 = expression();

    consume(TokenType::THEN, "IF requires a THEN");

    if (match(TokenType::NUMBER)) {
        lineNum = static_cast<int>(advance()->value);
    }

    checkEnd();

    return make_shared<IfStmt>(op, expr1, expr2, lineNum);
}

shared_ptr<EndStmt> Parser::getEndStmt() {
    checkEnd();
    return make_shared<EndStmt>();
}

ExprPtr Parser::expression() {

}

ExprPtr Parser::addition() {

}

ExprPtr Parser::mult() {

}

ExprPtr Parser::pow() {

}

ExprPtr Parser::unary() {

}

shared_ptr<Expr> Parser::primary() {

}

bool Parser::match(TokenType type) {
    if (isAtEnd()) {
        return false;
    }
    return type == (*current)->type;
}

bool Parser::match(vector<TokenType> types) {
    if (isAtEnd()) {
        return false;
    }
    TokenType currentType = (*current)->type;
    for (auto type: types) {
        if (type == currentType) {
            return true;
        }
    }

    return false;
}

StmtPtr Parser::getStmt(shared_ptr<QList<TokenPtr>> tokens) {
    source = tokens;
    current = source->begin();
    end = source->end();

    StmtPtr stmt;
    TokenPtr stmtIdentifier = advance();

    switch (stmtIdentifier->type) {
    case TokenType::LET:
        stmt = getLetStmt();
        break;
    case TokenType::PRINT:
        stmt = getPrintStmt();
        break;
    case TokenType::INPUT:
        stmt = getInputStmt();
        break;
    case TokenType::GOTO:
        stmt = getGotoStmt();
        break;
    case TokenType::IF:
        stmt = getIfStmt();
        break;
    case TokenType::END:
        stmt = getEndStmt();
        break;
    default:
        throw QString("Invalid start of statement: " + stmtIdentifier->lexeme);
    }

    return stmt;
}

bool Parser::isAtEnd() {
    return current == end;
}

TokenPtr Parser::advance() {
    ++current;
    return *(current - 1);
}

void Parser::error(QString errMsg) {
    throw QString(errMsg);
}

void Parser::consume(TokenType type, QString errMsg) {
    if (match(type)) {
        ++current;
    } else {
        throw errMsg;
    }
}

void Parser::checkEnd() {
    if (!isAtEnd()) {
        QString errMsg = "Excessive symbols at the end of the line: ";
        while (!isAtEnd()) {
            errMsg += advance()->lexeme;
        }
        throw errMsg;
    }
}
