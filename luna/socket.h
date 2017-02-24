#ifndef SOCKET_H
#define SOCKET_H

#ifdef _WIN32
    // fucking windows and its macros
    #define NOMINMAX
    /* See http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32 */
    #ifndef _WIN32_WINNT
        #define _WIN32_WINNT 0x0501  /* Windows XP. */
    #endif
    #include <winsock2.h>
    #include <Ws2tcpip.h>
    using sock_t = unsigned;
#else
    /* Assume that any non-Windows platform uses POSIX-style sockets instead. */
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
    #include <unistd.h> /* Needed for close() */
    using sock_t = int;
#endif

int sockInit();
int sockQuit();
int sockClose(sock_t sock);

#endif // SOCKET_H
