#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    refreshSerial();
    serialTimer = new QTimer(this); //建立串口读写超时定时器
    connect(serialTimer,SIGNAL(timeout()),this,SLOT(serial_idleHandle()));//必须要有的

}

/**
 * @brief MainWindow::refreshSerial  刷新串口
 */
void MainWindow::refreshSerial(){
    ui->portBox->clear();
    foreach (const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;

        serial.setPort(info);
        ui->portBox->addItem(serial.portName());
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_searchPortButton_clicked()
{
    refreshSerial();
}

void MainWindow::on_openSerialButton_clicked()
{
    if(ui->openSerialButton->text() == tr("打开串口"))
        {
            serial = new QSerialPort;
            //设置串口名
            serial->setPortName(ui->portBox->currentText());
            //打开串口
            if(!serial->open(QIODevice::ReadWrite)){
                /* open failed */
                QMessageBox::information(this,tr("Error"),tr("open failed"));
                qDebug() << "serial open failed...";
                return;
            }
            //设置波特率
            serial->setBaudRate(QSerialPort::Baud115200);//设置波特率为115200
            //设置数据位数
            serial->setDataBits(QSerialPort::Data8);//设置数据位8
            //设置校验位
            serial->setParity(QSerialPort::NoParity);
            //设置停止位
            serial->setStopBits(QSerialPort::OneStop);//停止位设置为1
            //设置流控制
            serial->setFlowControl(QSerialPort::NoFlowControl);//设置为无流控制


            //关闭设置菜单使能
            ui->portBox->setEnabled(false);
            ui->searchPortButton->setEnabled(false);
            ui->openSerialButton->setText(tr("关闭串口"));

            //连接信号槽
            QObject::connect(serial,&QSerialPort::readyRead,this,&MainWindow::serialReadData);
            qDebug() << "serial open...";
        }
        else
        {
            //关闭串口
            serial->clear();
            serial->close();
            serial->deleteLater();

            //恢复设置使能
            ui->portBox->setEnabled(true);
            ui->searchPortButton->setEnabled(true);
            ui->openSerialButton->setText(tr("打开串口"));
            qDebug() << "serial close...";

        }
}

/**
  * @brief  数据包校验
  * @param[in]  buff	数据包
  * @retval 	0 校验失败，1校验通过
  */
uint8_t MainWindow::USART_Checksum(uint8_t* buff, uint8_t len){
    uint8_t sum = 0;

    for(uint8_t i=0; i<len-1; i++){
        sum += buff[i];
    }

    if(sum == buff[len-1]){
        //校验通过
        return 1;
    }
    else{
        return 0;
    }

}

void MainWindow::usart_getInfo(uint8_t* buff, uint16_t dataLength, usart_dataSend_t* dataOut){

    for(uint16_t n = 0; n < dataLength; ){
        //匹配帧头
        if( (buff[n] == 0x5A) && (buff[n+1] == 0x5A) ){
            if(USART_Checksum(&buff[n], 32)){
                memcpy(dataOut->data, &buff[n+2], sizeof(uint8_t[29]));
                QString str;
                str.sprintf("%.02f V", dataOut->Bat_voltage);
                ui->batVoltageLabel->setText(str);

                str.sprintf("%.02f A", dataOut->Bat_current);
                ui->batCurrentLabel->setText(str);

                str.sprintf("%.02f W", dataOut->Bat_power);
                ui->batPowerLabel->setText(str);

                ui->batBuff_progressBar->setValue(dataOut->Bat_Buff);

                str.sprintf("%.02f V", dataOut->Cap_voltage);
                ui->capVoltageLabel->setText(str);

                str.sprintf("%.02f A", dataOut->Cap_changeCurrent);
                ui->capCurrentLabel->setText(str);

                ui->BQ_EN_checkBox->setChecked(dataOut->flag.BQ_isEnable);
                ui->BQ_PG_checkBox->setChecked(dataOut->flag.BQ_PG);
                ui->BQ_STAT_checkBox->setChecked(dataOut->flag.BQ_STAT);
                ui->CAP_OUT_checkBox->setChecked(dataOut->flag.CAP_isOutput);
                ui->boostEN_checkBox->setChecked(dataOut->flag.LM3488_isEnable);
                ui->cap_statusComboBox->setCurrentIndex(dataOut->cap_status);

                return;
            }
            else{
                n++;
            }

        }
        else{
            n++;
        }
    }

}

void MainWindow::serial_idleHandle(void){
    serialTimer->stop();
//    qDebug() << "serial idle handle...";
    ui->rxLabel->setText(rxBuff.toHex());
    usart_getInfo((uint8_t*)rxBuff.data(),rxBuff.length(),&usart_dataSend);
    rxBuff.clear();
}


//读取接收到的信息
void MainWindow::serialReadData(void)
{
    serialTimer->start(5);
    rxBuff.append(serial->readAll());

}
