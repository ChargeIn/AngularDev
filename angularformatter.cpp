#include "angularformatter.h"

AngularFormatter::AngularFormatter()
{

}

AngularFormatter::~AngularFormatter(){

}

const QRegularExpression* AngularFormatter::getSeparators(){
    return &separators;
}

FormattedLine* AngularFormatter::formatLine(FormattedLine *line){
    return line;
}
