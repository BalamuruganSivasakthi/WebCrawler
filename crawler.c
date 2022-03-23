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
#include "domain.c"

int depths[11]={0};
extern char domain[];
extern char path[];



void getDomainPath(char* link)	 //to separte domain and path from the link
{
  int ch,x=0;
  int i=0,j=0;
  while((domain[i++]=link[x++])!='/')
  {
  putchar(domain[i]);
  if(domain[i-1]=='\n')		//if the path is not available ,it will assign the path to be '\0'
    {
     domain[i-1]='\0';
     path[j]='\0';	
     return ;
    }
  }
  domain[i-1]='\0';
  while((path[j++]=link[x++])!='\n');
  path[j-1]='\0';
}	

		
void fileName(int depthno,int fileno, char * arr,char dir[]) //to assign the file name  with the exact depth number and file number
{
  sprintf(arr,"%s/file%d.txt",dir,fileno);
}


int getHttpLinks(FILE * ptr,char* link,FILE* URLS) //this function is to check whether we are gwtting 'https' after 'a href' or not
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
  printf(" \n %s \n ",link);
  getDomainPath(link);
  }  	
}	
 
 
void directoryName(int depth_number,char dir[])  //to assign the folder name 
{
  char arr[10];
  sprintf(arr,"/depth-%d",depth_number);
  strcat(dir,arr);
} 
 
 
void removeLastDepth(char dir[]) //while backtracking we have to remove the depth10 depth9 depth8 so on to get proper depth
{
  int len;
  len=strlen(dir);
  len--;
  while(dir[len]!='/')
  len--;
  dir[len]='\0';
}
 	
 	
void getLinks(int depth_number,char dir[],FILE * URLS)  //recursive function used to crawl until a given depth number
{
  int ch;
  static int flag=0;
  if(depth_number>1 || (depths[depth_number]!=0))
  {
    flag=1;
    return ;
  }
  int fileno=0;
  char arr[200];
  fileName(depth_number,fileno,arr,dir);
  FILE* ptr=fopen(arr,"r");
	
do
  {
  if((ch=fgetc(ptr))=='a' && (ch=fgetc(ptr))==' '&& (ch=fgetc(ptr))=='h'&& (ch=fgetc(ptr))=='r' && (ch=fgetc(ptr))=='e' && (ch=fgetc(ptr))=='f' && (ch=fgetc(ptr))=='=' && (ch=fgetc(ptr))=='\"')
  {
  char link[100];
  int check;
  check=getHttpLinks(ptr,link,URLS);

 // char* domain,*path;
  int len=strlen(link);
 	 
  if( !flag)
  directoryName(depth_number,dir);
  client(depth_number+1,fileno,link,dir,domain,path);
  if(fileno>20)
  {
    depths[depth_number]=fileno;
    removeLastDepth(dir);
    return ;
  }
  getLinks(depth_number+1,dir,URLS);
  fileno++;
  } 
 }while(ch!=EOF);
}


int main(int argc,char* argv[])
{ 
  FILE *URLS=fopen("Urls.txt","w");  //to print all the website URLs crawled 
  int depth_number=0;
  char domain[100];
  char path[100];
  strcpy(domain,argv[1]);
  strcpy(path,argv[2]);
  char dir[100]="bala";
  char link[202];
  sprintf(link,"%s/%s\n",domain,path);
  fputs(link,URLS);
  client(depth_number,0,link,dir,domain,path); //for the first website alone , will call the client from main itself
  getLinks(depth_number,dir,URLS); 
  
  //for crawling through more  websites from the same depth files
  
  char ab[100]="bala";
  for(int i=0;i<2;i++)
  {
    char mn[10];
    char previous_link[100];
    sprintf(mn,"/depth-%d",i);
    strcat(ab,mn);
    for(int j=1;j<=21;j++)
    {
     char bc[100];
     sprintf(bc,"depth-%d_file-%d",i,j);
     
     char xy[200];
     sprintf(xy,"%s/file%d.txt",ab,j);
     FILE* fp=fopen(xy,"r");
     int k=0;
     while((previous_link[k++]=fgetc(fp))!='\n');
     previous_link[k]='\0';
     getUrls(fp,ab,bc,previous_link,URLS);
     fclose(fp);
    }
   }  	
}


