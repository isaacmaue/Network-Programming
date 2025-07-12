//This is the server socket file 
/* To build this socket, we will follow this workflow:
1. Create the cosket
2. Bind the socket to the IP and port 
3. Listen for incoming connections 
4. Accept the incoming connections
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){
	char server_message [256] = "Connected to the server.";	


	int server_socket ;
	server_socket = socket (AF_INET, SOCK_STREAM, 0 );
	
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = inet_addr("192.168.1.52");

	//Bind the socket 
	bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

	//Listen for connections
	listen(server_socket, 1);
	
	
	struct sockaddr_in client_address;
	socklen_t client_len = sizeof(client_address);


	int client_socket;
	client_socket = accept(server_socket,(struct sockaddr *) &client_address, &client_len);

	send(client_socket, server_message, sizeof(server_message), 0);

	close(server_socket);


return 0;
}
