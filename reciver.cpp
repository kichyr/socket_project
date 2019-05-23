#include "reciver.h"

reciver::reciver(unsigned int port) : stopSock(false) {
    listeningPort = port;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    fut.resize(NUM_THREADS);
    started = false;
}

reciver::~reciver() {
    stop();
}

bool reciver::isAlive() {
	return !stopSock;
}

void reciver::set_in_addr(in_addr_t _in_addr) {
    servaddr.sin_addr.s_addr = htonl(_in_addr);
    in_addr = _in_addr;
}

//запускаем функцию принятия данных в новом потоке
void reciver::accept_data(std::function<void(int sock, reciver* r)> fn) {
    if(started) {
        int newsockfd = accept(sockfd, (struct sockaddr*) &cliaddr, &clilen);
        if(newsockfd == -1)
            throw std::string("can't accept");
        this->run(fn, newsockfd);
    }
}

void reciver::start() {
    if(bind(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0) {
        throw std::string("can't bind");
    }

    listen(sockfd, NUM_THREADS);
    started = true;
    stopSock = false;

    while(!stopSock)
        this->accept_data(recive);
}

int reciver::run(std::function<void(int sock, reciver* r)> fn, int newsocket) {
    static int i = 0;
    fut[i++] = std::async(std::launch::async, [fn, newsocket, this](){
        fn(newsocket, this);
    });
    return 0;
}

//получаем 
void recive(int socket, reciver* r) {
    int bytes_read;// = recv(socket, short_mess[], 1, 0);
    char type_of_mess;

    if((bytes_read = recv(socket, &type_of_mess, 1, 0)) < 1) 
        throw std::string("can't read type of msg");
    else if(type_of_mess == 1) {
        recive_short_mess(socket, r);
    }
    else if(type_of_mess == 0)
        recive_file(socket, r);
    else {
        throw "wrong format of recived msg";
    }
}

void recive_file(int socket, reciver* r){

}

void recive_short_mess(int socket, reciver* r) {
    char msg[MESS_SIZE];
    short num_msg;
    char next = 1;
    while(r->isAlive()) {
    
        int recived = recv(socket, &num_msg, 2, 0);
        if(recived == 0) continue;

        int bytes_read = recv(socket, &msg, MESS_SIZE, 0);
        msg[bytes_read] = '\0';
        r->rcv_short_mess.push_back(msg);
        //std::cout << num_msg << " " << bytes_read << " " << msg << std::endl;
        send(socket, &next, 1, 0);
        //fflush(stdout);
    }
 }

int reciver::stop() {
    stopSock = true;
    int res = close(sockfd);
    return 0;
}