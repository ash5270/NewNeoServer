#pragma once

//winsock2�� ����ϱ� ���� �Ʒ� �ڸ�Ʈ �߰� 
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"mswsock.lib")

#include <WinSock2.h>
#include <MSWSock.h>
#include <WS2tcpip.h>

#include"../system/NeoLog.h"

const size_t Memory_Pool_Block_Size = 512;
const size_t Memory_Pool_Block_Count = 10000;
