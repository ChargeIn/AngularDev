#ifndef FORMATTEDTEXT_H
#define FORMATTEDTEXT_H

#include <QString>

// formatting of the strings
enum S_FORMAT {
    NONE = 0,
    ITALIC = 1,
    BOLD = 2
};

typedef struct {
    QString* text;
    int fg; // foreground color index
    int bg; // background color index
    S_FORMAT format;
} FormattedString;

typedef struct {
    int size;
    FormattedString* strings;
    QString* rawText;
} FormattedLine;

typedef struct {
    int size;
    FormattedLine* lines;
} FormattedBlock;

typedef struct {
    int block;
    int line;
    int character;
} Position;

class FormattedText
{
public:
    int blockCount = 0;
    const int blockSize = 50;
    FormattedBlock* blocks;
    Position cursor;

    FormattedText();

    ~FormattedText();

    // adds a new line under the position of the cursor
    // and moves the cursor to the new line
    void addLine();

    // removes the line at the position of the cursor
    // and moves the cursor to the previous line
    void removeLine();

    void moveLeft();

    void moveRight();

    void moveUp();

    void moveDown();

    void clearAll();

    void removeLastChar();

    void removeLastWord();

    void writeText(QString input);

    void moveTo(int line, int character);

private:
    void addBlock(int pos);

    void removeBlock(int pos);

    void deleteBlock(FormattedBlock* block);

    void deleteLine(FormattedLine* line);

    void deleteString(FormattedString* string);
};

#endif // FORMATTEDTEXT_H
