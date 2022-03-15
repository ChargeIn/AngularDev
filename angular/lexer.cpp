#include "lexer.h"

#include "chars.h"

#include <QRegularExpression>

// -------------------------- Lexer ------------------------

std::vector<Token> Lexer::tokenize(QString text)
{
    _Scanner scanner = _Scanner(text);
    std::vector<Token> tokens;

    std::optional<Token> token = scanner.scanToken();
    while(token.has_value()){
        tokens.push_back(token.value());
        token = scanner.scanToken();
    }
    return tokens;
}

// -------------------------- Token ------------------------
Token::Token(size_t index, size_t end, TokenType type, double numValue, QString strValue)
{
    this->index = index;
    this->end = end;
    this->type = type;
    this->numValue = numValue;
    this->strValue = strValue;
}

bool Token::isCharacter(int code)
{
    return type == TokenType::Character && numValue == code;
}

bool Token::isNumber()
{
    return type == TokenType::Number;
}

bool Token::isString()
{
    return type == TokenType::String;
}

bool Token::isOperator(QString op)
{
    return type == TokenType::Operator && strValue == op;
}

bool Token::isIdentifier()
{
    return type == TokenType::Identifier;
}

bool Token::isPrivateIdentifier()
{
    return type == TokenType::PrivateIdentifier;
}

bool Token::isKeyword()
{
    return type == TokenType::Keyword;
}

bool Token::hasStrValueLet()
{
    return strValue == "let";
}

bool Token::hasStrValueAs()
{
    return strValue == "as";
}

bool Token::hasStrValueNull()
{
    return strValue == "null";
}

bool Token::hasStrValueUndefined()
{
    return strValue == "undefined";
}

bool Token::hasStrValueTrue()
{
    return strValue == "true";
}

bool Token::hasStrValueFalse()
{
    return strValue == "false";
}

bool Token::hasStrValueThis()
{
    return strValue == "this";
}

bool Token::isError()
{
    return type == TokenType::Error;
}

double Token::toNumber()
{
    return type == TokenType::Number ? numValue: -1;
}

QString Token::toString()
{
    switch(type) {
        case TokenType::Character:
        case TokenType::Identifier:
        case TokenType::Keyword:
        case TokenType::Operator:
        case TokenType::PrivateIdentifier:
        case TokenType::String:
        case TokenType::Error:
            return strValue;
        case TokenType::Number:
            return QString::number(numValue);
    }
}

Token Token::newCharacterToken(size_t index, size_t end, int code)
{
    return Token(index, end, TokenType::Character, code, QChar(code));
}

Token Token::newIdentifierToken(size_t index, size_t end, QString text)
{
    return Token(index, end, TokenType::Identifier, 0 , text);
}

Token Token::newPrivateIdentifierToken(size_t index, size_t end, QString text)
{
    return Token(index, end, TokenType::PrivateIdentifier, 0, text);
}

Token Token::newKeywordToken(size_t index, size_t end, QString text)
{
    return Token(index, end, TokenType::Keyword, 0 , text);
}

Token Token::newOperatorToken(size_t index, size_t end, QString text)
{
    return Token(index, end, TokenType::Operator, 0, text);
}

Token Token::newStringToken(size_t index, size_t end, QString text)
{
    return Token(index, end, TokenType::String, 0, text);
}

Token Token::newNumberToken(size_t index, size_t end, double n)
{
    return Token(index, end, TokenType::Number, n, "");
}

Token Token::newErrorToken(size_t index, size_t end, QString message)
{
    return Token(index, end, TokenType::Error, 0, message);
}

const Token Token::EOF_TOKEN = Token(-1, -1, TokenType::Character, 0, "");


// -------------------------- Scanner ------------------------
const QStringList _Scanner::KEYWORDS = {
        "const", "var", "let",
        "as", "of",
        "null","true", "false", "undefined", "boolean", "number", "string", "null"
        "if", "else", "for", "while", "switch", "case", "break", "continue",
        "export", "import", "from",
        "this", "class", "function", "return", "new", "enum"
        "public", "private", "static"
};

_Scanner::_Scanner(QString input)
{
    length = input.length();
    this->input = input;
}

void _Scanner::advance()
{
    peek = ++index >= length ? Chars::$EOF : input.at(index).toLatin1();
}

std::optional<Token> _Scanner::scanToken()
{    
    // Skip whitespace
    while(peek <= Chars::$SPACE){
        if(++index >= length){
            peek = Chars::$EOF;
            break;
        } else {
            peek = input.at(index).toLatin1();
        }
    }

    if(index >= length){
        return std::optional<Token>{};
    }

    // Handle identifiers and numbers.
    if(isIdentifierStart(peek)) return scanIdentifier();
    if(Chars::isDigit(peek)) return scanNumber(index);

    int start = index;

    switch(peek) {
        case Chars::$PERIOD:
           advance();
           return Chars::isDigit(peek) ?
                scanNumber(start) :
                Token::newCharacterToken(start, index, Chars::$PERIOD);
         case Chars::$LPAREN:
         case Chars::$RPAREN:
         case Chars::$LBRACE:
         case Chars::$RBRACE:
         case Chars::$LBRACKET:
         case Chars::$RBRACKET:
         case Chars::$COMMA:
         case Chars::$COLON:
         case Chars::$SEMICOLON:
           return scanCharacter(start, peek);
         case Chars::$SQ:
         case Chars::$DQ:
           return scanString();
         case Chars::$HASH:
           return scanPrivateIdentifier();
         case Chars::$PLUS:
         case Chars::$MINUS:
         case Chars::$STAR:
         case Chars::$SLASH:
         case Chars::$PERCENT:
         case Chars::$CARET:
           return scanOperator(start, QChar(peek));
         case Chars::$QUESTION:
           return scanQuestion(start);
         case Chars::$LT:
         case Chars::$GT:
           return scanComplexOperator(start, QChar(peek), Chars::$EQ, '=');
         case Chars::$BANG:
         case Chars::$EQ:
           return scanComplexOperator(
               start, QChar(peek), Chars::$EQ, '=', Chars::$EQ, '=');
         case Chars::$AMPERSAND:
           return scanComplexOperator(start, '&', Chars::$AMPERSAND, '&');
         case Chars::$BAR:
           return scanComplexOperator(start, '|', Chars::$BAR, '|');
         case Chars::$NBSP:
           while (Chars::isWhitespace(peek)) advance();
           return scanToken();
    }

    advance();
    return error("Unexpected character [" + QString(QChar(peek)) + "]", 0);
}

bool _Scanner::isIdentifierStart(int code)
{
    return (Chars::$a <= code && code <= Chars::$z) || (Chars::$A <= code && code <= Chars::$Z) ||
            (code == Chars::$_) || (code == Chars::$$);
}

bool _Scanner::isIdentifierPart(int code)
{
    return Chars::isAsciiLetter(code) || Chars::isDigit(code) || (code == Chars::$_) ||
            (code == Chars::$$);
}

bool _Scanner::isExponentStart(int code)
{
    return code == Chars::$e || code == Chars::$E;
}

bool _Scanner::isExponentSign(int code)
{
    return code == Chars::$MINUS ||   code == Chars::$PLUS;
}

int _Scanner::unescape(int code)
{
  switch (code) {
    case Chars::$n:
      return Chars::$LF;
    case Chars::$f:
      return Chars::$FF;
    case Chars::$r:
      return Chars::$CR;
    case Chars::$t:
      return Chars::$TAB;
    case Chars::$v:
      return Chars::$VTAB;
    default:
      return code;
  }
}

Token _Scanner::scanCharacter(int start, int code)
{
    advance();
    return Token::newCharacterToken(start, index, code);
}

Token _Scanner::scanOperator(int start, QString str)
{
    advance();
    return Token::newOperatorToken(start, index, str);
}

/**
 * Tokenize a 2 char long operator
 *
 * @param start start index in the expression
 * @param one first symbol (always part of the operator)
 * @param twoCode code point for the second symbol
 * @param two second symbol (part of the operator when the second code point matches)
 */
Token _Scanner::scanComplexOperator(int start, QChar one, int twoCode, QChar two)
{
    advance();
    QString str = one;
    if(peek == twoCode) {
        advance();
        str += two;
    }
    return Token::newOperatorToken(start, index, str);
}

/**
 * Tokenize a 3 char long operator
 *
 * @param start start index in the expression
 * @param one first symbol (always part of the operator)
 * @param twoCode code point for the second symbol
 * @param two second symbol (part of the operator when the second code point matches)
 * @param threeCode code point for the third symbol
 * @param three third symbol (part of the operator when provided and matches source expression)
 */
Token _Scanner::scanComplexOperator(int start, QChar one, int twoCode, QChar two, int threeCode, QChar three)
{
    advance();
    QString str = one;
    if(peek == twoCode) {
        advance();
        str += two;
    }
    if(peek == threeCode){
        advance();
        str += three;
    }
    return Token::newOperatorToken(start, index, str);
}

Token _Scanner::error(QString message, int offset)
{
    int position = index + offset;
    return Token::newErrorToken(
        position, index,
        "Lexer Error: " +  message + " at column "  + QString::number(position) + " in expression [" + input + "]");
}

Token _Scanner::scanIdentifier()
{
    int start = index;
    advance();

    while(isIdentifierPart(peek)) {
        advance();
    }

    QString str = input.sliced(start, index - start);
    return KEYWORDS.indexOf(str) > -1 ?
                Token::newKeywordToken(start, index, str) :
                Token::newIdentifierToken(start, index, str);
}

Token _Scanner::scanPrivateIdentifier()
{
    int start = index;
    advance();

    if(!isIdentifierStart(peek)){
        return error("Invalid character [#]", -1);
    }

    while(isIdentifierPart(peek)) advance();

    QString identifierName = input.sliced(start, index - start);
    return Token::newPrivateIdentifierToken(start, index, identifierName);
}

Token _Scanner::scanNumber(int start)
{
    bool hasSeparators = false;
    advance();

    while(true){
        if(Chars::isDigit(peek)){
            // Do nothing.
        } else if(peek == Chars::$_){
            // Separators are only valid when they're surrounded by digits. E.g. `1_0_1` is
            // valid while `_101` and `101_` are not. The separator can't be next to the decimal
            // point or another separator either. Note that it's unlikely that we'll hit a case where
            // the underscore is at the start, because that's a valid identifier and it will be picked
            // up earlier in the parsing. We validate for it anyway just in case.
            if((index > 0 && !Chars::isDigit(input.at(index-1).toLatin1())) ||
               (index < length -1 && !Chars::isDigit(input.at(index + 1).toLatin1()))) {
                return error("Invalid numeric separator", 0);
            }
            hasSeparators = true;
        } else if(peek == Chars::$PERIOD) {
            // Do nothing.
        } else if(isExponentSign(peek)) {
            advance();
            if(isExponentSign(peek)) advance();
            if(!Chars::isDigit(peek)) return error("Invalid exponent", -1);
        } else {
            break;
        }
        advance();
    }

    QString str = input.sliced(start, index - start);
    if(hasSeparators) {
        str = str.replace(QRegularExpression("_"), "");
    }

    bool ok = true;
    double value = str.toDouble(&ok);

    if(!ok){
        return error("Could not convert \"" + str + "\" to double.", -1);
    }

    return Token::newNumberToken(start, index, value);
}

Token _Scanner::scanString()
{
    int start = index;
    int quote = peek;
    advance();

    QString buffer = "";
    int marker = index;
    QRegularExpression hexMatch = QRegularExpression("^[0-9a-f]+$");

    while(peek != quote) {
        if(peek == Chars::$BACKSLASH) {
            advance();
            int unescapedCode;

            if(peek == Chars::$u) {
                QString hex = input.sliced(index +1, 4);

                if(hexMatch.match(hex).hasMatch()) {
                    bool ok = true;
                    unescapedCode = hex.toInt(&ok , 16);

                    if(!ok){
                        return error("Could not convert \"" + hex + "\" to int.", -1);
                    }
                } else {
                    return error("Invalid unicode escape [\\u" + hex + "]", 0);
                }

                for(int i = 0; i < 5; i++){
                    advance();
                }
            } else {
                unescapedCode = unescape(peek);
                advance();
            }
            buffer += QChar(unescapedCode);
            marker = index;
        } else if(peek == Chars::$EOF) {
            error("Unterminated quote", 0);
        } else {
            advance();
        }
    }

    QString last = input.sliced(marker, index - marker);
    advance();

    return Token::newStringToken(start, index, buffer + last);
}

Token _Scanner::scanQuestion(int start)
{
    advance();
    QString str = "?";

    if(peek == Chars::$QUESTION || peek == Chars::$PERIOD) {
        str += peek == Chars::$PERIOD ? "." : "?";
        advance();
    }

    return Token::newOperatorToken(start, index, str);
}
