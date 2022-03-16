#include "chars.h"

bool Chars::isWhitespace(int code)
{
    return (code >= $TAB && code <= $SPACE) || (code == $NBSP);
}

bool Chars::isDigit(int code) {
    return $0 <= code && code <= $9;
}

bool Chars::isAsciiLetter(int code) {
    return (code >= $a && code <= $z) || (code >= $A && code <= $Z);
}

bool Chars::isAsciiHexDigit(int code) {
    return (code >= $a && code <= $f) || (code >= $A && code <= $F) || isDigit(code);
}

bool Chars::isNewLine(int code) {
    return code == $LF || code == $CR;
}

bool Chars::isOctalDigit(int code) {
    return $0 <= code && code <= $7;
}

bool Chars::isQuote(int code) {
    return code == $SQ || code == $DQ || code == $BT;
}

