#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 8081
#define BUFFER_SIZE 100

void xorFun(char *data, char *crc)
{
    char encoded[100];
    for (int i = 0; i < strlen(data) + strlen(crc); i++)
    {
        if (i < strlen(data))
            encoded[i] = data[i];
        else
            encoded[i] = '0';
    }
    int crcLen = strlen(crc);
    int encLen = strlen(encoded);

    int i = 0;
    while (i <= encLen - crcLen)
    {
        for (int j = 0; j < crcLen; j++)
        {
            encoded[i + j] = (encoded[i + j] == '0') ? '1' : '0';
        }

        while (i < encLen && encoded[i] != '1')
            i++;
    }
    int j;
    for (j = 0; j < crcLen; j++)
    {
        data[j] = encoded[encLen - crcLen + j];
    }
    data[j] = '\0';
}

int main()
{
    // Socket Connection
    int server_fd;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        printf("Socket Failed");
        return 1;
    }
    printf("Socket Success\n");

    // Server Address
    struct sockaddr_in server_addr;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // Bind
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Bind Failed\n");
        return 1;
    }
    printf("Bind Success\n");

    // Listen
    if (listen(server_fd, 1) < 0)
    {
        printf("Listen Failed");
        return 1;
    }
    printf("Listen Success\n");

    // Accept Connection
    int client_fd;
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_fd < 0)
    {
        printf("Accept Connection Failed");
    }
    printf("Accept Success\n");

    // Handle Buffer
    char buffer[BUFFER_SIZE];
    while (1)
    {
        memset(buffer, 0, BUFFER_SIZE);
        read(client_fd, buffer, BUFFER_SIZE);
        printf("Client: %s", buffer);

        if (strncmp(buffer, "exit", 4) == 0)
            break;

        char data[100], crc[100];
        sscanf(buffer, "%s %s", data, crc);
        xorFun(data, crc);
        printf("Result: %s\n", data);
        write(client_fd, data, strlen(data));
    }
    close(server_fd);
    close(client_fd);
}
