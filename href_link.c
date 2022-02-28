#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void fn1(){
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
	 }}}}}}}}}
	
	 
 }while(ch!=EOF);
 
 fputc(ch,fp);
 fclose(ptr);
 fclose(fp);
 }
 
 void fn2()
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
 
 fputc(ch,fp);
 fclose(ptr);
 fclose(fp);
  
 
 
 }
 int main()
 {
 	fn1();
 	fn2();
 	return 0;
 }
