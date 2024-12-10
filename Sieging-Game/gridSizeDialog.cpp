#include "gridSizeDialog.h"
#include "ui_gridSizeDialog.h" // 包含自动生成的头文件

#include <QDebug> // 支持 qDebug

gridSizeDialog::gridSizeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog) // 注意这里也是 Dialog
{
    ui->setupUi(this);

    // 设置滑块的初始值和范围
    ui->horizontalSlider->setRange(5, 20); // 假设棋盘路数在5到20之间
    ui->horizontalSlider->setValue(10); // 默认值为10
    ui->label->setText("请选择棋盘路数: " + QString::number(ui->horizontalSlider->value()));
}

gridSizeDialog::~gridSizeDialog()
{
    delete ui;
}

// 获取选择的棋盘路数
int gridSizeDialog::getGridSize() const
{
    return ui->horizontalSlider->value();
}

void gridSizeDialog::on_buttonBox_accepted()
{
    qDebug() << "选择的棋盘路数是：" << getGridSize();
    this->accept();
}

void gridSizeDialog::on_buttonBox_rejected()
{
    this->reject();
}

void gridSizeDialog::on_horizontalSlider_valueChanged(int value)
{
    ui->label->setText("请选择棋盘路数: " + QString::number(value));
}
