#include "bluetoothserver.h"


bool BluetoothServer::create_socket()
{
    HANDLE Rad = NULL;
    BluetoothFindFirstRadio(&bthFindRadioParams, &Rad);
    BluetoothGetRadioInfo(Rad, &bthRadioInfo);

    WORD ver = MAKEWORD(2, 2);
    int wsOk = WSAStartup(ver, &wsData);
    if (wsOk != 0)
    {
        return false;
    }
    server = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
    if (server == INVALID_SOCKET)
    {
        WSACleanup();
        return false;
    }
    return true;

}

void BluetoothServer::set_server_address()
{
    memset(&sockAddrBth, 0, sizeof(sockAddrBth));
    sockAddrBth.addressFamily = AF_BTH;
    sockAddrBth.port = 5;
    sockAddrBth.btAddr = bthRadioInfo.address.ullLong;
    sockAddrBth.serviceClassId = create_clsid();
}

CLSID BluetoothServer::create_clsid()
{
    LPCOLESTR unicqueLine = L"{a75bc649-c8f8-48ff-992e-bbe8446a0ae2}";
    CLSID clsid;
    HRESULT is_error = CLSIDFromString(unicqueLine, &clsid);//из текстового представления в структурное
    if (is_error != NOERROR)
    {
    }
    return clsid;
}

bool BluetoothServer::bind_to_server_address()
{
    if (bind(server, (sockaddr *)&sockAddrBth, sizeof(sockAddrBth)) == SOCKET_ERROR)
    {
        close_server();
        return false;
    }
    return true;
}

bool BluetoothServer::listen_chanel()
{
    if (listen(server, SOMAXCONN) != 0)
    {
        close_server();
        return false;
    }
    return true;
}

bool BluetoothServer::accept_connection()
{
    int clientSize = sizeof(client);
    clientInfo = accept(server, (sockaddr *)&client, &clientSize);
    if (clientInfo == INVALID_SOCKET)
    {
        close_server();
        return false;
    }
    closesocket(server);
    return true;
}

string BluetoothServer::receive_move()
{
    char requestBuffer[1024] = {0};
    int bytesRead = recv(clientInfo,
                         requestBuffer,
                         sizeof(requestBuffer),
                         0);
    if (bytesRead == SOCKET_ERROR)
    {
        return "close_server";
    }
    return string(requestBuffer).substr(0, bytesRead);
}

int BluetoothServer::send_move(string move)
{
    return send(clientInfo, move.c_str(), move.size(), MSG_OOB);
}

void BluetoothServer::close_server()
{
    closesocket(server);
    WSACleanup();
}

void BluetoothServer::close_client()
{
    shutdown(clientInfo, SD_SEND);
    closesocket(clientInfo);
    WSACleanup();
}

