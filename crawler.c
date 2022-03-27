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
#include "Indepth_crawler.c"

int depths[11]={0};
extern char domain[];
extern char path[];
int depth_no,file_no;


void getDomainPath(char* link)	  //to separte domain and path from the link
{
  int ch,x=0;
  int i=0,j=0;
  while((domain[i++]=link[x++])!='/')   //extracting domain from the link
  {
  putchar(domain[i]);
  if(domain[i-1]=='\n')		 //if the path is not available ,it will assign the path to be '\0'
    {
     domain[i-1]='\0';
     path[j]='\0';	
     return ;
    }
  }
  domain[i-1]='\0';
  while((path[j++]=link[x++])!='\n');  //extracting path from the link
  path[j-1]='\0';
}	

		
//to assign the file name  with the exact depth number and file number		
void fileName(int depthno,int fileno, char * arr,char dir[]) 
{
  sprintf(arr,"%s/file%d.txt",dir,fileno);
}


//function to check whether we are gwtting 'https' after 'a href' or not
int getHttpLinks(FILE * ptr,char* link,FILE* URLS) 
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
 
 
//function to change the directory name ,while backtracking
void removeLastDepth(char dir[]) 
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
  if(depth_number>depth_no-1 || (depths[depth_number]!=0))
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
  int len=strlen(link);
 	 
  if( !flag)
  directoryName(depth_number,dir);
  client(depth_number+1,fileno,link,dir,domain,path);
  if(fileno>file_no-1)
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
  FILE *URLS=fopen("bala/Urls.txt","w");  //to print all the website URLs crawled 
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
  
  char main_folder[100]="bala";		//initializing the folder name to "bala" to get into that folder
  
  printf("Enter upto which depth you want to crawl");
  scanf("%d",&depth_no);
  printf("Enter how many files you want to crawl from each depth");
  scanf("%d",&file_no);
  
  for(int i=0;i<depth_no;i++) 	 //for depth_number
  {
    char folder_name[10];
    char previous_link[100];
    sprintf(folder_name,"/depth-%d",i);
    strcat(main_folder,folder_name);
    
    for(int j=1;j<=file_no;j++)	//for file number
    {
     char pre_file_name[100];
     sprintf(pre_file_name,"depth-%d_file-%d",i,j);
     
     char file_name[200];
     sprintf(file_name,"%s/file%d.txt",main_folder,j);
     FILE* fp=fopen(file_name,"r");
     int k=0;
     while((previous_link[k++]=fgetc(fp))!='\n');
     previous_link[k]='\0';
     getUrls(fp,main_folder,pre_file_name,previous_link,URLS);
     fclose(fp);
    }
   }  	
}

