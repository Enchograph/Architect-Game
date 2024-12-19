#ifndef GAMEOVERDIALOG_H
#define GAMEOVERDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class gameOverDialog : public QDialog
{
    Q_OBJECT

public:
    explicit gameOverDialog(QWidget *parent = nullptr);
    void setDialogText(const QString &text);  // 设置对话框显示的文字

signals:
    void dialogClosed();

private slots:
    void onButtonClicked();

private:
    QLabel *gameOverDialogTextLabel;
    QPushButton *gameOverDialogButton;
};

#endif // GAMEOVERDIALOG_H
