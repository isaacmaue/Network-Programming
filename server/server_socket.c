//This is the server socket file 
/* To build this socket, we will follow this workflow:
1. Create the cosket
2. Bind the socket to the IP and port 
3. Listen for incoming connections from a client
4. Accept the incoming connections
5. Send data 
6. close the socket
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){
	//Message to send to the client upon successful connection
	char server_message [256] = "Connected to the server.";	

	//The main server socket
	int server_socket ;
	//Assign socket type to server socket. We are using IPV4 , TCP, and 0 for protocol spec
	server_socket = socket (AF_INET, SOCK_STREAM, 0 );

	
	//Fill out server struct sockaddr_in. Famil, port, and IP
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = inet_addr("192.168.1.52");
	


	//Bind the socket 
	int bind_result = bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	if (bind_result == 0){
		printf("Binding was successful\n");
		}else{
		printf("Binding failed\n.");
	}


	//Listen for connections
	int listen_result = listen(server_socket, 1);
	if(listen_result == 0){
	printf("Listen successful\n.");
	}else{
		printf("Listen failed\n.");
	}
	
	
	struct sockaddr_in client_address;
	socklen_t client_len = sizeof(client_address);


	int client_socket;
	client_socket = accept(server_socket,(struct sockaddr *) &client_address, &client_len);

	send(client_socket, server_message, sizeof(server_message), 0);

	close(server_socket);


return 0;
}
