#ifndef FORMATTER_H
#define FORMATTER_H

#include <QString>

// formatting of the strings
enum STR_FORMAT {
    NONE = 0,
    ITALIC = 1,
    BOLD = 2
};

typedef struct {
    QString* text;
    int fg; // foreground color index
    int bg; // background color index
    STR_FORMAT format;
} FormattedString;

typedef struct {
    int size;
    FormattedString* strings;
    QString* rawText;
} FormattedLine;

class Formatter
{
public:
    Formatter();

    virtual ~Formatter();

    virtual const QRegularExpression* getSeparators();

    // reformates the line based on the raw text
    virtual FormattedLine* formatLine(FormattedLine* line);
};

#endif // FORMATTER_H
