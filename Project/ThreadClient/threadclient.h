#ifndef THREADCLIENT_H
#define THREADCLIENT_H

#include <QBluetoothLocalDevice>
#include <QObject>
#include <QDebug>

#include "../BluetoothClient/bluetoothclient.h"

class ThreadClient : public QObject
{
    Q_OBJECT

private:
    BluetoothClient *bluetoothClient = nullptr;

public slots:
    void slot_to_find_devices();
    void slot_to_create_client(int);
    void slot_to_close_client();
    void slot_to_send_from_client(QString);
    void slot_to_receive_to_client();

public:
    explicit ThreadClient(QObject *parent = nullptr);
    void get_list();
    QString get_device_name();

signals:
    void signal_for_error();
    void signal_for_accepted_connection(QString);
    void signal_to_get_devices_list(QStringList);
    void signal_to_receive_to_client(QString);
    void signal_to_end_client();
    void signal_for_error_opponent();
};

#endif // THREADCLIENT_H
