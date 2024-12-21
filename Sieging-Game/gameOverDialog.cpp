#include "gameOverDialog.h"

gameOverDialog::gameOverDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("游戏结束！");
    gameOverDialogTextLabel = new QLabel("游戏结束！", this);
    QFont font("", 12);
    gameOverDialogTextLabel->setFont(font);
    gameOverDialogButton = new QPushButton("确定", this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(gameOverDialogTextLabel);
    layout->addWidget(gameOverDialogButton);
    setLayout(layout);

    connect(gameOverDialogButton, &QPushButton::clicked, this, &gameOverDialog::onButtonClicked);
}

void gameOverDialog::setDialogText(const QString &text)
{
    gameOverDialogTextLabel->setText(text);
}

void gameOverDialog::onButtonClicked()
{
    emit dialogClosed();
    close();
}
