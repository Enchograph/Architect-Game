#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::letGifBegin(QMovie *movie, QLabel *gifLabel)
{
    gifLabel->setMovie(movie);
    movie->start();
}
