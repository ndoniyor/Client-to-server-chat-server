#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
    char client_data[256];
    char server_data[256];
    int server_socket, port_num;
    char exit_phrase[] = "/exit\n";
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    printf("Enter port number (>2000)");
    scanf("%d",&port_num);
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET; //specify family address
    server_address.sin_port = htons(port_num);  //specify connection port
    server_address.sin_addr.s_addr = INADDR_ANY;  //ip add = 0.0.0.0 for local connections

    int client_socket;

    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
    listen(server_socket, 5);   
    client_socket = accept(server_socket, NULL, NULL);
    printf ("Client has connected to the server.\n");

    while(1){ //connection has been established and chat link will run until stopped by user
        printf("Awaiting client response...\n");
        recv(client_socket, &client_data, sizeof(client_data), 0);
        if(strcmp(client_data, exit_phrase)==0){
            printf("Client has exit the session\n");
            break;
        }
        printf("Client: %s\n", client_data);

        printf("Response: ");
        fgets(server_data, 256, stdin);
        send(client_socket, server_data, sizeof(server_data), 0);
        if(strcmp(server_data, exit_phrase)==0){
            printf("Host has disconnected the session\n");
            break;
        }
    }


}