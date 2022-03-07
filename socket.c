	
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<netdb.h>

int a;
int ReadHttpStatus(int sock){
    char c;
    char buff[1024]="",*ptr=buff+1;
    int bytes_received, status;
    printf("Begin Response ..\n");
    while(bytes_received = recv(sock, ptr, 1, 0)){
        if(bytes_received==-1){
            perror("ReadHttpStatus");
            exit(1);
        }
	a+=bytes_received;
        if((ptr[-1]=='\r')  && (*ptr=='\n' )) break;
        ptr++;
    }
    *ptr=0;
    ptr=buff+1;

    sscanf(ptr,"%*s %d ", &status);

    printf("%s\n",ptr);
    printf("status=%d\n",status);
    printf("End Response ..\n");
    return (bytes_received>0)?status:0;

}

int ParseHeader(int sock){
    char c;
    char buff[1024]="",*ptr=buff+4;
    int bytes_received, status;
   
    printf("Begin HEADER ..\n");
    while(bytes_received = recv(sock, ptr, 1, 0)){
        if(bytes_received==-1){
        	
            perror("Parse Header");
            exit(1);
        }
	a+=bytes_received;
	
        if(
            (ptr[-3]=='\r')  && (ptr[-2]=='\n' ) &&
            (ptr[-1]=='\r')  && (*ptr=='\n' )
        ) break;
        ptr++;
    }

    *ptr=0;
    ptr=buff+4;

    if(bytes_received){
        ptr=strstr(ptr,"Content-Length:");
        if(ptr){
            sscanf(ptr,"%*s %d",&bytes_received);

        }else
            bytes_received=-1; //unknown size

       printf("Content-Length: %d\n",bytes_received);
    }
    printf("End HEADER ..\n");
    return  bytes_received;

}

int depth_1()
{

	//tried for the tutorialspoint website
	char path[]="\0";
	char domain[]="www.gnu.org";
	char* address;
	//address=argv[1];//as arg[0] would be ./socket
	//creating a socket
	int network_socket;//to hold info about the socket
	network_socket =socket(AF_INET ,SOCK_STREAM,0);//0 referring to default TCP protocol

	struct hostent *hos;
	hos = gethostbyname(domain); //changing the host domain to ip address
	if (hos == NULL){
       herror("gethostbyname");
       exit(1);
        }
        
	//specying an address for the socket
	struct sockaddr_in server_address;
	server_address.sin_family =AF_INET ;
	server_address.sin_port =htons(80);
	server_address.sin_addr = *((struct in_addr *)hos->h_addr);
        bzero(&(server_address.sin_zero),8); 
	
	
	int connection;//to check whether the connection is established or not

	connection=connect(network_socket,(struct sockaddr*) &server_address,sizeof(server_address));
	if(connection==-1)
	{
		printf("error");
	}

	char response[512];
	char request[512];
	char server_response [512];
	snprintf(request, sizeof(request), "GET /%s HTTP/1.1\r\nHost: %s\r\n\r\n", path,domain);
        printf("%s",request);
	send(network_socket ,request ,sizeof(request),0);
	
	int data_rec;
    	FILE *fp=fopen("html_source_code.txt","wb");
    	
   
   	int data=0;
   

       //to download source code from a website and to print it in a file

       int contentlengh;
       int bytes_received;
       char recv_data[1024];
       if(ReadHttpStatus(network_socket) && (contentlengh=ParseHeader(network_socket))){

        int bytes=-(a+2);
        FILE* fd=fopen("html_source_code.txt","wb");
        printf("Saving data...\n\n");

        while(bytes_received = recv(network_socket, recv_data, 1024, 0)){
            if(bytes_received==-1){
                perror("recieve");
                exit(3);
            }


            fwrite(recv_data,1,bytes_received,fd);
            bytes+=bytes_received;
            printf("Bytes recieved: %d from %d\n",bytes,contentlengh);
            if(bytes==contentlengh)
            break;
            
        }
        fclose(fd);
        close(network_socket);
        fclose(fp);
       return 0;
}
}
