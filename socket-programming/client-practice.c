#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 100

int main()
{
    // Socket Connection
    int client_fd;
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0)
    {
        printf("Socket Failed");
        return 1;
    }
    printf("Socket Success\n");

    // Server Address
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Connect
    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Connection Failed");
        return 1;
    }
    printf("Connection Success\n");

    // Handle Buffer
    char buffer[100];
    while (1)
    {
        memset(buffer, 0, BUFFER_SIZE);
        printf("Client (You): ");
        fgets(buffer, BUFFER_SIZE, stdin);
        write(client_fd, buffer, strlen(buffer));

        if (strncmp(buffer, "exit", 4) == 0)
            break;

        memset(buffer, 0, BUFFER_SIZE);
        read(client_fd, buffer, BUFFER_SIZE);
        printf("Server: %s", buffer);
    }
    close(client_fd);
}