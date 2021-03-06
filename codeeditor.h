#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QObject>
#include <QWidget>
#include <QFile>
#include <QResizeEvent>
#include <QChar>

#include "formattedtext.h"
#include "formatter.h"

typedef struct {
    int height; // number of lines
    int width;  // number of characters per line
    double lineheight;
    float charWidth;
    int numberOffset; // line counter offset
    int textOffset; // text offset from the left
} EditorWindow;

class CodeEditor : public QWidget {
    Q_OBJECT
public:
    explicit CodeEditor(QFile *file = nullptr, QWidget *parent = nullptr);

    ~CodeEditor();

public
    slots:
            void openFile(QFile * file);

protected:
    void paintEvent(QPaintEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

    void focusOutEvent(QFocusEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

private:
    EditorWindow win;
    FormattedText *text;
    Formatter *formatter;
    const QChar cursorChar = QChar(9613);

    constexpr static const QColor
    numberLine = QColor(68, 68, 88);

    /*
     * Terminal colors (same as xterm)
     */
    constexpr static const QColor
    colors[5] = {
        QColor(27, 27, 34),           // Default background color QColor(24,24,24)
                QColor(233, 233, 233),        // Default font color
                QColor(204, 120, 50),       // Base Key Words
                QColor(104, 151, 187),      // Numbers
                QColor(106, 135, 89)        // String
    };
};

#endif // CODEEDITOR_H
