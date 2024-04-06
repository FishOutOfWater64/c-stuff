#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];
    char recieved_bytes[] = "GET /path/file.html HTTP/1.0\nFrom: someuser@jmarshall.com\nUser-Agent: HTTPTool/1.0\n\n"; 
     
    buffer[sizeof(recieved_bytes)] = '\0';

    char *token;
    token = strtok(buffer, "\n");
    while (token != NULL) {
        printf("Recieved: %s\n", token);
        token = strtok(NULL, "\n");
    }
}