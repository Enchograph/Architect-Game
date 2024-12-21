#ifndef GRIDSIZEDIALOG_H
#define GRIDSIZEDIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class gridSizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit gridSizeDialog(QWidget *parent = nullptr);
    ~gridSizeDialog();

    int getGridSize() const;
    bool getFirstHand()const;
    void setCheckBoxVisible(bool);
    void setValue(int value);


private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::Dialog *ui;
};

#endif // GRIDSIZEDIALOG_H
