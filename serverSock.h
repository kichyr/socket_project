#ifndef SERVERSOCK_H
#define SERVERSOCK_H
#include <iostream>
#include <future>
#include <functional>

#include "clientSock.h"

#include <errno.h>
#include <string.h>

#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netdb.h>
#include <unistd.h>

using namespace std;


class serverSock {
  public:
    serverSock(unsigned int port);
    serverSock();
    ~serverSock();

    void accept_data(std::function<void(int sock)> fn);

    bool inited;

    int init(unsigned int port);//!<Necessary only if not already done by using constructor with port
    int start(std::function<void(int sock)> fn);
    int run(std::function<void(int sock)> fn, int newsocket);
    int stop();

  protected:
    future<void> thr;

  private:
    int enable_keepalive(int sock);

    int sockfd;//start server to listen for clients to send them ids
    socklen_t clilen;
    struct sockaddr_in servaddr, cliaddr;
    static const unsigned int buffSize = 1024;
    char mesg[buffSize];

    unsigned int listeningPort;
    bool started;
    bool stopSock;

};

#endif // SERVERSOCK_H