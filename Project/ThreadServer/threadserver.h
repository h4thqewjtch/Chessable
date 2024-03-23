#ifndef THREADSERVER_H
#define THREADSERVER_H

#include <QBluetoothLocalDevice>
#include <QObject>
#include <QDebug>

#include "../BluetoothServer/bluetoothserver.h"

class ThreadServer : public QObject
{
    Q_OBJECT

private:
    BluetoothServer *bluetoothServer = nullptr;

public slots:
    void slot_to_create_server();
    void slot_to_close_server();
    void slot_to_send_from_server(QString);
    void slot_to_receive_to_server();

public:
    explicit ThreadServer(QObject *parent = nullptr);
    QString get_device_name();

signals:
    void signal_for_error();
    void signal_for_accepted_connection(QString);
    void signal_to_receive_to_server(QString);
    void signal_to_end_server();
    void signal_for_error_opponent();
};

#endif // THREADSERVER_H
