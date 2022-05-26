#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "codeeditor.h"
#include "ui/titlebar.h"

#include <QProcess>
#include <QGraphicsBlurEffect>
#include <QToolButton>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    //setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
    //setWindowFlag(Qt::FramelessWindowHint, true);
    //setAttribute(Qt::WA_NoSystemBackground, true);
    //setAttribute(Qt::WA_TranslucentBackground, true);
    //setWindowFlags(Qt::Window
    // | Qt::CustomizeWindowHint | Qt::WindowSystemMenuHint);

    ui->setupUi(this);
    term1 = new QLightTerminal();
    ui->tabWidget->insertTab(0, term1, "Console1");
    QLightTerminal *term2 = new QLightTerminal();
    term2->setFontSize(14);
    term2->setBackground(QColor(100, 255, 0));
    ui->tabWidget->insertTab(1, term2, "Console2");
    QLightTerminal *term3 = new QLightTerminal();
    term3->setFontSize(18);
    term3->setBackground(QColor(24, 24, 24));
    ui->tabWidget->insertTab(2, term3, "Console3");
    ui->code->addWidget(new CodeEditor());

    menuWidget = new TitleBar(this);
    setMenuWidget(menuWidget);

    //QString program = {"./../../../../../Documents/coding/SimplePDF/node_modules/.bin/prettier"};

    //QProcess *myProcess = new QProcess(this);
    //myProcess->start(program, QStringList{""});
    //myProcess->waitForReadyRead();
    //qDebug() << myProcess->readAllStandardOutput();
    //qDebug() << myProcess->readAllStandardError();


    connect(ui->pushButton, &QPushButton::pressed, this, &MainWindow::increase);
    connect(ui->pushButton_2, &QPushButton::pressed, this, &MainWindow::decrease);
}

MainWindow::~MainWindow() {
    delete menuWidget;
    delete ui;
}

void MainWindow::increase() {
    i++;
    term1->setBackground(QColor(i, i, i));
    qDebug() << i;
}

void MainWindow::decrease() {
    i--;
    term1->setBackground(QColor(i, i, i));
    qDebug() << i;
}
