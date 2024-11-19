#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 8081
#define BUFFER_SIZE 100

void generate_hamming_code(char *data, int *encoded)
{
    int dataLength = strlen(data);
    int codeLength = dataLength + 3;
    int dataIndex = 0, parityIndex = 0;

    for (int i = 0; i < codeLength; i++)
    {
        if (i == ((int)pow(2, parityIndex) - 1))
            continue;
        else
        {
            encoded[i] = data[dataIndex++] - '0';
        }
    }

    encoded[6] = encoded[4] ^ encoded[2] ^ encoded[0];
    encoded[5] = encoded[4] ^ encoded[1] ^ encoded[0];
    encoded[3] = encoded[0] ^ encoded[2] ^ encoded[1];
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
            
        int res[7];
        generate_hamming_code(buffer, res);
        for (int i = 6; i >= 0; i--)
        {
            printf("%d", res[i]);
            write(client_fd, res, sizeof(res));
        }
    }
    close(server_fd);
    close(client_fd);
}
