/********************************************************************************
** Form generated from reading UI file 'gridSizeDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRIDSIZEDIALOG_H
#define UI_GRIDSIZEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QDialogButtonBox *buttonBox;
    QSlider *horizontalSlider;
    QLabel *label;
    QCheckBox *robotCheckBox;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(600, 450);
        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(215, 310, 170, 40));
        buttonBox->setMinimumSize(QSize(170, 40));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        horizontalSlider = new QSlider(Dialog);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setGeometry(QRect(115, 180, 370, 30));
        horizontalSlider->setStyleSheet(QString::fromUtf8("/*QSlider::groove:horizontal {\n"
"border: 0px solid #bbb;\n"
"}\n"
"\n"
"QSlider::sub-page:horizontal {\n"
"background: #0e6d0e;\n"
"height:5px;\n"
"border-radius: 50%;\n"
"margin-top:8px;\n"
"margin-bottom:8px;\n"
"}\n"
"\n"
"QSlider::add-page:horizontal {\n"
"background: rgb(255,255, 255);\n"
"height:5px;\n"
"border: 0px solid #777;\n"
"border-radius: 50%;\n"
"margin-top:9px;\n"
"margin-bottom:9px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"background: rgb(193,204,208);\n"
"width: 30px;\n"
"border: 1px solid rgb(193,204,208);\n"
"border-radius: 15px; \n"
"margin-top:4px;\n"
"margin-bottom:4px;\n"
"}*/"));
        horizontalSlider->setMinimum(3);
        horizontalSlider->setMaximum(21);
        horizontalSlider->setPageStep(1);
        horizontalSlider->setOrientation(Qt::Horizontal);
        label = new QLabel(Dialog);
        label->setObjectName("label");
        label->setGeometry(QRect(185, 70, 230, 60));
        label->setAlignment(Qt::AlignCenter);
        robotCheckBox = new QCheckBox(Dialog);
        robotCheckBox->setObjectName("robotCheckBox");
        robotCheckBox->setGeometry(QRect(220, 250, 160, 20));

        retranslateUi(Dialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Dialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Dialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "\350\257\267\351\200\211\346\213\251\346\243\213\347\233\230\350\267\257\346\225\260", nullptr));
        robotCheckBox->setText(QCoreApplication::translate("Dialog", "\346\234\272\345\231\250\344\272\272\345\205\210\346\211\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRIDSIZEDIALOG_H
