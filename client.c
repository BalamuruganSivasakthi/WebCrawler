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
#include<sys/stat.h>

char path[50];
char domain[50];


void client(int depth_number,int fileno,char* link,char dir[])
{

  int network_socket;					//to hold info about the socket
  network_socket =socket(AF_INET ,SOCK_STREAM,0);	//0 referring to default TCP protocol

  struct hostent *hos;
  hos = gethostbyname(domain); 			//changing the host domain to ip address
  if (hos == NULL)
  {
  herror("gethostbyname");
  exit(1);
  }
        
  //specying an address for the socket
	
  struct sockaddr_in server_address;
  server_address.sin_family =AF_INET ;
  server_address.sin_port =htons(80);
  server_address.sin_addr = *((struct in_addr *)hos->h_addr);					//assigning the address we got from gethostbyname
  bzero(&(server_address.sin_zero),8); 
	
  int connection;											//to check whether the connection is established or not
  connection=connect(network_socket,(struct sockaddr*) &server_address,sizeof(server_address));
 
  if(connection==-1) 											//if connection is not established
  {
  printf("error");
  }
  static int flag=0;
  char response[512];
  char request[512];
  char server_response [512];
  snprintf(request, sizeof(request), "GET /%s HTTP/1.1\r\nHost: %s\r\n\r\n", path,domain);
  printf("%s",request);
  send(network_socket ,request ,sizeof(request),0);
	
  int data_rec;
  char file_name[]="file";	
  char s[10];
  sprintf(s, "%d",fileno);
  strcat(file_name,s);
  char fol[150];
  sprintf(fol,"%s/%s",dir,file_name);
  printf("\n fol-%s \n",fol);
  
  
  struct stat st={0};
  mkdir(dir,0700);
  mkdir(fol, 0700);     	//to create a folder with dir as name in read,write and execution mode
   	
  char array[200];
  sprintf(array,"%s/%s.txt",fol,file_name);
  printf("\n array  %s \n",array);
  FILE *fp=fopen(array,"wb");
  fputs(link,fp);		//first putting the link of the website at the top of the file
  int data=0;
   
  				//to download source code from a website and to print it in a file

  while( data_rec= recv(network_socket, response, sizeof(response), 0))
  {
  if( data_rec== -1 ) 		//if any error occured during the reception
  {
  perror("receive");
  return;
  }
  data+=data_rec;
  fwrite(response,1,data_rec,fp);
  if(data==-1)
  break;			 //when all the data is received ,data variable will become -1
  }
  printf("\nsource code received completely\n");
  close(network_socket);
  fclose(fp);
}
 	
