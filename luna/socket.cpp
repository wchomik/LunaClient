#include "socket.h"

#include <stdexcept>

#ifdef _WIN32
int sockInit()
{
    WSADATA wsa_data;
    return WSAStartup(MAKEWORD(2,2), &wsa_data);
}

int sockQuit()
{
    return WSACleanup();
}

int sockClose(sock_t sock)
{
    return closesocket(sock);
}
#else
int sockInit()
{
    return 0;
}

void sockQuit()
{
    return 0;
}

int sockClose(sock_t sock){
    return close(sock);
}
#endif


