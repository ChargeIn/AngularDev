#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow w;

    // Set app style sheet
    QFile mainStyleSheet("./styles/main.qss");
    mainStyleSheet.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(mainStyleSheet.readAll());

    app.setStyleSheet(styleSheet);

    w.show();

    return app.exec();
}
