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





 void getResponse(char* link)
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
	sprintf(arr,"%s/file%d.txt",dir,fileno);
}

		


void getHttpLinks(FILE * ptr,char* link)
 {
        
	 int ch,i=0;
	


	ch=fgetc(ptr);
	if(ch=='h')
	{
	 if((ch=fgetc(ptr))=='t')
	 {
	  if((ch=fgetc(ptr))=='t')
	  {
	   if((ch=fgetc(ptr))=='p')
	   {
	    if((ch=fgetc(ptr))=='s')
	    {
	     if((ch=fgetc(ptr))==':')
	     {
	      if((ch=fgetc(ptr))=='/')
	      {
		if((ch=fgetc(ptr))=='/')
		{
	
		 
	while((ch=fgetc(ptr))!='\"')
	{
	 	link[i++]=ch;
	 	
	 }
	 
	 link[i]='\n';
	 link[i+1]='\0';
	 getResponse(link);
	 }}}}}}}}
	
 }	
 
 void dir_name(int depth_number,char dir[])
 {
 	char arr[10];
 	//if(depth_number==1)
 	sprintf(arr,"/depth-%d",depth_number);
 	//else
 	//sprintf(arr,"depth-%d",depth_number);
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
 	
 
 void getLinks(int depth_number,char dir[]){

	
	int ch;
	static int flag=0;
	if(depth_number>10 || (depths[depth_number]!=0))
	{
		flag=1;
		return ;
	}
	int fileno=0;
	char arr[200];

	printf(" \n %s \n ",dir);
	fn_name(depth_number,fileno,arr,dir);
	printf(" \n %s \n", arr);
	FILE* ptr=fopen(arr,"r");
	

 do{
	ch=fgetc(ptr);
	if(ch=='<')
	{
	 if((ch=fgetc(ptr))=='a')
	 {
	  if((ch=fgetc(ptr))==' ')
	  {
	   if((ch=fgetc(ptr))=='h')
	   {
	    if((ch=fgetc(ptr))=='r')
	    {
	     if((ch=fgetc(ptr))=='e')
	     {
	      if((ch=fgetc(ptr))=='f')
	      {
		if((ch=fgetc(ptr))=='=')
		{
		 if((ch=fgetc(ptr))=='\"') 
		 {    	
		 
	
	
	 char link[100];
	 getHttpLinks(ptr,link);
	 
	 
	if( !flag)
	dir_name(depth_number,dir);
	 client(depth_number+1,fileno,link,dir);
	 if(fileno>20 )
	 {
	 	depths[depth_number]=fileno;
	 	remo(dir);
	 	return ;
	 }
	 getLinks(depth_number+1,dir);
	 printf("filenumber=%d depthnumber-%d \n",fileno,depth_number);
	 fileno++;
	 
	 
	
	        }
	       }
              }
             }
            }
           }
          }
         }
        }
	
	 
 }while(ch!=EOF);
 
 
 }
 
 
 int main(int argc,char* argv[])
 {
 
 	int depth_number=0;
        char dir[100]="bala/";
 	strcpy(domain,argv[1]);
 	strcpy(path,argv[2]);
 	char link[102];
 	sprintf(link,"%s/%s\n",domain,path);
	client(depth_number,0,link,dir);
	getLinks(depth_number,dir);
 	
 	/* depth_1();
 	 FILE* ptr=fopen("html_source_code.txt","r");
	 FILE* fp=fopen("links.txt","w");
 	getLinks(fp,ptr);
 	fclose(fp);
 	fclose(ptr);
 	ptr=fopen("links.txt","r");
 	fp=fopen("http_links.txt","w");
 	getHttpLinks(fp,ptr);
 	fclose(fp);
 	fp=fopen("http_links.txt","r");
 	getResponse(fp);
 	fclose(fp);
 	 fclose(ptr);
 	fp=fopen("http_links.txt","r");
 	
 	int nooffiles=nooflines(fp);
 	printf("%d",nooffiles);
 	
 	FILE *filep=fopen("depth_2_http_links.txt","w");
 	for(int i=1;i<=nooffiles;i++)
 	{
 		FILE* p=fopen("depth_2_links.txt","w");
 		
 		char file_name[]="file";
		
		char s[10];
		sprintf(s, "%d",i);
		strcat(file_name,s);
		char charr[40];
		sprintf(charr,"bala/%s/%s.txt",file_name,file_name);
    		FILE *fptr=fopen(charr,"r");
    		getLinks(p,fptr);
    		fclose(p);
    		FILE* pr=fopen("depth_2_links.txt","r");
    		getHttpLinks(filep,pr);	
    		fclose(fptr);
    		fclose(pr);
    	}
    	fclose(filep);
    	
 	fclose(fp);
 	return 0;*/
 }
