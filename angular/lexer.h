#ifndef LEXER_H
#define LEXER_H

#include <QString>
#include <QChar>
#include <QStringList>

#include <vector>
#include <optional>

enum TokenType {
  Character,
  Identifier,
  PrivateIdentifier,
  Keyword,
  String,
  Operator,
  Number,
  Error
};

class Token {
public:
    size_t index, end;
    TokenType type;
    double numValue;
    QString strValue;

    Token(size_t index, size_t end, TokenType type, double numValue, QString strValue);

    bool isCharacter(int code);

    bool isNumber();

    bool isString();

    bool isOperator(QString op);

    bool isIdentifier();

    bool isPrivateIdentifier();

    bool isKeyword();

    bool hasStrValueLet();

    bool hasStrValueAs();

    bool hasStrValueNull();

    bool hasStrValueUndefined();

    bool hasStrValueTrue();

    bool hasStrValueFalse();

    bool hasStrValueThis();

    bool isError();

    double toNumber();

    QString toString();

    static Token newCharacterToken(size_t index, size_t end, int code);

    static Token newIdentifierToken(size_t index, size_t end, QString text);

    static Token newPrivateIdentifierToken(size_t index, size_t end, QString text);

    static Token newKeywordToken(size_t index, size_t end, QString text);

    static Token newOperatorToken(size_t index, size_t end, QString text);

    static Token newStringToken(size_t index, size_t end, QString text);

    static Token newNumberToken(size_t index, size_t end, double n);

    static Token newErrorToken(size_t index, size_t end, QString message);

    static const Token EOF_TOKEN;
};

class _Scanner {
private:
    int length;
    int peek = 0;
    int index = -1;
    QString input;
public:
    static const QStringList KEYWORDS;

    _Scanner(QString input);

    void advance();

    std::optional<Token> scanToken();

    static bool isIdentifierStart(int code);

    static bool isIdentifierPart(int code);

    static bool isExponentStart(int code);

    static bool isExponentSign(int code);

    static int unescape(int code);

    Token scanCharacter(int start, int code);

    Token scanOperator(int start, QString str);

    Token scanComplexOperator(int start, QChar one, int twoCode, QChar two);

    Token scanComplexOperator(int start, QChar one, int twoCode, QChar two, int threeCode, QChar three);

    Token scanIdentifier();

    Token scanPrivateIdentifier();

    Token scanNumber(int start);

    Token scanString();

    Token scanQuestion(int start);

    Token error(QString message, int offset);
};

class Lexer
{
public:
    static std::vector<Token> tokenize(QString text);
};

#endif // LEXER_H
