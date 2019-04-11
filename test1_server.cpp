#include"serverSock.h"

void recive(serverSock socket) {
    char buf[1024] = "lol kek cheburek";
    //int bytes_read = recv(socket., buf, 1024, 0);
}

int main() {
    serverSock socket_s(8081);
    socket_s.start();
    socket_s.run()
}