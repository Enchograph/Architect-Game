#include "gridSizeDialog.h"
#include "ui_gridSizeDialog.h"

gridSizeDialog::gridSizeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->horizontalSlider->setRange(5, 20); // 假设棋盘路数在5到20之间
    ui->horizontalSlider->setValue(10); // 默认值为10
    ui->label->setText("请选择棋盘路数: " + QString::number(ui->horizontalSlider->value()));
}

gridSizeDialog::~gridSizeDialog()
{
    delete ui;
}

int gridSizeDialog::getGridSize() const
{
    return ui->horizontalSlider->value();
}

void gridSizeDialog::on_buttonBox_accepted()
{
    accept();
}

void gridSizeDialog::on_buttonBox_rejected()
{
    reject();
}

void gridSizeDialog::on_horizontalSlider_valueChanged(int value)
{
    ui->label->setText("请选择棋盘路数: " + QString::number(value));
}
