#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 100

int main()
{
    // Socket Creation
    int server_fd;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        printf("Socket Failed");
        return 1;
    }
    printf("Socket Success!\n");

    // Server Address
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind Socket
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Binding Failed");
        return 1;
    }

    // Listen Socket
    if (listen(server_fd, 1) < 0)
    {
        printf("Listen Failed");
        return 1;
    }
    printf("Server is listening on port %d\n", PORT);

    // Accept Connection
    int client_fd;
    struct sockaddr_in client_addr;
    socklen_t sock_len = sizeof(client_addr);
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &sock_len);
    if (client_fd < 0)
    {
        printf("Accept Failed");
        return 1;
    }
    printf("Accept Success!\n");

    // Handle Buffer
    char buffer[BUFFER_SIZE];
    while (1)
    {
        memset(buffer, 0, BUFFER_SIZE);
        read(client_fd, buffer, BUFFER_SIZE);
        printf("Client: %s", buffer);

        if (strncmp(buffer, "exit", 4) == 0)
            break;

        printf("Server(You): ");
        fgets(buffer, BUFFER_SIZE, stdin);
        write(client_fd, buffer, strlen(buffer));
    }
    close(client_fd);
    close(server_fd);
}