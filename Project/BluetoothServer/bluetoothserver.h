#ifndef BLUETOOTHSERVER_H
#define BLUETOOTHSERVER_H

#include<iostream>
#include<WinSock2.h>
#include<ws2bth.h>
#include<bluetoothapis.h>
#include<stdio.h>
#include<string>
#include<ole2.h>
#include<windows.h>
#include<rpcdce.h>
#include<bthdef.h>
#include<thread>

#pragma comment (lib, "ws2_32.lib")
#pragma comment(lib, "Bthprops.lib")
#pragma comment(lib, "RPCRT4.lib")
#pragma comment(lib, "Ole32.lib")

using namespace std;

class BluetoothServer
{
private:
    BLUETOOTH_FIND_RADIO_PARAMS bthFindRadioParams = { sizeof(BLUETOOTH_FIND_RADIO_PARAMS) };
    BLUETOOTH_RADIO_INFO bthRadioInfo = { sizeof(BLUETOOTH_RADIO_INFO), 0, };
    WSADATA wsData;
    SOCKET server = INVALID_SOCKET;
    SOCKADDR_BTH sockAddrBth;
    SOCKET clientInfo = INVALID_SOCKET;
    SOCKADDR_BTH client;

    CLSID create_clsid();

public:
    BluetoothServer() {}
    ~BluetoothServer() {}
    bool create_socket();
    void set_server_address();
    bool bind_to_server_address();
    bool listen_chanel();
    bool accept_connection();
    string receive_move();
    int send_move(string);
    void close_client();

};


#endif // BLUETOOTHSERVER_H
