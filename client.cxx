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
    serv.sin_port = htons(52002);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(51000); // или любой другой порт...
    serv.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if(bind(sock, (struct sockaddr *)&serv, sizeof(serv)) < 0)
    {
        perror("bind");
        close(sock);
        exit(2);
    }
    
    
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(3);
    }
    printf("Message => ");
    while((read_b = read(1, sendline, 1023)) > 0){
		send(sock, sendline, read_b, 0);
		if(read_b < 1023){
			break;
		}
	}
	if(listen(sock, 100) < 0){
		perror("listen");
		close(sock);
		exit(3);
	}
	socklen_t clilen;
	struct sockaddr_in cliaddr;
	sock = accept(sock, (struct sockaddr *) &cliaddr, &clilen);
	read(sock, buff, 100);
	cout << buff;
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
		clilen = sizeof(cliaddr);
        if((sock = accept(sock, (struct sockaddr *) &cliaddr, &clilen)) < 0){
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
