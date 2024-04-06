#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8081
#define BUFFER_SIZE 1024

int main() {
    int server_socket, client_socket; 
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];
    int recieved_bytes;

    // Create socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed\n");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Socket binding failed\n");
        exit(EXIT_FAILURE);
    }
    
    // Listen for incoming connections
    if (listen(server_socket, 5)) {
        perror("Listen failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // Accept incoming connections
    if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len)) == -1) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    printf("Connection accepted from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    // // Recieve client data
    // int bytes_recieved;
    // while ((bytes_recieved = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
    //     buffer[bytes_recieved] = '\0';
    //     printf("Received: %s\n", buffer);

    //     // Echo data back to client
    //     if (send(client_socket, buffer, bytes_recieved, 0) == -1) {
    //         perror("Send failed\n");
    //         exit(EXIT_FAILURE);
    //     }
    // }

    // if (bytes_recieved == -1) {
    //     perror("Receive failed\n");
    //     exit(EXIT_FAILURE);
    // }

    if ((recieved_bytes = recv(server_socket, buffer, BUFFER_SIZE, 0)) == -1) {
        perror("Recieve failed\n");
        exit(EXIT_FAILURE);
    } else if (recieved_bytes == 0) {
        close(client_socket);
    } else {
        buffer[recieved_bytes] = '\0';

        char *token;
        token = strtok(buffer, "\n");
        while (token != NULL) {
            printf("Recieved: %s\n", token);
            token = strtok(NULL, "\n");
        }
    }
    
    close(server_socket);
    close(client_socket);

    return 0;
}
