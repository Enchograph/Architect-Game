#include "gridSizeDialog.h"
#include "ui_gridSizeDialog.h"

gridSizeDialog::gridSizeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->horizontalSlider->setRange(5, 20); // 令棋盘路数在5到20之间
    ui->horizontalSlider->setValue(7); // 默认值为7
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

bool gridSizeDialog::getFirstHand()const
{
    return ui->robotCheckBox->isChecked();
}

void gridSizeDialog::setCheckBoxVisible(bool a)
{
    ui->robotCheckBox->setVisible(a);
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

void gridSizeDialog::setValue(int value)
{
    ui->horizontalSlider->setValue(value);
}
