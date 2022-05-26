#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "libs/QLightTerminal/qlightterminal.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

public
    slots:
            void increase();

    void decrease();


protected:
    void setupMenubar();

private:
    Ui::MainWindow *ui;
    QWidget *menuWidget;
    QLightTerminal *term1;
    int i = 0;
};
#endif // MAINWINDOW_H
