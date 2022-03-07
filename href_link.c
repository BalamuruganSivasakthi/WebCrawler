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
#include "socket.c"

void getLinks(FILE * fp,FILE * ptr){

int ch;

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
		 
	while((ch=fgetc(ptr))!='\"')
	{
	 	fputc(ch,fp);
	 
	 }
	 
	 
	 
	 if(ch=='\"')
	 	fputc('\n',fp);
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
 
 fputc(ch,fp);

 }
 
 void getHttpLinks(FILE * fp,FILE * ptr)
 {
        
	 int ch;

 do{
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
	
		 
	while((ch=fgetc(ptr))!='\n')
	{
	 	fputc(ch,fp);
	 	
	 }
	 
	 fputc('\n',fp);
	 }}}}}}}}
	
	 
 }while(ch!=EOF);
 


 
 
 }

 void getResponse(FILE * ptr)
 {
 	
 	
 	int ch;
 	char path[50];
 	char domain[50];
 	
 	 while((ch=fgetc(ptr))!=EOF)
 	{
 	  int i=0,j=0;
 	   while(ch!='/' && ch!='\n' && ch!=' ')
 	   {
 	   domain[i++]=ch;
 	   ch=fgetc(ptr);
 	   }
 	   if(ch!='/')
 	   continue;
 	   domain[i]='\0';
 	   if(ch!='\n' || ch!=' ')
 	   while((ch=fgetc(ptr))!='\n')
 	   {
 	   path[j++]=ch;
 	   }
 	   path[j]='\0';
 	  
 	   
 	   client(domain,path);
 	   }
 		
	}	
		
 int nooflines(FILE* fp) 
 {
 	int len=0;
	int ch;
	 while((ch=fgetc(fp))!=EOF)
 	{
 	  int i=0,j=0;
 	   while(ch!='/' && ch!='\n' && ch!=' ')
 	   {
 	   
 	   ch=fgetc(fp);
 	   }
 	   if(ch!='/')
 	   continue;
 		len++;
 	   if(ch!='\n' || ch!=' ')
 	   while((ch=fgetc(fp))!='\n');
 	   }	
	
	return len;
}		
 
 int main()
 {
 	 depth_1();
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
		
    		FILE *fptr=fopen(file_name,"r");
    		printf("%s \n",file_name);
    		getLinks(p,fptr);
    		fclose(p);
    		FILE* pr=fopen("depth_2_links.txt","r");
    		getHttpLinks(filep,pr);	
    		fclose(fptr);
    		fclose(pr);
    	}
    	fclose(filep);
    	
 	fclose(fp);
 	return 0;
 }
