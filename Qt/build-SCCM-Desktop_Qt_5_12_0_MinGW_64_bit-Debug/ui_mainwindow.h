/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QComboBox *portBox;
    QPushButton *openSerialButton;
    QPushButton *searchPortButton;
    QLabel *rxLabel;
    QGroupBox *BatGroupBox;
    QLabel *label;
    QLabel *batVoltageLabel;
    QLabel *label_2;
    QLabel *batCurrentLabel;
    QLabel *label_3;
    QLabel *batPowerLabel;
    QLabel *label_4;
    QProgressBar *batBuff_progressBar;
    QGroupBox *CapGroupBox_2;
    QLabel *label_5;
    QLabel *capVoltageLabel;
    QLabel *label_6;
    QLabel *capCurrentLabel;
    QGroupBox *StatBackGroupBox;
    QCheckBox *BQ_EN_checkBox;
    QCheckBox *boostEN_checkBox;
    QCheckBox *CAP_OUT_checkBox;
    QCheckBox *BQ_PG_checkBox;
    QCheckBox *BQ_STAT_checkBox;
    QComboBox *cap_statusComboBox;
    QLabel *label_7;
    QGroupBox *StatSetGroupBox;
    QCheckBox *BQ_EN_SetcheckBox;
    QCheckBox *boostEN_SetcheckBox;
    QCheckBox *CAP_OUT_SetcheckBox;
    QPushButton *pushButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(401, 370);
        MainWindow->setTabletTracking(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        portBox = new QComboBox(centralWidget);
        portBox->setObjectName(QString::fromUtf8("portBox"));
        portBox->setGeometry(QRect(10, 10, 91, 22));
        openSerialButton = new QPushButton(centralWidget);
        openSerialButton->setObjectName(QString::fromUtf8("openSerialButton"));
        openSerialButton->setGeometry(QRect(190, 10, 71, 23));
        searchPortButton = new QPushButton(centralWidget);
        searchPortButton->setObjectName(QString::fromUtf8("searchPortButton"));
        searchPortButton->setGeometry(QRect(110, 10, 75, 23));
        rxLabel = new QLabel(centralWidget);
        rxLabel->setObjectName(QString::fromUtf8("rxLabel"));
        rxLabel->setGeometry(QRect(10, 40, 381, 16));
        BatGroupBox = new QGroupBox(centralWidget);
        BatGroupBox->setObjectName(QString::fromUtf8("BatGroupBox"));
        BatGroupBox->setGeometry(QRect(10, 70, 381, 80));
        label = new QLabel(BatGroupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 31, 16));
        batVoltageLabel = new QLabel(BatGroupBox);
        batVoltageLabel->setObjectName(QString::fromUtf8("batVoltageLabel"));
        batVoltageLabel->setGeometry(QRect(60, 20, 61, 16));
        label_2 = new QLabel(BatGroupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(140, 20, 31, 16));
        batCurrentLabel = new QLabel(BatGroupBox);
        batCurrentLabel->setObjectName(QString::fromUtf8("batCurrentLabel"));
        batCurrentLabel->setGeometry(QRect(180, 20, 61, 16));
        label_3 = new QLabel(BatGroupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(250, 20, 31, 16));
        batPowerLabel = new QLabel(BatGroupBox);
        batPowerLabel->setObjectName(QString::fromUtf8("batPowerLabel"));
        batPowerLabel->setGeometry(QRect(290, 20, 61, 16));
        label_4 = new QLabel(BatGroupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 50, 61, 16));
        batBuff_progressBar = new QProgressBar(BatGroupBox);
        batBuff_progressBar->setObjectName(QString::fromUtf8("batBuff_progressBar"));
        batBuff_progressBar->setGeometry(QRect(80, 50, 271, 16));
        batBuff_progressBar->setAutoFillBackground(false);
        batBuff_progressBar->setMaximum(60);
        batBuff_progressBar->setValue(60);
        batBuff_progressBar->setTextVisible(true);
        batBuff_progressBar->setInvertedAppearance(false);
        CapGroupBox_2 = new QGroupBox(centralWidget);
        CapGroupBox_2->setObjectName(QString::fromUtf8("CapGroupBox_2"));
        CapGroupBox_2->setGeometry(QRect(10, 160, 381, 51));
        label_5 = new QLabel(CapGroupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 20, 31, 16));
        capVoltageLabel = new QLabel(CapGroupBox_2);
        capVoltageLabel->setObjectName(QString::fromUtf8("capVoltageLabel"));
        capVoltageLabel->setGeometry(QRect(60, 20, 61, 16));
        label_6 = new QLabel(CapGroupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(140, 20, 51, 16));
        capCurrentLabel = new QLabel(CapGroupBox_2);
        capCurrentLabel->setObjectName(QString::fromUtf8("capCurrentLabel"));
        capCurrentLabel->setGeometry(QRect(200, 20, 61, 16));
        StatBackGroupBox = new QGroupBox(centralWidget);
        StatBackGroupBox->setObjectName(QString::fromUtf8("StatBackGroupBox"));
        StatBackGroupBox->setGeometry(QRect(10, 220, 381, 81));
        BQ_EN_checkBox = new QCheckBox(StatBackGroupBox);
        BQ_EN_checkBox->setObjectName(QString::fromUtf8("BQ_EN_checkBox"));
        BQ_EN_checkBox->setEnabled(false);
        BQ_EN_checkBox->setGeometry(QRect(20, 20, 71, 16));
        BQ_EN_checkBox->setChecked(false);
        boostEN_checkBox = new QCheckBox(StatBackGroupBox);
        boostEN_checkBox->setObjectName(QString::fromUtf8("boostEN_checkBox"));
        boostEN_checkBox->setEnabled(false);
        boostEN_checkBox->setGeometry(QRect(110, 20, 71, 16));
        boostEN_checkBox->setChecked(false);
        CAP_OUT_checkBox = new QCheckBox(StatBackGroupBox);
        CAP_OUT_checkBox->setObjectName(QString::fromUtf8("CAP_OUT_checkBox"));
        CAP_OUT_checkBox->setEnabled(false);
        CAP_OUT_checkBox->setGeometry(QRect(200, 20, 71, 16));
        CAP_OUT_checkBox->setTabletTracking(false);
        CAP_OUT_checkBox->setCheckable(true);
        CAP_OUT_checkBox->setChecked(false);
        BQ_PG_checkBox = new QCheckBox(StatBackGroupBox);
        BQ_PG_checkBox->setObjectName(QString::fromUtf8("BQ_PG_checkBox"));
        BQ_PG_checkBox->setEnabled(false);
        BQ_PG_checkBox->setGeometry(QRect(20, 60, 71, 16));
        BQ_PG_checkBox->setChecked(false);
        BQ_STAT_checkBox = new QCheckBox(StatBackGroupBox);
        BQ_STAT_checkBox->setObjectName(QString::fromUtf8("BQ_STAT_checkBox"));
        BQ_STAT_checkBox->setEnabled(false);
        BQ_STAT_checkBox->setGeometry(QRect(20, 40, 71, 16));
        BQ_STAT_checkBox->setChecked(false);
        cap_statusComboBox = new QComboBox(StatBackGroupBox);
        cap_statusComboBox->addItem(QString());
        cap_statusComboBox->addItem(QString());
        cap_statusComboBox->addItem(QString());
        cap_statusComboBox->setObjectName(QString::fromUtf8("cap_statusComboBox"));
        cap_statusComboBox->setEnabled(false);
        cap_statusComboBox->setGeometry(QRect(200, 51, 69, 21));
        label_7 = new QLabel(StatBackGroupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setEnabled(false);
        label_7->setGeometry(QRect(130, 50, 54, 21));
        StatSetGroupBox = new QGroupBox(centralWidget);
        StatSetGroupBox->setObjectName(QString::fromUtf8("StatSetGroupBox"));
        StatSetGroupBox->setGeometry(QRect(10, 310, 381, 51));
        BQ_EN_SetcheckBox = new QCheckBox(StatSetGroupBox);
        BQ_EN_SetcheckBox->setObjectName(QString::fromUtf8("BQ_EN_SetcheckBox"));
        BQ_EN_SetcheckBox->setEnabled(true);
        BQ_EN_SetcheckBox->setGeometry(QRect(20, 20, 71, 16));
        BQ_EN_SetcheckBox->setChecked(false);
        boostEN_SetcheckBox = new QCheckBox(StatSetGroupBox);
        boostEN_SetcheckBox->setObjectName(QString::fromUtf8("boostEN_SetcheckBox"));
        boostEN_SetcheckBox->setEnabled(true);
        boostEN_SetcheckBox->setGeometry(QRect(110, 20, 71, 16));
        boostEN_SetcheckBox->setChecked(false);
        CAP_OUT_SetcheckBox = new QCheckBox(StatSetGroupBox);
        CAP_OUT_SetcheckBox->setObjectName(QString::fromUtf8("CAP_OUT_SetcheckBox"));
        CAP_OUT_SetcheckBox->setEnabled(true);
        CAP_OUT_SetcheckBox->setGeometry(QRect(200, 20, 71, 16));
        CAP_OUT_SetcheckBox->setTabletTracking(false);
        CAP_OUT_SetcheckBox->setCheckable(true);
        CAP_OUT_SetcheckBox->setChecked(false);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(310, 10, 75, 23));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        openSerialButton->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        searchPortButton->setText(QApplication::translate("MainWindow", "\346\220\234\347\264\242\344\270\262\345\217\243", nullptr));
        rxLabel->setText(QString());
        BatGroupBox->setTitle(QApplication::translate("MainWindow", "\347\224\265\346\261\240", nullptr));
        label->setText(QApplication::translate("MainWindow", "\347\224\265\345\216\213:", nullptr));
        batVoltageLabel->setText(QApplication::translate("MainWindow", "V", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\347\224\265\346\265\201:", nullptr));
        batCurrentLabel->setText(QApplication::translate("MainWindow", "A", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\345\212\237\347\216\207:", nullptr));
        batPowerLabel->setText(QApplication::translate("MainWindow", "W", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "\347\274\223\345\206\262\345\212\237\347\216\207:", nullptr));
        batBuff_progressBar->setFormat(QApplication::translate("MainWindow", "%vJ", nullptr));
        CapGroupBox_2->setTitle(QApplication::translate("MainWindow", "\347\224\265\345\256\271", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "\347\224\265\345\216\213:", nullptr));
        capVoltageLabel->setText(QApplication::translate("MainWindow", "V", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "\345\205\205\347\224\265\347\224\265\346\265\201:", nullptr));
        capCurrentLabel->setText(QApplication::translate("MainWindow", "A", nullptr));
        StatBackGroupBox->setTitle(QApplication::translate("MainWindow", "\347\212\266\346\200\201\350\277\224\345\233\236", nullptr));
        BQ_EN_checkBox->setText(QApplication::translate("MainWindow", "\345\205\205\347\224\265\344\275\277\350\203\275", nullptr));
        boostEN_checkBox->setText(QApplication::translate("MainWindow", "\345\215\207\345\216\213\344\275\277\350\203\275", nullptr));
        CAP_OUT_checkBox->setText(QApplication::translate("MainWindow", "\347\224\265\345\256\271\350\276\223\345\207\272", nullptr));
        BQ_PG_checkBox->setText(QApplication::translate("MainWindow", "BQ_PG", nullptr));
        BQ_STAT_checkBox->setText(QApplication::translate("MainWindow", "BQ_STAT", nullptr));
        cap_statusComboBox->setItemText(0, QApplication::translate("MainWindow", "\344\275\216", nullptr));
        cap_statusComboBox->setItemText(1, QApplication::translate("MainWindow", "\344\270\255", nullptr));
        cap_statusComboBox->setItemText(2, QApplication::translate("MainWindow", "\346\273\241", nullptr));

        label_7->setText(QApplication::translate("MainWindow", "\347\224\265\345\256\271\347\224\265\351\207\217\357\274\232", nullptr));
        StatSetGroupBox->setTitle(QApplication::translate("MainWindow", "\347\212\266\346\200\201\350\256\276\347\275\256", nullptr));
        BQ_EN_SetcheckBox->setText(QApplication::translate("MainWindow", "\345\205\205\347\224\265\344\275\277\350\203\275", nullptr));
        boostEN_SetcheckBox->setText(QApplication::translate("MainWindow", "\345\215\207\345\216\213\344\275\277\350\203\275", nullptr));
        CAP_OUT_SetcheckBox->setText(QApplication::translate("MainWindow", "\347\224\265\345\256\271\350\276\223\345\207\272", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "\346\263\242\345\275\242\345\233\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
