//This is the client TCP socket that connects to the Ubuntu server in my NM

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


#include <netinet/in.h>

int main(){
    //Create the network socket that will hold the int file descriptor. We can use this for other socket usage.
    int networkSocket;

    //Call the socket() and assign the retuerned int to our socket var. 
    networkSocket = socket(AF_INET, SOCK_STREAM, 0);

    //Specifying an address to connect to (server)
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = inet_addr("192.168.1.52");

    int connection_status = connect(networkSocket, (struct sockaddr *) &server_address, sizeof(server_address));
    
    //Check if the connection_status is 0 or not
    if(connection_status == 0){
        printf("The connection is good\n");
    }else{
        printf("The connection status of %d indicates a bad connection.\n", connection_status);
    }

    //Allow the socket to receive data from the server
    char server_response[256];
    
    recv(networkSocket, &server_response, sizeof(server_response), 0);

    //Print the data that was recieved
    printf("Received data: %s\n", server_response);

    //Close the socket
    close(networkSocket);

    return 0;
}