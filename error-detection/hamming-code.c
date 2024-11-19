#include <stdio.h>
#include <math.h>
#include <string.h>

#include <stdio.h>
#include <math.h>
#include <string.h>

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
    char data[32];

    printf("Please enter the Data Word (4 bits):\n");
    scanf("%s", data);

    int encoded[7];
    generate_hamming_code(data, encoded);


}
