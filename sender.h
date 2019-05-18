#ifndef SENDER_H
#define SENDER_H
#include <iostream>
#include <future>
#include <functional>

#include <errno.h>
#include <string.h>

#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/signal.h>
#include <vector>


class sender {
    public:
        sender(std::string _host, std::vector<int> _reciver_ports);
        ~sender();

        void connect(int *sockfd, int port);
        void disconnect(int sockfd);
        void connect_all();
        void disconnect_all();

        void send_short_msg(std::string msg);



        std::string host;
        unsigned int port;
        bool connected;
    

    private:

        static const unsigned int buffSize = 1000;
        //int sockfd;//establish connection to ID distribution server
        char recv[buffSize];
        std::vector<int> reciver_ports;
        std::vector<int> sockets;
};
#endif // CLIENTSOCK_H