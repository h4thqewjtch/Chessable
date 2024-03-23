#ifndef BLUETOOTHCLIENT_H
#define BLUETOOTHCLIENT_H

#include <QStringList>


#include<iostream>
#include<WinSock2.h>
#include<ws2bth.h>
#include<bluetoothapis.h>
#include<stdio.h>
#include<string.h>
#include<vector>
#include<windows.h>
#include<bthdef.h>
#include<objbase.h>
#include<ole2.h>

#pragma comment(lib, "Bthprops.lib")
#pragma comment (lib, "ws2_32.lib")
#pragma comment(lib, "Ole32.lib")

using namespace std;

class BluetoothClient
{

private:
    vector <BLUETOOTH_DEVICE_INFO> bluetoothDev;
    BLUETOOTH_FIND_RADIO_PARAMS bthFindRadioParams = { sizeof(BLUETOOTH_FIND_RADIO_PARAMS) };
    BLUETOOTH_RADIO_INFO bthRadioInfo = { sizeof(BLUETOOTH_RADIO_INFO), 0, };
    BLUETOOTH_DEVICE_SEARCH_PARAMS bluetooth_filters =
    {
        sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS),
        1,
        0,
        1,
        1,
        1,
        15,
        NULL
    };
    BLUETOOTH_DEVICE_INFO tempDevInfo = { sizeof(BLUETOOTH_DEVICE_INFO), 0, };
    WSADATA wsData;
    SOCKET client;
    SOCKADDR_BTH sockAddrBth;

private slots:
    CLSID create_clsid();

public:
    BluetoothClient() {}
    ~BluetoothClient() {}
    QStringList find_device();
    QStringList get_vector();
    bool create_socket();
    void set_server_address(int);
    bool connect_to_server();
    int send_move(string);
    string receive_move();
    void close_client();


};

#endif // BLUETOOTHCLIENT_H
