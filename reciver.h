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
#include <fstream>
#include <mutex>

//TO FIX
#define NUM_THREADS 40
#define MESS_SIZE 4096

class synchronized_file_writer {
    private:
        std::string path;
        std::ofstream file;
        int f_length;
        std::mutex mutex_to_write;
    public:
        void init_new_file(const std::string& name) {
			file.close();
            path = name+"(recived)";
            file.open(path);
            //file.seekp(0, file.end);
            //f_length = file.tellg();
            file.seekp(0, file.beg);
        }

        void write(int from_position, char* buff, int bytes_to_write) {
            mutex_to_write.lock();
            file.seekp(from_position, file.beg);
            file.write(buff, bytes_to_write);
            file.seekp(0);
            mutex_to_write.unlock();
        }
		~synchronized_file_writer() {
			file.close();
		}
}; 

class reciver {
	public:
		

		void init(unsigned int port);
		~reciver();
		
		//Возврвщвет true, если сервер работает
		bool isAlive();
		
		//зпринимаем данные, они омеют формат //тип сообщения//номер_сообщения(файл)////
		void accept_data(std::function<void(int sock, reciver* r)> fn);
		
		
		int run(std::function<void(int sock, reciver* r)> fn, int newsocket);
		int stop();

		std::vector<std::string> rcv_short_mess;
		void start();


		void set_in_addr(in_addr_t _in_addr);

	protected:
		std::vector<std::future<void>> fut; // массив осинхронных потоков

	private:
		synchronized_file_writer writer;
		int reciving_file_flag = 0;
		int sockfd; //start server to listen for clients to send them ids
		socklen_t clilen;
		struct sockaddr_in servaddr, cliaddr;
		static const unsigned int buffSize = 1024;
		in_addr_t in_addr = INADDR_ANY;

		unsigned int listeningPort;
		bool started;
		bool stopSock;	
		std::mutex mutex_to_recive_file;

		//0 - короткое сообщение, 1 - файл
		friend void recive_short_mess(int socket, reciver* r);
		friend void recive_file(int socket, reciver* r);
};
void recive(int socket, reciver* r);


#endif // RECIVER_H