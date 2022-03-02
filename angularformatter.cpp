#include "angularformatter.h"

#include <QRegularExpressionMatchIterator>
#include <QRegularExpressionMatch>

AngularFormatter::AngularFormatter()
{

}

AngularFormatter::~AngularFormatter(){

}

const QRegularExpression* AngularFormatter::getSeparators(){
    return &separators;
}

FormattedLine* AngularFormatter::formatLine(FormattedLine *line){
    FormattedString* tempLine = new FormattedString[line->rawText->size()];

    int matchCount = 0;
    int start = 0;
    while(start < line->rawText->size()){
        QString match = line->rawText->section(separators, start);
        start+= match.size();
        tempLine[matchCount].text = new QString(match.data());

        bool matched = false;

        for(int i = 0; i < baseKeyWords.size(); i++){
            if(match == baseKeyWords[i]){
                matched = true;
                tempLine[matchCount].bg = 0;
                tempLine[matchCount].fg = 2;
                tempLine[matchCount].format = NONE;

                break;
            }
        }

        if(!matched){
            tempLine[matchCount].bg = 0;
            tempLine[matchCount].fg = 1;
            tempLine[matchCount].format = NONE;
        }

        matchCount ++;
    }

    FormattedString* sizedLine = new FormattedString[matchCount];
    ::memcpy(sizedLine, tempLine, matchCount * sizeof(FormattedString));

    // delete old line
    for(int i = 0; i < line->size; i++){
        delete line->strings[i].text;
    }
    delete[] line->strings;
    delete[] tempLine;

    line->strings = sizedLine;
    line->size = matchCount;

    return line;
}
