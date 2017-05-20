#ifndef QSERIALTHREAD_H
#define QSERIALTHREAD_H

#include <QObject>
#include <QThread>
#include <QtDebug>

#include "serialset.h"

class QSerialThread : public QThread
{
    Q_OBJECT
public:
    QSerialThread(QObject *parent = 0);
    ~QSerialThread();

    //打开串口
    bool openSerial(struct Settings serialset);

    //关闭串口
    void closeSerial(void);

    //初始化，串口信息
    //bool initSerial(void);

    //写数据
    bool writeData(QByteArray data);

    //获取串口信息
    QStringList getSerialInfo(void);

public slots:
    //读数据
    void readData(void);

signals:
    //发送读到的数据
    void sendReadData(QByteArray data);

private:
    //串口定义
    QSerialPort *serial;

};

#endif // QSERIALTHREAD_H
