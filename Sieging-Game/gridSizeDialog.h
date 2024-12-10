#ifndef GRIDSIZEDIALOG_H
#define GRIDSIZEDIALOG_H

#include <QDialog>

namespace Ui {
class Dialog; // 注意这里的类名要与 .ui 文件一致
}

class gridSizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit gridSizeDialog(QWidget *parent = nullptr);
    ~gridSizeDialog();

    // 获取选择的棋盘路数
    int getGridSize() const;

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::Dialog *ui; // 注意这里也是 Dialog
};

#endif // GRIDSIZEDIALOG_H
