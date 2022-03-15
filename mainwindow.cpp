#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "libs/QLightTerminal/qlightterminal.h"
#include "codeeditor.h"

#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->insertTab(0, new QLightTerminal(), "Console");
    ui->code->addWidget(new CodeEditor());


    QString program = {"./../../../../../Documents/coding/SimplePDF/node_modules/.bin/prettier"};

    QProcess *myProcess = new QProcess(this);
    myProcess->start(program, QStringList{""});
    myProcess->waitForReadyRead();
    qDebug() << myProcess->readAllStandardOutput();
    qDebug() << myProcess->readAllStandardError();
}

MainWindow::~MainWindow()
{
    delete ui;
}

