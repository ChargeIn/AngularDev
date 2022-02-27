#ifndef ANGULARFORMATTER_H
#define ANGULARFORMATTER_H

#include <QStringList>
#include <QRegularExpression>
#include <QStringList>

#include "formatter.h"

class AngularFormatter: public Formatter
{
public:
    const QStringList baseUtils{"const", "function", "let", "class", "export"};
    const QRegularExpression separators = QRegularExpression("(\\s+ |[ #:;,.+\\-_\\(\\{\\}\\)\\/])");

    AngularFormatter();

    ~AngularFormatter() override;

    const QRegularExpression* getSeparators() override;

    FormattedLine* formatLine(FormattedLine* line) override;
};

#endif // ANGULARFORMATTER_H
