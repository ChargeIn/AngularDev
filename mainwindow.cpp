#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "libs/QLightTerminal/qlightterminal.h"
#include "codeeditor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->insertTab(0, new QLightTerminal(), "Console");
    ui->code->addWidget(new CodeEditor());
}

MainWindow::~MainWindow()
{
    delete ui;
}

