/********************************************************************************
** Form generated from reading UI file 'waveform.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WAVEFORM_H
#define UI_WAVEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WaveForm
{
public:
    QGraphicsView *graphicsView;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;

    void setupUi(QWidget *WaveForm)
    {
        if (WaveForm->objectName().isEmpty())
            WaveForm->setObjectName(QString::fromUtf8("WaveForm"));
        WaveForm->resize(932, 544);
        graphicsView = new QGraphicsView(WaveForm);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(10, 10, 911, 501));
        checkBox = new QCheckBox(WaveForm);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(20, 520, 71, 16));
        checkBox_2 = new QCheckBox(WaveForm);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setGeometry(QRect(100, 520, 91, 16));
        checkBox_3 = new QCheckBox(WaveForm);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setGeometry(QRect(210, 520, 91, 16));

        retranslateUi(WaveForm);

        QMetaObject::connectSlotsByName(WaveForm);
    } // setupUi

    void retranslateUi(QWidget *WaveForm)
    {
        WaveForm->setWindowTitle(QApplication::translate("WaveForm", "Form", nullptr));
        checkBox->setText(QApplication::translate("WaveForm", "\345\212\237\347\216\207\346\233\262\347\272\277", nullptr));
        checkBox_2->setText(QApplication::translate("WaveForm", "\347\274\223\345\206\262\345\212\237\347\216\207\346\233\262\347\272\277", nullptr));
        checkBox_3->setText(QApplication::translate("WaveForm", "\345\205\205\347\224\265\345\212\237\347\216\207\346\233\262\347\272\277", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WaveForm: public Ui_WaveForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WAVEFORM_H
