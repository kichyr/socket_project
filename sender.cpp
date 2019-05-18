#include "sender.h"

sender::sender(std::string _host, std::vector<int> _reciver_ports) {
    host = _host;
    reciver_ports = _reciver_ports;
    sockets.resize(reciver_ports.size());
}

sender::~sender() {
    disconnect_all();
}

void sender::connect_all() {
    for(int i = 0; i < reciver_ports.size(); i++)
        connect(&sockets[i], reciver_ports[i]);
}

void sender::connect(int *sockfd, int port) {
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

void sender::disconnect_all() {
    for(auto socket : sockets)
        disconnect(socket);
}

void sender::disconnect(int sockfd) {
    close(sockfd);
}

void sender::send_short_msg(std::string msg) {
    int sended;
    char type_msg = '0';
    if((sended = write(sockets[0], &type_msg, 1)) < 0)
        throw "can't send msg";
    if((sended = write(sockets[0], msg.c_str(), msg.size())) < 0)
        throw "can't send msg";
}

/* int sender::(string mesg) {
    sentBytes = ::write(sockfd, mesg.substr(i, mesg.length() - i).c_str(), mesg.length() - i);

    if(sentBytes == -1) {
        cerr << "Error sending IDs: " << errno << "  " << strerror(errno) << endl;
        return 1;
    }
   return 0;
} */
