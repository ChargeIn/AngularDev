#include "titlebar.h"

#include <QMouseEvent>

TitleBar::TitleBar(QWidget *parent)
        : QWidget{parent} {
    this->parent = parent;
    menuWidgetLayout = new QGridLayout(this);
    setLayout(menuWidgetLayout);

    menuBar = new QMenuBar(this);
    min = new QToolButton();
    max = new QToolButton();
    close = new QToolButton();
    menuWidgetLayout->addWidget(menuBar, 0, 0, 1, 1);
    menuWidgetLayout->addWidget(min, 0, 1, 1, 1);
    menuWidgetLayout->addWidget(max, 0, 2, 1, 1);
    menuWidgetLayout->addWidget(close, 0, 3, 1, 1);
}

TitleBar::~TitleBar() {
    delete menuWidgetLayout;
    delete menuBar;
}

void TitleBar::mousePressEvent(QMouseEvent *evt) {

    qDebug() << "Start drag: " << evt->globalPosition();

    oldPos = evt->globalPosition();

    evt->accept();
}

void TitleBar::mouseMoveEvent(QMouseEvent *evt) {
    const QPointF delta = evt->globalPosition() - oldPos;
    qDebug() << "Move drag: " << delta;
    window()->move(parent->x() + delta.x(), parent->y() + delta.y());
    oldPos = evt->globalPosition();

    evt->accept();
}
