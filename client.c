#include<stdio.h>
#include <stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<string.h>
#include <unistd.h>
int main(){
	//1,socket
	int c_fd;
	c_fd = socket(AF_INET,SOCK_STREAM,0);
	if(c_fd == -1){
		perror("socket");
		exit(-1);
	}

	//2,connect
	struct sockaddr_in c_addr;
	memset(&c_addr,0,sizeof(struct sockaddr_in));

	c_addr.sin_family = AF_INET;
	c_addr.sin_port = htons(8989);
	inet_aton("192.168.153.130",&c_addr.sin_addr);

	connect(c_fd,(struct sockaddr *)&c_addr,sizeof(struct sockaddr_in));

	//3,write
	char *msg = "msg from client";
	write(c_fd,msg,strlen(msg));

	//4,read
	char readBuf[128];
	int n_read = read(c_fd,readBuf,128);
	if(n_read == -1){
		perror("read");
	}else{
		printf("get message:%d,%s\n",n_read,readBuf);
	}

	return 0;
}
