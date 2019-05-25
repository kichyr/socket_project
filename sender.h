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
#define MESS_SIZE 4

namespace project1 {
class synchronized_file_reader {
    private:
        std::string path;
        std::ifstream file;
        int f_length;
        std::mutex mutex_to_read;
    public:
        void init(const std::string& _path) {
            path = _path;
            file.open(path);
            file.seekg(0, file.end);
            f_length = file.tellg();
            file.seekg(0, file.beg);
        }

        int read(int from_position, char* buff) {
            if(from_position >= f_length) return 0;
            mutex_to_read.lock();
            int num_bytes_to_read = std::min(MESS_SIZE, f_length - from_position);
            file.seekg(from_position, file.beg);
            file.read(buff, MESS_SIZE);
            file.seekg(0);
            mutex_to_read.unlock();
            return num_bytes_to_read;
        }

        int get_file_lenght() {
            return f_length;
        }
};    

class sender {
    public:
        // iP в виде строки, порт ресивера, есть ли сокет сообщений, кол-во сокетов в cоединении без учета сокета-сообщений
        void init(bool _is_msg_socket, int _num_sockets);
        ~sender();

        void connect(int *sockfd, int port);
        void disconnect(int sockfd);
        void connect_all(std::string _host, int _reciver_ports);
        void disconnect_all();

        void send_short_msg(std::string msg);
        void send_file(char* path);


        std::string host;
        unsigned int port;
        bool connected;
    

    private:
        synchronized_file_reader reader;
        int sending_file_flag = 0;
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
}
#endif // CLIENTSOCK_H