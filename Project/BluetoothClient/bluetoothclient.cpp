#include "bluetoothclient.h"


QStringList BluetoothClient::find_device()
{
    bluetoothDev.clear();
    HANDLE hRadio = NULL;
    while (TRUE)
    {
        HBLUETOOTH_RADIO_FIND hbthRadioFind = BluetoothFindFirstRadio(&bthFindRadioParams, &hRadio);
        int radioNum = 1;
        do
        {
            BluetoothGetRadioInfo(hRadio, &bthRadioInfo);
            bluetooth_filters.hRadio = hRadio;
            ZeroMemory(&tempDevInfo, sizeof(BLUETOOTH_DEVICE_INFO));
            tempDevInfo.dwSize = sizeof(BLUETOOTH_DEVICE_INFO);
            HBLUETOOTH_DEVICE_FIND hbthDevFind = BluetoothFindFirstDevice(&bluetooth_filters, &tempDevInfo);
            radioNum++;
            int devNum = 1;
            do
            {
                bluetoothDev.push_back(tempDevInfo);
                devNum++;
            }
            while (BluetoothFindNextDevice(hbthDevFind, &tempDevInfo));
            BluetoothFindDeviceClose(hbthDevFind);
        }
        while (BluetoothFindNextRadio(&bthFindRadioParams, &hRadio));
        BluetoothFindRadioClose(hbthRadioFind);
        if (!BluetoothFindNextRadio(&bthFindRadioParams, &hRadio))
        {
            break;
        }
        Sleep(1000);
    }
    return get_vector();
}

QStringList BluetoothClient::get_vector()
{
    QStringList deviceList = QStringList();
    for (int i = 0; i < bluetoothDev.size(); i++)
    {
        char str[248];
        WideCharToMultiByte(CP_UTF8, 0, bluetoothDev[i].szName, -1, str, sizeof(str), NULL, NULL);
        deviceList.append(QString(str));
    }
    return deviceList;
}

bool BluetoothClient::create_socket()
{
    WORD ver = MAKEWORD(2, 2);
    int wsOk = WSAStartup(ver, &wsData);
    if (wsOk != 0)
    {
        return false;
    }
    client = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
    if (client == INVALID_SOCKET)
    {
        WSACleanup();
        return false;
    }
    return true;
}

void BluetoothClient::set_server_address(int connectNum)
{
    memset(&sockAddrBth, 0, sizeof(sockAddrBth));
    sockAddrBth.addressFamily = AF_BTH;
    sockAddrBth.port = 5;
    sockAddrBth.btAddr = bluetoothDev[connectNum].Address.ullLong;
    sockAddrBth.serviceClassId = create_clsid();
}

CLSID BluetoothClient::create_clsid()
{
    LPCOLESTR unicqueLine = L"{a75bc649-c8f8-48ff-992e-bbe8446a0ae2}";
    CLSID clsid;
    CLSIDFromString(unicqueLine, &clsid);
    return clsid;
}

bool BluetoothClient::connect_to_server()
{
    int connRes = connect(client, (sockaddr *)&sockAddrBth, sizeof(sockAddrBth));
    if (connRes == SOCKET_ERROR)
    {
        return false;
    }
    return true;
}

int BluetoothClient::send_move(string move)
{
    return send(client, move.c_str(), move.size(), MSG_OOB);
}

string BluetoothClient::receive_move()
{
    char requestBuffer[1024] = {0};
    int bytesRead = recv(client,
                         requestBuffer,
                         sizeof(requestBuffer),
                         0);
    if (bytesRead == SOCKET_ERROR)
    {
        return "resign";
    }
    return string(requestBuffer).substr(0, bytesRead);
}

void BluetoothClient::close_client()
{
    if (client != INVALID_SOCKET)
    {
        shutdown(client, SD_BOTH);
        closesocket(client);
        WSACleanup();
        cout << "WSACLEANUP";
    }
}
