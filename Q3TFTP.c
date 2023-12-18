#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h> 

int main(int argc, char* argv[]){
	
// Question 1  
	char* hostname = argv[1];
	//char* filename = argv[2];
	
	struct addrinfo host, *res;
	memset(&host,0,sizeof host);
	
	//Question 2
	host.ai_family = AF_UNSPEC; /* allow the protocol IPv4 or IPv6*/
	host.ai_socktype = SOCK_DGRAM;
	host.ai_flags = AI_PASSIVE;
	host.ai_protocol = 0;
	host.ai_canonname = NULL;
	host.ai_addr = NULL;
	host.ai_next = NULL;
	
	int status = getaddrinfo(hostname ,"1069",&host,&res);
	if(status != 0){
		fprintf(stderr,"getaddrinfo = %s\n", gai_strerror(status));
		}else {
		fprintf(stderr,"getaddrinfo = error\n");
		};
	if((res=NULL)){
		fprintf(stderr,"connexion imposible\n");
	}else{
		fprintf(stderr,"succesful connexion\n");
	};
	
//Question 3 
	int sock = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
	if (sock==-1){
		fprintf(stderr,"error socket's creation\n");
		exit(EXIT_FAILURE);
	};
}
