#include "gameOverDialog.h"

gameOverDialog::gameOverDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("游戏结束！");
    gameOverDialogTextLabel = new QLabel("游戏结束！", this);
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
    gameOverDialogTextLabel->setText(text);  // 更新文本
}

void gameOverDialog::onButtonClicked()
{
    emit dialogClosed();  // 发出对话框关闭信号
    close();  // 关闭对话框
}
