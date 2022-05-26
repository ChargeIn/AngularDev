#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QMenuBar>
#include <QToolButton>
#include <QPointF>

class TitleBar : public QWidget {
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = nullptr);

    ~TitleBar();

protected:
    void mousePressEvent(QMouseEvent *evt) override;

    void mouseMoveEvent(QMouseEvent *evt) override;

private:
    QWidget *parent;
    QGridLayout *menuWidgetLayout;
    QMenuBar *menuBar;
    QToolButton *close;
    QToolButton *max;
    QToolButton *min;
    QPointF oldPos;
};

#endif // TITLEBAR_H
