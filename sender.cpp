#include "sender.h"

void project1::sender::init(bool _is_msg_socket, int _num_sockets) {
    is_msg_socket = _is_msg_socket;
    num_sockets = _num_sockets;
    sockets.resize(num_sockets);
    fut.resize(num_sockets);
}

project1::sender::~sender() {
    disconnect_all();
}

void project1::sender::connect_all(std::string _host, int _reciver_port) {
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
        write(sockets[i], &i, 4);
    }
}

void project1::sender::connect(int *sockfd, int port) {
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



void project1::sender::disconnect_all() {
    for(auto socket : sockets)
        disconnect(socket);
    if(is_msg_socket)
        disconnect(mess_sock);
}

void project1::sender::disconnect(int sockfd) {
    close(sockfd);
}

void project1::sender::send_short_msg(std::string msg) {
    int sended;
    char ok;
    if((sended = write(mess_sock, &counter_of_short_msg, 2)) < 0)
        throw "can't send msg";
    counter_of_short_msg++;
    if((sended = send(mess_sock, msg.c_str(), msg.size(), 0)) < 0)
        throw "can't send msg";
    recv(mess_sock, &ok, 1, 0);
}


void send_piece_of_file(int socket, int start_p, int step, project1::synchronized_file_reader* reader, int* sending_file_flag_ptr) {
    char s[MESS_SIZE];
    int readen_bytes;
    int p;
    char ok; //response of getting
    std::cout << '(' << start_p << ' ' << start_p + (step)  << std::endl;
    std::cout << (*reader).get_file_lenght() << std::endl;
    for(p = start_p; p <= std::min(start_p + (step), reader->get_file_lenght() + (step));p += MESS_SIZE) {
        readen_bytes = (*reader).read(p, s);
        std::cout << ".///" << readen_bytes << "////" <<std::endl;
        if(readen_bytes <= 0) break;
        fflush(stdout);
        send(socket, &p, 4, 0);
        send(socket, s, readen_bytes, 0);
        recv(socket, &ok, 1, 0);
    }
    p = -1;
    send(socket, &p, 4, 0);
    *sending_file_flag_ptr--;
}

void project1::sender::send_file(char* path) {
    if(sending_file_flag != 0)
        throw "another file sending";
    char ok;
    sending_file_flag = num_sockets;
    reader.init(path);
    //sending name_of_file

    send(sockets[0], path, strlen(path), 0);
    recv(sockets[0], &ok, 1, 0);
    //

    int step_for_one_socket = int(int(reader.get_file_lenght() / MESS_SIZE + 1) / num_sockets + 1);
    synchronized_file_reader* reader_ptr = &reader;
    int* sending_file_flag_ptr = &sending_file_flag;
    std::cout << step_for_one_socket << std::endl;
    for(int i = 0; i < num_sockets; i++) {
        int s = sockets[i];
        fut[i] = std::async(std::launch::async, [s, i, step_for_one_socket, reader_ptr, sending_file_flag_ptr](){
                send_piece_of_file(s, MESS_SIZE*i*step_for_one_socket+i, MESS_SIZE*step_for_one_socket, reader_ptr, sending_file_flag_ptr);
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
