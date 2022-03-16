#ifndef CHARS_H
#define CHARS_H


class Chars
{
public:
    static const int $EOF = 0;
    static const int $BSPACE = 8;
    static const int $TAB = 9;
    static const int $LF = 10;
    static const int $VTAB = 11;
    static const int $FF = 12;
    static const int $CR = 13;
    static const int $SPACE = 32;
    static const int $BANG = 33;
    static const int $DQ = 34;
    static const int $HASH = 35;
    static const int $$ = 36;
    static const int $PERCENT = 37;
    static const int $AMPERSAND = 38;
    static const int $SQ = 39;
    static const int $LPAREN = 40;
    static const int $RPAREN = 41;
    static const int $STAR = 42;
    static const int $PLUS = 43;
    static const int $COMMA = 44;
    static const int $MINUS = 45;
    static const int $PERIOD = 46;
    static const int $SLASH = 47;
    static const int $COLON = 58;
    static const int $SEMICOLON = 59;
    static const int $LT = 60;
    static const int $EQ = 61;
    static const int $GT = 62;
    static const int $QUESTION = 63;
    static const int $0 = 48;
    static const int $7 = 55;
    static const int $9 = 57;
    static const int $A = 65;
    static const int $E = 69;
    static const int $F = 70;
    static const int $X = 88;
    static const int $Z = 90;
    static const int $LBRACKET = 91;
    static const int $BACKSLASH = 92;
    static const int $RBRACKET = 93;
    static const int $CARET = 94;
    static const int $_ = 95;
    static const int $a = 97;
    static const int $b = 98;
    static const int $e = 101;
    static const int $f = 102;
    static const int $n = 110;
    static const int $r = 114;
    static const int $t = 116;
    static const int $u = 117;
    static const int $v = 118;
    static const int $x = 120;
    static const int $z = 122;
    static const int $LBRACE = 123;
    static const int $BAR = 124;
    static const int $RBRACE = 125;
    static const int $NBSP = 160;
    static const int $PIPE = 124;
    static const int $TILDA = 126;
    static const int $AT = 64;
    static const int $BT = 96;

    static bool isWhitespace(int code);

    static bool isDigit(int code);

    static bool isAsciiLetter(int code);

    static bool isAsciiHexDigit(int code);

    static bool isNewLine(int code);

    static bool isOctalDigit(int code);

    static bool isQuote(int code);
};

#endif // CHARS_H
