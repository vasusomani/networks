#include <stdio.h>
#include <string.h>

void xorFun(char *encoded, const char *crc)
{
    int crcLength = strlen(crc);
    int encodedLength = strlen(encoded);
    int i = 0;

    while (i <= encodedLength - crcLength)
    {
        for (int j = 0; j < crcLength; j++)
        {
            encoded[i + j] = (encoded[i + j] == crc[j]) ? '0' : '1';
        }
        // find the next '1'
        while (i < encodedLength && encoded[i] != '1')
        {
            i++;
        }
    }
}

int main()
{
    char data[100], crc[20], encoded[120];

    printf("Enter the binary data: ");
    scanf("%s", data);

    printf("Enter the CRC polynomial: ");
    scanf("%s", crc);

    int dataLength = strlen(data);
    int crcLength = strlen(crc);

    // Append zero bits equal to the length of CRC - 1
    strcpy(encoded, data);
    for (int i = 0; i < crcLength - 1; i++)
    {
        encoded[dataLength + i] = '0';
    }
    encoded[dataLength + crcLength - 1] = '\0';

    // Perform the XOR operation
    xorFun(encoded, crc);

    // Extract the remainder (last crcLength-1 bits)
    char remainder[20];
    strncpy(remainder, encoded + dataLength, crcLength - 1);
    remainder[crcLength - 1] = '\0';

    // Print the encoded data (data + remainder)
    printf("Encoded data with CRC: %s%s\n", data, remainder);

    return 0;
}
