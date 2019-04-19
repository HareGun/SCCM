#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>

#pragma execution_character_set(¡°utf-8¡±)
#pragma anon_unions

typedef union{
  uint8_t data[29];

   struct{
    float Bat_voltage;
    float Bat_current;
    float Bat_power;
    float Bat_Buff;
    float Cap_voltage;
    float Cap_changeCurrent;
    uint8_t cap_status;
    union{
       struct{

        bool BQ_isEnable : 1;
        bool BQ_STAT : 1;
        bool BQ_PG : 1;
        bool LM3488_isEnable : 1;

        bool CAP_isOutput : 1;
      };
      uint32_t flagData;
    }flag;


  };

}usart_dataSend_t;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    usart_dataSend_t usart_dataSend;
private slots:

    void on_searchPortButton_clicked();
    void on_openSerialButton_clicked();
    void serialReadData(void);
    void serial_idleHandle();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    QTimer *serialTimer;
    QByteArray rxBuff;


    void refreshSerial();
    uint8_t USART_Checksum(uint8_t* buff, uint8_t len);
    void usart_getInfo(uint8_t* buff, uint16_t dataLength, usart_dataSend_t* dataOut);

};

#endif // MAINWINDOW_H
