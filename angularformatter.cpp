#include "angularformatter.h"

#include <QRegularExpressionMatchIterator>
#include <QRegularExpressionMatch>

#include <vector>

AngularFormatter::AngularFormatter()
{

}

AngularFormatter::~AngularFormatter(){

}

const QRegularExpression* AngularFormatter::getSeparators(){
    return &separators;
}

FormattedLine* AngularFormatter::formatLine(FormattedLine *line){
    std::vector<Token> tokens = l.tokenize(*line->rawText);
    FormattedString* tempLine = new FormattedString[tokens.size()];

    int start = 0;
    int i = 0;
    while(i < tokens.size()){
        FormattedString* s = &tempLine[i];

        switch(tokens[i].type) {
            case TokenType::Keyword:
                s->bg = 0;
                s->fg = 2;
                break;
            case TokenType::Number:
                s->bg = 0;
                s->fg = 3;
                break;
            default:
                s->bg = 0;
                s->fg = 1;
        }

        s->format = STR_FORMAT::NONE;
        s->text = line->rawText->sliced(start, tokens[i].end - start);
        start = tokens[i].end;
        i++;
    }

    // delete old line
    delete[] line->strings;

    line->strings = tempLine;
    line->size = tokens.size();

    return line;
}
