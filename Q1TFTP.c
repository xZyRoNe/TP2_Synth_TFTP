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
}
