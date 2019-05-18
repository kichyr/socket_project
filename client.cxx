#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <sys/socket.h>
using namespace std;

//char message[] = "hello there!\n";
//char buf[1024];

int main(int argc, char **argv)
{
    int sock;
    struct sockaddr_in addr, serv;
    char sendline[1024];
    char buff[1024];
    int read_b;
    //char * peername;
    //char buf[100];

    if(argc != 2) {
		printf("Usage: a.out <IP adress>\n");
		exit(1);
	}
	bzero(sendline, 1024);
    sock = socket(AF_INET, SOCK_STREAM, 0);

    //addr.sin_addr.s_addr = htonl(localhost);
	inet_aton(argv[1], &addr.sin_addr);
    serv.sin_family = AF_INET;
    serv.sin_port = htons(52004);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(51000); // или любой другой порт...
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    
    int enable = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(int));
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
 

    if(bind(sock, (struct sockaddr *)&serv, sizeof(serv)) < 0)
    {
        perror("bind");
        close(sock);
        exit(2);
    }



    cout << "kok-----------------------------------" << endl;
    fflush(stdout);
    
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(3);
    }
    cout << "kok-----------------------------------" << endl;
    fflush(stdout);
    shutdown(sock, SHUT_RDWR);
    close(sock);

    //получаем ответ от сервера
    struct sockaddr_in servaddr;
	//структура для адреса сервера
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(52004);
    servaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    //////////////////////////////
    int rcv_sock = socket(AF_INET, SOCK_STREAM, 0);
    
    enable = 1;
    setsockopt(rcv_sock, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(int));
    setsockopt(rcv_sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

    if(bind(rcv_sock, (struct sockaddr *)&serv, sizeof(serv)) < 0)
    {
        perror("bind");
        close(sock);
        exit(2);
    }

    int bytes_read;
    if(listen(rcv_sock, 100) < 0){
		perror("listen");
		close(rcv_sock);
		exit(3);
	}
    char buf[1024];
    while(1)
    {
		socklen_t clilen = sizeof(addr);
        //recvfrom(listener, buff, 1024, 0)
        if((sock = accept(rcv_sock, (struct sockaddr *) &addr, &clilen)) < 0){
			perror("accept");
			//close(addr);
			exit(4);
		}
		//peername = getpeername(listener, (struct sockaddr *) &cliaddr, &clilen
		//char *peername = inet_ntoa(addr.sin_addr);
		//cout << peername << endl;
        while((bytes_read = read(sock, buf, 1023)) > 0){
			printf("%s", buf);
			if(bytes_read < 1023){
				break;
			}
		}
		cout << endl;
		//send_echo(cliaddr.sin_addr.s_addr, cliaddr.sin_port);
        //lose(sock);
		//cout << endl << cliaddr << endl;
        bzero(&buf, bytes_read);
    }
    //recv(rcv_sock, *buf, 1024, 5);
    //recvfrom(rcv_sock, *buf, 5, MSG_WAITALL, (struct sockaddr *)&servaddr, &len);
    //printf("%s", buff);
	/* if(listen(sock, 100) < 0){
		perror("listen");
		close(sock);
		exit(3);
	}
	socklen_t clilen;
	struct sockaddr_in cliaddr;
    clilen = sizeof(cliaddr);
    int listen = socket(AF_INET, SOCK_STREAM, 0);;
	sock = accept(listen, (struct sockaddr *) &cliaddr, &clilen);
	read(sock, buff, 100);
	cout << buff; */
//создаем TCP сокет
	/*int bytes_read;
	socklen_t clilen;
    struct sockaddr_in cliaddr;
    if(listen(sock, 100) < 0){
		perror("listen");
		close(sock);
		exit(3);
	}
    
    while(1)
    {
        if((sock = accept(sock, (struct sockaddr *) &cliaddr, &clilen)) < 0){
		clilen = sizeof(cliaddr);
			perror("accept");
			close(sock);
			exit(4);
		}
		//peername = getpeername(listener, (struct sockaddr *) &cliaddr, &clilen
		peername = inet_ntoa(cliaddr.sin_addr);
		cout << peername << endl;
        while((bytes_read = read(sock, buff, 1023)) > 0){
			printf("%s", buff);
			if(bytes_read < 1023){
				break;
			}
		}
		cout << endl;
        close(sock);
		//cout << endl << cliaddr << endl;
        //bzero(&buf, bytes_read);
    }*/
    return 0;
}
