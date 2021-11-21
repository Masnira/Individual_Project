#include <netdb.h> //hostent
#include <stdio.h>
#include <unistd.h> //write
#include <stdlib.h>
#include <arpa/inet.h> //inet_addr
#include <string.h> //strcpy
#include <sys/socket.h>

#define MAX 1024
#define port 42
#define SA struct sockaddr

   //handle error by prompt exit
	#define handle_error_en(en, msg) \
               do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)
	#define handle_error(msg) \
               do { perror(msg); exit(EXIT_FAILURE); } while (0) 
				   
int main(int argc ,int sockfd, char *argv[])
{ 
	int createSocket;
	struct sockaddr_in server;
    char *message, server_reply[2000];       
        
	char buff[1024];
    bzero(buff, 1024);
    int n;
 
	//Create socket
	createSocket = socket(AF_INET , SOCK_STREAM , 0);
	if (createSocket == -1)
	{
  
	printf("[*]Could not create socket!");
	}
	puts("\n[*]Socket successfully created...");
  
  
	server.sin_addr.s_addr = inet_addr("192.168.56.108"); //IP Address of Server 
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	//Connect to server
	if (connect(createSocket , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("\n[*]Connect error!");
		return 1;
	}
	puts("\n[*]Socket connect to server...");
	puts("[*]Connected!");
	puts("\n==Welcome to ARPA Host Name Server Protocol==\n");
 

    //Send some request 
	do
	{
 
        bzero(buff, sizeof(buff));
        printf("\n[*]Enter request:");
        n = 0;
  
	while ((buff[n++] = getchar()) != '\n');
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
       
      
    } 
	while (0);
 

    //Receving reply from server
    if( recv(createSocket, server_reply, 2000, 0)<0)
    {
             
    puts("\n[*]Failed Received!");
    }
  
    puts("\n[*]Reply successfully received!");
    puts(server_reply);
 
	//Advanced Socket Function
    //Resolve Hostname
	char *hostname = "www.shopee.com";
	char ipAdd[100];
	struct hostent *host;
	struct in_addr **addr_list;
	int i;
  
	if ( (host = gethostbyname( hostname ) ) == NULL) 
	{
  
		//gethostbyname failed
		herror("gethostbyname");
		return 1;
	}
	printf("\n[*]Hostname:%s",hostname);
 
	//Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
	addr_list = (struct in_addr **) host->h_addr_list;
 
	for(i = 0; addr_list[i] != NULL; i++) 
	{
  
	strcpy(ipAdd , inet_ntoa(*addr_list[i]) );
	}
 
    printf("\n[*]IP Address: %s \n" ,ipAdd);
    return 0;
 
    //Close the socket
    close(createSocket);
 
}
