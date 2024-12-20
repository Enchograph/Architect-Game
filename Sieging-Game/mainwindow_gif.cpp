#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::letGifBegin(QMovie *movie,QLabel * gifLabel){


//                QSize si(gifLabel->width(),gifLabel->height());
//                movie->setScaledSize(si);
    gifLabel->setMovie(movie);

    movie->start();

}
