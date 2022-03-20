#ifndef ANGULARFORMATTER_H
#define ANGULARFORMATTER_H

#include <QStringList>
#include <QRegularExpression>
#include <QStringList>
#include <QColor>

#include "formatter.h"
#include "typescript/lexer.h"

class AngularFormatter : public Formatter {
public:
    const QStringList baseKeyWords{"const", "function", "let", "class", "export"};
    const QRegularExpression separators = QRegularExpression("(\\s+ |[ #:;,.+\\-_\\(\\{\\}\\)\\/\"<>])");

    AngularFormatter();

    ~AngularFormatter();

    const QRegularExpression *getSeparators() override;

    FormattedLine *formatLine(FormattedLine *line) override;

private:
    Lexer l;
};

#endif // ANGULARFORMATTER_H
