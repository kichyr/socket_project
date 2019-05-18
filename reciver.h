#ifndef RECIVER_H
#define RECIVER_H
#include <iostream>
#include <future>
#include <functional>

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
#include <vector>

#define NUM_THREADS 10
#define MESS_SIZE 4096




class reciver {
	public:
		reciver(unsigned int port);
		~reciver();
		
		//зпринимаем данные, они омеют формат //тип сообщения//номер_сообщения(файл)////
		void accept_data(std::function<void(int sock, reciver* r)> fn);
		
		
		int run(std::function<void(int sock, reciver* r)> fn, int newsocket);
		int stop();

		std::vector<std::string> rcv_short_mess;
		void start();

	protected:
		std::vector<std::future<void>> fut; // массив осинхронных потоков

	private:

		int sockfd; //start server to listen for clients to send them ids
		socklen_t clilen;
		struct sockaddr_in servaddr, cliaddr;
		static const unsigned int buffSize = 1024;
		

		unsigned int listeningPort;
		bool started;
		bool stopSock;

		
};


//0 - короткое сообщение, 1 - файл
	void recive(int socket, reciver* r);
	void recive_short_mess(int socket, reciver* r);
	void recive_file(int socket, reciver* r);
#endif // SERVERSOCK_H