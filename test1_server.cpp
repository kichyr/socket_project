#include"serverSock.h"

void recive(int socket) {
    //char buf[1024] = "lol kek cheburek";
    char buff[1024];
    int bytes_read = recv(socket, buff, 1024, 0);
    cout << buff;
    flush(std::cout);
    sleep(5);
    cout << "dead";
    flush(std::cout);
}

int main() {
    serverSock socket_s(8081);
    socket_s.start(recive);
}