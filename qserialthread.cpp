#include "qserialthread.h"

QSerialThread::QSerialThread(QObject *parent):QThread(parent)
{
    serial = new QSerialPort(this);
    //初始化串口信息
    //this->initSerial();
    connect(serial,SIGNAL(readyRead()),this,SLOT(readData()));
}

QSerialThread::~QSerialThread()
{
    this->closeSerial();
    delete serial;
}

//获取串口信息
QStringList QSerialThread::getSerialInfo()
{
    QStringList list;

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        list<<info.portName();
    }

    return list;
}

//打开串口
bool QSerialThread::openSerial(struct Settings serialset)
{
    this->closeSerial();

    serial->setPortName(serialset.name);
    serial->setBaudRate(serialset.baudRate);
    serial->setDataBits(serialset.dataBits);
    serial->setParity(serialset.parity);
    serial->setStopBits(serialset.stopBits);
    serial->setFlowControl(serialset.flowControl);

    if(serial->open(QIODevice::ReadWrite))
        return true;
    else
        return false;
}

//关闭串口
void QSerialThread::closeSerial()
{
    if(serial->isOpen())
        serial->close();
}

//读串口数据
void QSerialThread::readData()
{
    QByteArray data;
    data = serial->readAll();
    if(!data.isEmpty())
        emit sendReadData(data);
}

//写串口数据
bool QSerialThread::writeData(QByteArray data)
{
    int ret;
    ret = serial->write(data);
    if(ret == data.size())
        return true;
    else
        return false;
}

//初始化串口信息
bool QSerialThread::initSerial()
{
    struct Settings serialset;
    if(getSerialInfo().isEmpty())
        return false;

    serialset.name = getSerialInfo().at(0);
    serialset.baudRate = QSerialPort::Baud115200;
    serialset.dataBits = QSerialPort::Data8;
    serialset.parity = QSerialPort::NoParity;
    serialset.stopBits = QSerialPort::OneStop;
    serialset.flowControl = QSerialPort::NoFlowControl;

    return (this->openSerial(serialset));
}

