#ifndef FORMATTEDTEXT_H
#define FORMATTEDTEXT_H

#include <QString>

#include "formatter.h"

typedef struct {
    int size;
    FormattedLine* lines;
} FormattedBlock;

typedef struct {
    int block;
    int line;
    int character;
    int scope;
} Cursor;

enum TEXT_SCOPE {
    SCOPE_NONE = 1 << 0,
};

class FormattedText
{
public:
    Formatter* formatter;
    int blockCount = 0;
    const int blockSize = 5;
    FormattedBlock* blocks;
    Cursor cursor;
    int lastCharPos = 0; // last x position of the cursor before up/down move

    FormattedText(Formatter* formatter);

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

    void removeLastChar();

    void removeLastWord();

    void writeText(QString input);

    void moveTo(int line, int character);

private:
    void addBlock(int pos);

    void removeBlock(int pos);

    void deleteBlock(FormattedBlock* block);

    void deleteLine(FormattedLine* line);
};

#endif // FORMATTEDTEXT_H
