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

void send_echo(unsigned int ip, int port) {
	int sender = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv, servaddr;
    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(53000);

    serv.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if(bind(sender, (struct sockaddr *)&serv, sizeof(serv)) < 0)

	struct sockaddr_in servaddr;
	//структура для адреса сервера
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = (port);
    servaddr.sin_addr.s_addr =  (ip);
    sleep(10);
	
	//connect(sender, (struct sockaddr *)&servaddr, sizeof(servaddr));
    char buff[5] = {'a', 'a', 'a', 'a', 'a'};
	//write(sender, "sosi", 4);
    //sendto(sender, buff, 5, 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
	
    if(connect(sender, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        exit(3);
    }
    write(sender, buff, 5);

	close(sender);
}

int main()
{
    int sock, listener;
    socklen_t clilen;
    struct sockaddr_in servaddr, cliaddr;
    char buf[1024];
    int bytes_read;
    char * peername;
//создаем TCP сокет
    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }
    //структура для адреса сервера
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(51000);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listener, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind");
        close(listener);
        exit(2);
    }
        if(listen(listener, 100) < 0){
		perror("listen");
		close(listener);
		exit(3);
	} 
    char buff[1024];
    while(1)
    {
		clilen = sizeof(cliaddr);
        //recvfrom(listener, buff, 1024, 0)
        if((sock = accept(listener, (struct sockaddr *) &cliaddr, &clilen)) < 0){
			perror("accept");
			close(listener);
			exit(4);
		}
		//peername = getpeername(listener, (struct sockaddr *) &cliaddr, &clilen
		peername = inet_ntoa(cliaddr.sin_addr);
		cout << peername << endl;
        /*while((bytes_read = read(sock, buf, 1023)) > 0){
			printf("%s", buf);
			if(bytes_read < 1023){
				break;
			}
		}*/
		cout << endl;
		send_echo(cliaddr.sin_addr.s_addr, cliaddr.sin_port);
        close(sock);
		//cout << endl << cliaddr << endl;
        bzero(&buf, bytes_read);
    }

	
    
    return 0;
}
