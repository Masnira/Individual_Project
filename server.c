#include<stdio.h> //printf
#include<string.h> //strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h> //write 

#define port 42

	//handle error by prompt exit
	#define handle_error_en(en, msg) \
               do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)
	#define handle_error(msg) \
               do { perror(msg); exit(EXIT_FAILURE); } while (0) 

int main(int argc , char *argv[])
{
	int createSocket , new_socket , cli;
	struct sockaddr_in server , client;
    char *message; //accept
	
	//Create socket
	createSocket = socket(AF_INET , SOCK_STREAM , 0);
	if (createSocket == -1)
	{
		printf("[*]Could not create socket!\n");
	}

		puts("\n[*]Socket created success\n");
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( port );
	
	//Bind
	if( bind(createSocket,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("[*]Bind failed!\n");
	}
		printf("[*]Bind done at port: %d\n", port);
	
	//Listen
	listen(createSocket , 3);
	
    //Client incoming connection
	puts("\n[*]Waiting for incoming connections...\n");
	
	//Client connected or not
	cli = sizeof(struct sockaddr_in);
	while( (new_socket = accept(createSocket, (struct sockaddr *)&client, (socklen_t*)&cli)) )
	{
		puts("[*]Connection Accepted..\n");
		
	//Reply to the client
		message = "[*]From Server:\nHello Client!\nRequest for hostname : www.shopee.com is successful!\n";
		write(new_socket , message , strlen(message));

	}
	

	if (new_socket<0)
	{
		perror("[*]Accept failed!\n");
		return 1;
	}
	
	//Close the socket
	close(createSocket);
	return 0;
}
