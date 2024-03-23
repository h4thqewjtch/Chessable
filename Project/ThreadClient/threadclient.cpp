#include "threadclient.h"

ThreadClient::ThreadClient(QObject *parent)
    : QObject{parent}
{
    bluetoothClient = new BluetoothClient();
}

QString ThreadClient::get_device_name()
{
    QBluetoothLocalDevice localDevice;
    return localDevice.name();
}

void ThreadClient::slot_to_find_devices()
{
    QStringList list = bluetoothClient->find_device();
    emit signal_to_get_devices_list(list);
}

void ThreadClient::slot_to_create_client(int number)
{
    bluetoothClient->set_server_address(number);
    if (bluetoothClient->create_socket()
            && bluetoothClient->connect_to_server())
    {
        emit signal_for_accepted_connection("WHITE");
    }
    else
    {
        emit signal_for_error();
    }
}

void ThreadClient::slot_to_close_client()
{
    bluetoothClient->close_client();
    delete bluetoothClient;
}

void ThreadClient::slot_to_send_from_client(QString currentMoveString)
{
    int size = bluetoothClient->send_move(currentMoveString.toStdString());
    if (size != SOCKET_ERROR)
    {
        if (currentMoveString == ""
                || currentMoveString == "checkmate")
        {
            emit signal_to_end_client();
        }
    }
}

void ThreadClient::slot_to_receive_to_client()
{
    qDebug() << "slot_to_receive_to_client";
    QString opponentMove = QString::fromStdString(bluetoothClient->receive_move());
    qDebug() << "opponentMove: " << opponentMove;
    if (opponentMove == "")
    {
        emit signal_for_error_opponent();
    }
    else if (opponentMove == "checkmate")
    {
        emit signal_to_end_client();
    }
    else
    {
        emit signal_to_receive_to_client(opponentMove);
    }
}
