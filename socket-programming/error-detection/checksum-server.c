#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PORT 8082
#define SIZE 8

unsigned char calculateChecksum(const int data[], int size)
{
    unsigned int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += data[i];
    }
    while (sum >> 8)
    {
        sum = (sum & 0xFF) + (sum >> 8);
    }
    return ~sum;
}

int main()
{
    int socketFD, connFD, data[SIZE], receiverData[SIZE];
    struct sockaddr_in serverAddr;
    unsigned char receivedChecksum, calculatedChecksum, receiverChecksum;

    socketFD = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(PORT);

    bind(socketFD, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    listen(socketFD, 5);

    printf("Server listening...\n");

    connFD = accept(socketFD, NULL, NULL);
    if (connFD < 0)
    {
        printf("Server accept failed...\n");
        exit(0);
    }
    printf("Server accepted the client...\n");

    read(connFD, data, sizeof(data));
    read(connFD, &receivedChecksum, sizeof(receivedChecksum));

    calculatedChecksum = calculateChecksum(data, SIZE);
    printf("Checksum received from sender: %d\n", receivedChecksum);
    printf("Checksum calculated on server: %d\n", calculatedChecksum);

    if (receivedChecksum != calculatedChecksum)
    {
        printf("Error detected in sender data\n");
        char response[] = "Error detected in sender data";
        write(connFD, response, sizeof(response));
        close(connFD);
        close(socketFD);
        return 0;
    }

    read(connFD, receiverData, sizeof(receiverData));

    receiverChecksum = calculateChecksum(receiverData, SIZE);
    printf("Checksum calculated for receiver data: %d\n", receiverChecksum);

    if (receiverChecksum == receivedChecksum)
    {
        printf("No error detected in receiver data\n");
        char response[] = "No error in receiver data";
        write(connFD, response, sizeof(response));
    }
    else
    {
        printf("Error detected in receiver data\n");
        char response[] = "Error detected in receiver data";
        write(connFD, response, sizeof(response));
    }

    close(connFD);
    close(socketFD);
    return 0;
}
