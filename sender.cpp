#include "sender.h"

project::sender::sender(bool _is_msg_socket, int _num_sockets) {
    is_msg_socket = _is_msg_socket;
    num_sockets = _num_sockets;
    sockets.resize(num_sockets);
    fut.resize(num_sockets);
}

project::sender::~sender() {
    disconnect_all();
}

void project::sender::connect_all(std::string _host, int _reciver_port) {
    host = _host;
    reciver_port = _reciver_port;

    int sended;
    char type_msg;
    //сокет для передачи коротких сообщений
    if(is_msg_socket){ 
        type_msg = 1;
        connect(&mess_sock, reciver_port);
        if((sended = write(mess_sock, &type_msg, 1)) < 0)
            throw "can't send type of msg";
    }
    //сокеты для передачи больших файлов
    type_msg = 0;
    for(int i = 0; i < num_sockets; i++) {
        connect(&sockets[i], reciver_port);
        if((sended = write(sockets[i], &type_msg, 1)) < 0)
            throw "can't send type of msg";
    }
}

void project::sender::connect(int *sockfd, int port) {
    struct sockaddr_in servaddr;
    struct hostent* server;

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    server = gethostbyname(host.data());
    bcopy((char*) server->h_addr, (char*) &servaddr.sin_addr.s_addr, server->h_length);
    servaddr.sin_port = htons(port);

    *sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(::connect(*sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0)
        throw "can't connect to host";
}

void project::sender::disconnect_all() {
    for(auto socket : sockets)
        disconnect(socket);
    if(is_msg_socket)
        disconnect(mess_sock);
}

void project::sender::disconnect(int sockfd) {
    close(sockfd);
}

void project::sender::send_short_msg(std::string msg) {
    int sended;
    char ok;
    if((sended = write(mess_sock, &counter_of_short_msg, 2)) < 0)
        throw "can't send msg";
    counter_of_short_msg++;
    if((sended = send(mess_sock, msg.c_str(), msg.size(), 0)) < 0)
        throw "can't send msg";
    recv(mess_sock, &ok, 1, 0);
}

class synchronized_file_reader {
    private:
        std::string path;
        std::ifstream file;
        int f_length;
        std::mutex mutex_to_read;
    public:
        synchronized_file_reader(const std::string& _path) : path(_path) {
            file.open(path);
            file.seekg(0, file.end);
            f_length = file.tellg();
            file.seekg(0, file.beg);
        }

        int read(int from_position, std::string buff) {
            mutex_to_read.lock();
            file.seekg(from_position);
    //        file.read(buff.c_str, MESS_SIZE);
            mutex_to_read.unlock();
            return f_length - from_position;
        }

        int get_file_lenght() {
            return f_length;
        }
};

void send_peace_of_file(int socket, int start_p, int step, synchronized_file_reader* reader) {
    
}

void project::sender::send_file(std::string path) {
    synchronized_file_reader reader(path);
    int step_for_one_socket = ceil(ceil(reader.get_file_lenght() / MESS_SIZE) / num_sockets);
    synchronized_file_reader* reader_ptr = &reader;
    //std::function<void(int, int, int, synchronized_file_reader&)> peace_sender;
    //peace_sender = send_peace_of_file;
    for(int i = 0; i < num_sockets; i++) {
        int s = sockets[i];
        fut[i] = std::async(std::launch::async, [s, i, step_for_one_socket, reader_ptr](){
                send_peace_of_file(s, i*step_for_one_socket, step_for_one_socket, reader_ptr);
            });
    }
}

/* int sender::(string mesg) {
    sentBytes = ::write(sockfd, mesg.substr(i, mesg.length() - i).c_str(), mesg.length() - i);

    if(sentBytes == -1) {
        cerr << "Error sending IDs: " << errno << "  " << strerror(errno) << endl;
        return 1;
    }
   return 0;
} */
