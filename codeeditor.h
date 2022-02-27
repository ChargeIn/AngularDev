#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QObject>
#include <QWidget>
#include <QFile>
#include <QResizeEvent>

#include "formattedtext.h"

typedef struct {
    int height; // number of lines
    int width;  // number of characters per line
    double lineheight;
    float charWidth;
} EditorWindow;

class CodeEditor : public QWidget
{
    Q_OBJECT
public:
    explicit CodeEditor(QFile *file = nullptr, QWidget *parent = nullptr);

    void addLine();

public slots:
    void openFile(QFile *file);

protected:
    void paintEvent(QPaintEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

    void focusOutEvent(QFocusEvent *event) override;

    void mousePressEvent(QMouseEvent * event ) override;

    void mouseDoubleClickEvent(QMouseEvent * event ) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

private:
    EditorWindow win;
    FormattedText* text;

    /*
     * Terminal colors (same as xterm)
     */
    constexpr static const QColor colors[2] = {
        QColor(187,187,187),        // Default font color
        QColor(24,24,24)            // Default background color
    };
};

#endif // CODEEDITOR_H
