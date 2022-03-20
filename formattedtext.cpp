#include "formattedtext.h"

FormattedText::FormattedText(Formatter *formatter) {
    this->formatter = formatter;
    blocks = new FormattedBlock[0];
    addBlock(0);
    cursor = {0, 0, 0, 0};
}

FormattedText::~FormattedText() {
    for (int i = 0; i < blockCount; i++) {
        deleteBlock(&blocks[i]);
    }
    delete[] blocks;
}


void FormattedText::deleteBlock(FormattedBlock *block) {
    for (int i = 0; i < block->size; i++) {
        deleteLine(&block->lines[i]);
    }
    delete[] block->lines;
}

void FormattedText::deleteLine(FormattedLine *line) {
    delete[] line->strings;
    delete line->rawText;
}

void FormattedText::addLine() {
    FormattedBlock *block = &blocks[cursor.block];

    if (block->size < blockSize) {
        FormattedLine *line = &block->lines[block->size];
        line->size = 1;
        line->rawText = new QString();

        FormattedString *str = new FormattedString[1];
        str[0].bg = 1;
        str[0].fg = 0;
        str[0].format = NONE;
        str[0].text = QString();

        line->strings = str;
        block->size++;
        cursor.line++;
        cursor.character = 0;
        return;
    }

    // add a new block
    cursor.block++;
    cursor.line = 0;
    cursor.character = 0;
    addBlock(cursor.block);
}

void FormattedText::removeLine() {
    FormattedBlock *block = &blocks[cursor.block];

    if (block->size > 1) {
        FormattedLine *line = &block->lines[cursor.line];
        line->rawText->clear();
        line->strings = new FormattedString[0];
        line->size = 0;

        block->size--;
        cursor.line--;
        cursor.character = blocks[cursor.block].lines[cursor.line].rawText->size();
    } else {
        if (cursor.block > 0) {
            removeBlock(cursor.block);
            cursor.block--;
            cursor.line = blocks[cursor.block].size - 1;
            cursor.character = blocks[cursor.block].lines[cursor.line].rawText->size();
        }
    }
}

void FormattedText::moveLeft() {
    if (cursor.character == 0) {
        if (cursor.line > 0) {
            cursor.line--;
            cursor.character = blocks[cursor.block].lines[cursor.line].rawText->size();
        } else {
            if (cursor.block > 0) {
                cursor.block--;
                cursor.line = blocks[cursor.block].size - 1;
                cursor.character = blocks[cursor.block].lines[cursor.line].rawText->size();
            }
        }
    } else {
        cursor.character--;
    }
    lastCharPos = cursor.character;
}

void FormattedText::moveRight() {
    FormattedBlock *block = &blocks[cursor.block];
    if (cursor.character < block->lines[cursor.line].rawText->size()) {
        cursor.character++;
    } else {
        if (cursor.line < block->size - 1) {
            cursor.line++;
            cursor.character = 0;
        } else {
            if (cursor.block < blockCount - 1) {
                cursor.block++;
                cursor.line = 0;
                cursor.character = 0;
            }
        }
    }
    lastCharPos = cursor.character;
}

void FormattedText::moveUp() {
    if (cursor.line > 0) {
        cursor.line--;
    } else {
        if (cursor.block > 0) {
            cursor.block--;
            cursor.line = blocks[cursor.block].size - 1;
        } else {
            return;
        }
    }

    int maxIndex = blocks[cursor.block].lines[cursor.line].rawText->size() - 1;

    if (lastCharPos > maxIndex) {
        cursor.character = maxIndex;
    } else {
        cursor.character = lastCharPos;
    }
}

void FormattedText::moveDown() {
    if (cursor.line < blocks[cursor.block].size - 1) {
        cursor.line++;
    } else {
        if (cursor.block < blockCount - 1) {
            cursor.block++;
            cursor.line = 0;
        } else {
            return;
        }
    }

    int maxIndex = blocks[cursor.block].lines[cursor.line].rawText->size() - 1;

    if (lastCharPos > maxIndex) {
        cursor.character = maxIndex;
    } else {
        cursor.character = lastCharPos;
    }
}

void FormattedText::removeLastChar() {
    FormattedLine *line = &blocks[cursor.block].lines[cursor.line];

    if (line->rawText->size() > 0) {
        line->rawText->chop(1);
        cursor.character--;
    } else {
        removeLine();
    }
}

void FormattedText::removeLastWord() {
    FormattedLine *line = &blocks[cursor.block].lines[cursor.line];

    if (line->rawText->size() > 0) {
        int lastMatch = line->rawText->lastIndexOf(*formatter->getSeparators());
        int toRemove = line->rawText->size() - lastMatch - 1;
        if (toRemove < 1) {
            toRemove = 1;
        }
        line->rawText->chop(toRemove);
        cursor.character -= toRemove;
    } else {
        removeLine();
    }
}

void FormattedText::writeText(QString input) {
    QString *rawText = blocks[cursor.block].lines[cursor.line].rawText;
    rawText->append(input);
    cursor.character += input.size();
    lastCharPos = cursor.character;
    formatter->formatLine(&blocks[cursor.block].lines[cursor.line]);
}

void FormattedText::addBlock(int pos) {
    FormattedBlock *newBlocks = new FormattedBlock[blockCount + 1];


    int size = sizeof(FormattedBlock);
    ::memcpy(newBlocks, blocks, pos * size);
    ::memcpy(&newBlocks[pos + 1], &blocks[pos], (blockCount - pos) * size);

    delete[] blocks;
    blocks = newBlocks;

    blocks[pos] = {1, new FormattedLine[blockSize]};
    blocks[pos].lines[0].rawText = new QString();
    blocks[pos].lines[0].size = 1;

    FormattedString *str = new FormattedString[1];
    str[0].bg = 1;
    str[0].fg = 0;
    str[0].format = NONE;
    str[0].text = QString();

    blocks[pos].lines[0].strings = str;
    blockCount++;
}

void FormattedText::removeBlock(int pos) {
    FormattedBlock *newBlocks = new FormattedBlock[blockCount - 1];

    int size = sizeof(FormattedBlock);
    ::memcpy(newBlocks, blocks, pos * size);
    if (blockCount - pos > 0) {
        ::memcpy(&newBlocks[pos], &blocks[pos + 1], (blockCount - pos - 1) * size);
    }

    deleteBlock(&blocks[pos]);

    delete[] blocks;
    blocks = newBlocks;
    blockCount--;
}
