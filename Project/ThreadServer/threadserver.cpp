#include "threadserver.h"

ThreadServer::ThreadServer(QObject *parent)
    : QObject{parent}
{
    bluetoothServer = new BluetoothServer();
}

QString ThreadServer::get_device_name()
{
    QBluetoothLocalDevice localDevice;
    return localDevice.name();
}

void ThreadServer::slot_to_create_server()
{
    bluetoothServer->set_server_address();
    if (bluetoothServer->create_socket()
            && bluetoothServer->bind_to_server_address()
            && bluetoothServer->listen_chanel()
            && bluetoothServer->accept_connection())
    {
        emit signal_for_accepted_connection("BLACK");
    }
    else
    {
        emit signal_for_error();
    }
}

void ThreadServer::slot_to_close_server()
{
    bluetoothServer->close_client();
    delete bluetoothServer;
}

void ThreadServer::slot_to_send_from_server(QString currentMoveString)
{
    int size = bluetoothServer->send_move(currentMoveString.toStdString());
    if (size != SOCKET_ERROR)
    {
        if (currentMoveString == ""
                || currentMoveString == "resign"
                || currentMoveString == "checkmate")
        {
            emit signal_to_end_server();
        }
    }
}

void ThreadServer::slot_to_receive_to_server()
{
    qDebug() << "slot_to_receive_to_server";
    QString opponentMove = QString::fromStdString(bluetoothServer->receive_move());
    qDebug() << "opponentMove: " << opponentMove;
    if (opponentMove == "" || opponentMove == "resign")
    {
        emit signal_for_error_opponent();
    }
    else if (opponentMove == "checkmate")
    {
        emit signal_to_end_server();
    }
    else
    {
        emit signal_to_receive_to_server(opponentMove);
    }
}


