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
	char* filename = argv[2];
	
	struct addrinfo host, *res;
	memset(&host,0,sizeof host);
	
	//Question 2
	host.ai_family = AF_UNSPEC; //allow the protocol IPv4 or IPv6
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
		fprintf(stderr,"getaddrinfo = ok\n");
		};
	if((res==NULL)){
		fprintf(stderr,"connexion imposible\n");
	}else{
		fprintf(stderr,"succesful connexion\n");
	};
	printf("ok1\n %d %d %d\n",res->ai_family,res->ai_socktype,res->ai_protocol);
//Question 3 
	int sock = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
	printf("ok2\n");
	if (sock==-1){
		fprintf(stderr,"error socket's creation\n");
		exit(EXIT_FAILURE);
	};
//Question 4 
	
	char RRQ[256];
	RRQ[0]=0;
	RRQ[1]=1; 	
	
	printf("ok3\n");	
						
	strcpy(&RRQ[2],filename);					
	RRQ[2+strlen(filename)]=0;						
	strcpy(&RRQ[3+strlen(filename)],"octet");	
	RRQ[8+strlen(filename)]=0;			
	
	printf("ok4\n");	
	int lenght_RRQ= 9+strlen(filename);
	printf("ok5\n");	
	if(!sendto(sock,RRQ,lenght_RRQ,0,res->ai_addr, res->ai_addrlen)){
		fprintf(stderr, "error Read request \n");
	  printf("ok6\n");
	  }
	 char recv[516];
	 
	 int lenght_recv=recvfrom(sock, recv, 516, 0, res->ai_addr,&(res->ai_addrlen));
		
	 fprintf(stderr,"Opcode: %d,%d  Block %d,%d\nData Size: %d\n",recv[0],recv[1],recv[2],recv[3],lenght_recv-4);
	 
	 char ACK[100];
	 ACK[0]=0;ACK[1]=4;
	 
	 int lenght_ACK=4;
	int file =open(filename,O_CREAT|O_WRONLY,0x777);
	write(file,recv+4,lenght_recv-4);
	while(lenght_recv==516){
		ACK[2]=recv[2];ACK[3]=recv[3];		
		
		sendto(sock,ACK,lenght_ACK,0,res->ai_addr, res->ai_addrlen);
		
		lenght_recv=recvfrom(sock, recv, 516, 0,res->ai_addr,&(res->ai_addrlen));
		write(file,recv+4,lenght_recv-4);
		fprintf(stderr,"Opcode: %d,%d  Block %d,%d\nData Size: %d\n",recv[0],recv[1],recv[2],recv[3],lenght_recv-4);
	
	
}
	exit(EXIT_SUCCESS); 

}
