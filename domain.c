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

char ndomain[100];
char npath[100];

void getSourceCode(char narr[],int fileno,char previous_link[],char link[])
{
  
  int network_socket;					//to hold info about the socket
  network_socket =socket(AF_INET ,SOCK_STREAM,0);	//0 referring to default TCP protocol
  printf(" \n domain- %s path -%s",ndomain,npath); 
  struct hostent *hos;
  hos = gethostbyname(ndomain); 			//changing the host domain to ip address
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
  snprintf(request, sizeof(request), "GET /%s HTTP/1.1\r\nHost: %s\r\n\r\n", npath,ndomain);
  printf("%s",request);
  send(network_socket ,request ,sizeof(request),0);
	
  int data_rec;
  char file_name[]="file";	
  char s[10];
  sprintf(s, "%d",fileno);
  strcat(file_name,s);
 	
  char array[200];
  sprintf(array,"%s/%s.txt",narr,file_name);
  FILE *fp=fopen(array,"wb");
  fputs(previous_link,fp);
  fputs(link,fp);
  int data=0;
   
  //to download source code from a website and to print it in a file

  while( data_rec= recv(network_socket, response, sizeof(response), 0))
  {
  if( data_rec== -1 ) 			 //if any error occured during the reception
  {
  perror("receive");
  return;
  }
  data+=data_rec;
  fwrite(response,1,data_rec,fp);
  if(data==-1)
  break;				 //when all the data is received ,data variable will become -1
  }
  printf("\nsource code received completely\n");
  close(network_socket);
  fclose(fp);
}


void getUrlsDomainPath(char* link) 					//same as getDomainPath with variables only changing
{
  int ch,x=0;
  int i=0,j=0;
  while((ndomain[i++]=link[x++])!='/')
  {
  putchar(ndomain[i]);
  if(ndomain[i-1]=='\n')
    {
     ndomain[i-1]='\0';
     npath[j]='\0';
     return ;
    }
  }
  ndomain[i-1]='\0';
  while((npath[j++]=link[x++])!='\n');
  npath[j-1]='\0';
}


int gethttpUrls(FILE * ptr,char* link,FILE* URLS)			//same as getHttpLinks (to identify and separate https://)
{     
  int ch,i=0;
  if((ch=fgetc(ptr))=='h' && (ch=fgetc(ptr))=='t'&& (ch=fgetc(ptr))=='t'&& (ch=fgetc(ptr))=='p' && (ch=fgetc(ptr))=='s' && (ch=fgetc(ptr))==':' && (ch=fgetc(ptr))=='/' && (ch=fgetc(ptr))=='/')
  {
  while((ch=fgetc(ptr))!='\"')
  {
  link[i++]=ch;
  }
  link[i]='\n';
  link[i+1]='\0';
  fputs(link,URLS);
  }  
  if(i==0)
  return 0;
  getUrlsDomainPath(link);	
  return 1;
}


void getUrls(FILE* ptr,char ab[],char bc[],char previous_link[],FILE* URLS) 		//same as getLinks but without being recursion
{
  int ch;
  int i=0,count=0;
  char narr[100];
  sprintf(narr,"%s/%s",ab,bc);
  mkdir(narr, 0700); 
	
do
  {
  
  if((ch=fgetc(ptr))=='a' && (ch=fgetc(ptr))==' '&& (ch=fgetc(ptr))=='h'&& (ch=fgetc(ptr))=='r' && (ch=fgetc(ptr))=='e' && (ch=fgetc(ptr))=='f' && (ch=fgetc(ptr))=='=' && (ch=fgetc(ptr))=='\"')
  {
  count++;
  char link[100];
  if(count>=20)
  return;
  if(gethttpUrls(ptr,link,URLS))	 
  getSourceCode(narr,i,previous_link,link);
  i++;
  } 
 }while(ch!=EOF);
}





