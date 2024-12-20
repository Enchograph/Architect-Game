#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // 禁用高DPI缩放
    QCoreApplication::setAttribute(Qt::AA_DisableHighDpiScaling);

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/resources/icon.png"));
    MainWindow w;
    w.show();
    return a.exec();
}
