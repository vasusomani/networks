#include <stdio.h>

// Function to calculate checksum
void calculate_checksum(char *binary)
{
    int len = strlen(binary);

    if (len % 2 != 0)
    {
        printf("Error: Binary string must have an even number of bits.\n");
        return;
    }

    int sum = 0;
    for (int i = 0; i < len; i += 2)
    {
        // Extract two bits at a time and interpret them as binary numbers
        int num = (binary[i] - '0') * 2 + (binary[i + 1] - '0');
        sum += num;
    }

    // Convert sum to binary and wrap around if exceeding 4 bits
    int checksum = (~sum) & 0xF;

    // Print the checksum result
    printf("Checksum: %04d\n", checksum);
}

int main()
{
    const int size = 8;
    int data[size];
    printf("Enter binary number: \n", );
    for (int i = 0; i < size; i++)
    {
        scanf("%s", data);
    }
    calculate_checksum(data);
    // char checksum = calculateChecksum(data, size);
    // printf("Checksum: %d\n", checksum);
    return 0;
}