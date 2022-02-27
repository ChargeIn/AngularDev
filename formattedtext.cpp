#include "formattedtext.h"

#include "string.h"

#include <QRegularExpression>

FormattedText::FormattedText()
{
    blocks = new FormattedBlock[0];
    cursor = {0,0,0};
    addBlock(0);
    addLine();
    cursor = {0,0,0};
}

FormattedText::~FormattedText()
{
    for(int i = 0; i < blockCount; i++){
        deleteBlock(&blocks[i]);
    }
    delete[] blocks;
}


void FormattedText::deleteBlock(FormattedBlock *block)
{
    for(int i = 0; i < block->size; i++){
        deleteLine(&block->lines[i]);
    }
    delete[] block->lines;
}

void FormattedText::deleteLine(FormattedLine *line)
{
    for(int j = 0; j < line->size; j++){
        deleteString(&line->strings[j]);
    }
    delete[] line->strings;
    delete line->rawText;
}

void FormattedText::deleteString(FormattedString *string)
{
    delete string->text;
}

void FormattedText::addLine()
{
    FormattedBlock* block = &blocks[cursor.block];

    if(block->size < blockSize){
        FormattedLine* line = &block->lines[block->size];
        line->size = 1;
        line->rawText = new QString();

        FormattedString* str = new FormattedString[1];
        str[0].bg = 1;
        str[0].fg = 0;
        str[0].format = NONE;
        str[0].text = new QString();

        line->strings = str;
        block->size++;
        cursor.line++;
        return;
    }

    // add a new block
    cursor.block++;
    cursor.line = -1;
    addBlock(cursor.block);
    addLine();
}

void FormattedText::removeLine()
{
    FormattedBlock* block = &blocks[cursor.block];

    if(block->size > 1){
        FormattedLine* line = &block->lines[cursor.line];
        for(int i = 0; i < line->size; i++){
            deleteString(&line->strings[i]);
        }
        line->rawText->clear();
        line->strings = new FormattedString[0];
        line->size = 0;

        block->size--;
        cursor.line--;
    } else {
        if(cursor.block > 0){
            removeBlock(cursor.block);
            cursor.block--;
            cursor.line = blocks[cursor.block].size-1;
        }
    }
}

void FormattedText::moveLeft()
{

}

void FormattedText::moveRight()
{

}

void FormattedText::moveUp()
{

}

void FormattedText::moveDown()
{

}

void FormattedText::clearAll()
{

}

void FormattedText::removeLastChar()
{
    FormattedLine* line = &blocks[cursor.block].lines[cursor.line];

    if(line->rawText->size() > 0){
        line->rawText->chop(1);
    } else {
        removeLine();
    }
}

void FormattedText::removeLastWord()
{
    FormattedLine* line = &blocks[cursor.block].lines[cursor.line];

    if(line->rawText->size() > 0){
        QRegularExpression separators = QRegularExpression("(\\s+ |[ #:;,.+\\-_\\(\\{\\}\\)\\/])");
        int lastMatch = line->rawText->lastIndexOf(separators);
        int toRemove = line->rawText->size() - lastMatch - 1;
        if(toRemove < 1){
            toRemove = 1;
        }
        line->rawText->chop(toRemove);
    } else {
        removeLine();
    }
}

void FormattedText::writeText(QString input)
{
    QString* rawText = blocks[cursor.block].lines[cursor.line].rawText;
    rawText->append(input);
}

void FormattedText::addBlock(int pos)
{
    FormattedBlock* newBlocks = new FormattedBlock[blockCount+1];


    int size = sizeof(FormattedBlock);
    ::memcpy(newBlocks, blocks, pos * size);
    ::memcpy(&newBlocks[pos+1], &blocks[pos], (blockCount - pos) * size);

    delete[] blocks;
    blocks = newBlocks;

    blocks[pos] = { 0, new FormattedLine[blockSize]};
    blockCount++;
}

void FormattedText::removeBlock(int pos)
{
   FormattedBlock* newBlocks = new FormattedBlock[blockCount-1];

    int size = sizeof(FormattedBlock);
    ::memcpy(newBlocks, blocks, pos * size);
    if(blockCount - pos > 0){
        ::memcpy(&newBlocks[pos], &blocks[pos+1], (blockCount - pos -1) * size);
    }

    deleteBlock(&blocks[pos]);

    delete[] blocks;
    blocks = newBlocks;
    blockCount--;
}
