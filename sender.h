#ifndef SENDER_H
#define SENDER_H
#include <iostream>
#include <future>
#include <functional>

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
#include <fstream>
#include <mutex>
#include <math.h>

//TO FIX
#define MESS_SIZE 4096

class sender {
    public:
        // iP в виде строки, порт ресивера, есть ли сокет сообщений, кол-во сокетов в cоединении без учета сокета-сообщений
        sender(bool _is_msg_socket, int _num_sockets);
        ~sender();

        void connect(int *sockfd, int port);
        void disconnect(int sockfd);
        void connect_all(std::string _host, int _reciver_ports);
        void disconnect_all();

        void send_short_msg(std::string msg);
        void send_file(std::string msg);


        std::string host;
        unsigned int port;
        bool connected;
    

    private:
        int mess_sock; //сокет сообщений
        std::vector<std::future<void>> fut; // массив осинхронных потоков
        short counter_of_short_msg = 0;
        bool is_msg_socket;
        int num_sockets;
        static const unsigned int buffSize = 1000;
        //int sockfd;//establish connection to ID distribution server
        int reciver_port;
        std::vector<int> sockets;
        //std::mutex m;
};
#endif // CLIENTSOCK_H