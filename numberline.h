#ifndef NUMBERLINE_H
#define NUMBERLINE_H

#include <QWidget>

class NumberLine : public QWidget {
    Q_OBJECT
public:
    explicit NumberLine(QWidget *parent = nullptr);

    signals:

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
};

#endif // NUMBERLINE_H
