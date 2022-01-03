#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
    int network_socket, port_num;
    char exit_phrase[] = "/exit\n";
    network_socket = socket(AF_INET, SOCK_STREAM, 0); //Creates endpoint for communication, returns socket file descriptor, which is set equal to internet_socket
    printf("Enter port number (>2000)");
    scanf("%d",&port_num);
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET; //specify family address
    server_address.sin_port = htons(port_num);  //specify connection port
    server_address.sin_addr.s_addr = INADDR_ANY;  //ip add = 0.0.0.0 for local connections
    int connection_status = connect(network_socket, (struct sockaddr*) &server_address, sizeof(server_address));
    if(connection_status == -1){
        printf("Connection failed.\n");
        return 0;
    }
    char client_data[256];
    char server_data[256];
    while(1){
        printf("Response: ");
        fgets(client_data, 256, stdin);
        send(network_socket, &client_data, sizeof(client_data), 0);
        if(strcmp(client_data, exit_phrase)==0){
            printf("You have left the session\n");
            break;
        }

        printf("Awaiting server response...\n");
        recv(network_socket, &server_data, sizeof(server_data), 0);
        if(strcmp(server_data, exit_phrase)==0){
            printf("Host has left the session\n");
            break;
        }
        printf("Server: %s\n", server_data);
    }
    return 0;
}