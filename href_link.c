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
#include "client.c"

int depths[11]={0};
extern char domain[];
extern char path[];


void getDomainPath(char* link)
{
  int ch,x=0;
  printf("domain :%s \n path: %s  \n link: %s",domain,path,link);
  int i=0,j=0;
  while((domain[i++]=link[x++])!='/')
  {
  putchar(domain[i]);
  if(domain[i-1]=='\n')
    {
     domain[i-1]='\0';
     path[j]='\0';
     return ;
    }
  }
  domain[i-1]='\0';
  while((path[j++]=link[x++])!='\n');
  path[j-1]='\0';
  printf("\n domain :%s \n path: %s  \n link: %s",domain,path,link);
}	
		
void fn_name(int depthno,int fileno, char * arr,char dir[])
{
	sprintf(arr,"%s/file%d/file%d.txt",dir,fileno,fileno);
}

void getHttpLinks(FILE * ptr,char* link)
{     
  int ch,i=0;
  if((ch=fgetc(ptr))=='h' && (ch=fgetc(ptr))=='t'&& if((ch=fgetc(ptr))=='t'&& (ch=fgetc(ptr))=='p' && (ch=fgetc(ptr))=='s' && (ch=fgetc(ptr))==':' && (ch=fgetc(ptr))=='/' && (ch=fgetc(ptr))=='/')
  {
  while((ch=fgetc(ptr))!='\"')
  {
  link[i++]=ch;
  }
  link[i]='\n';
  link[i+1]='\0';
  getDomainPath(link);
  }  	
}	
 
void dir_name(int depth_number,char dir[])
{
  char arr[10];
  sprintf(arr,"/depth-%d",depth_number);
  strcat(dir,arr);
  printf(" \n %s \n ",dir);
} 
 
void remo(char dir[])
{
  int len;
  len=strlen(dir);
  len--;
  while(dir[len]!='/')
  len--;
  dir[len]='\0';
}
 	
void getLinks(int depth_number,char dir[])
{
  int ch;
  static int flag=0;
  if(depth_number>3 || (depths[depth_number]!=0))
  {
    flag=1;
    return ;
  }
  int fileno=0;
  char arr[200];
  printf(" \n %s \n ",dir);
  fn_name(depth_number,fileno,arr,dir);
  printf(" \n arr- %s \n", arr);
  FILE* ptr=fopen(arr,"r");
	
do
  {
  if((ch=fgetc(ptr))=='a' && (ch=fgetc(ptr))==' '&& if((ch=fgetc(ptr))=='h'&& (ch=fgetc(ptr))=='r' && (ch=fgetc(ptr))=='e' && (ch=fgetc(ptr))=='f' && (ch=fgetc(ptr))=='=' && (ch=fgetc(ptr))=='\')
  {
  char link[100];
  getHttpLinks(ptr,link);	 
  if( !flag)
  dir_name(depth_number,dir);
  client(depth_number+1,fileno,link,dir);
  if(fileno>20)
  {
    depths[depth_number]=fileno;
    remo(dir);
    return ;
  }
  getLinks(depth_number+1,dir);
  printf("filenumber=%d depthnumber-%d \n",fileno,depth_number);
  fileno++;
  } 
 }while(ch!=EOF);
 
}

 
int main(int argc,char* argv[])
{ 
  int depth_number=0;
  char dir[100]="bala";
  strcpy(domain,argv[1]);
  strcpy(path,argv[2]);
  char link[102];
  sprintf(link,"%s/%s\n",domain,path);
  client(depth_number,0,link,dir);
  getLinks(depth_number,dir); 	
}
