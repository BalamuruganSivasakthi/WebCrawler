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

void getLinks(){
FILE* ptr=fopen("html_source_code.txt","r");
FILE* fp=fopen("links.txt","w");
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
 fclose(ptr);
 fclose(fp);
 }
 
 void getHttpLinks()
 {
         FILE* ptr=fopen("links.txt","r");
	 FILE* fp=fopen("http_links.txt","w");
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
 
// fputc(ch,fp);
 fclose(ptr);
 fclose(fp);
 
 
 }

 void getResponse()
 {
 	FILE* ptr=fopen("http_links.txt","r");
 	
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
 		fclose(ptr);
	}		
 			
 
 int main()
 {
 	getLinks();
 	getHttpLinks();
 	getResponse();
 	return 0;
 }
