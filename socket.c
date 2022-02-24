	//to create a simple socket and to check its working
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>

#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>

int main(int argc,char* argv[])
{
	char* address;
	address=argv[1];
	//creating a socket
	int network_socket;//to hold info about the socket
	network_socket =socket(AF_INET ,SOCK_STREAM,0);//0 referring to default TCP protocol

	//specying an address for the socket
	struct sockaddr_in server_address;
	server_address.sin_family =AF_INET ;
	server_address.sin_port =htons(80);
	inet_aton(address,&server_address.sin_addr.s_addr);//sin_address itsekf is a structure

	int connection;//to check whether the connection is established or not

	connection=connect(network_socket,(struct sockaddr*) &server_address,sizeof(server_address));
	if(connection==-1)
	{
		printf("error");
	}


	char server_response [512];
	char request[]="GET / HTTP/1.1\r\n\r\n";
	send(network_socket ,request ,sizeof(request),0);
	recv(network_socket,&server_response ,sizeof(server_response),0);

	printf("server response:%s\n",server_response);
	close(network_socket);

	return 0;


	}
