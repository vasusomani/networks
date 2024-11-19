#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverseString(char *str, char *revStr)
{
    int j = 0;
    for (int i = (strlen(str) - 1); i >= 0; i--)
    {
        revStr[j++] = str[i];
    }
}

int main()
{
    char data[100], res[100];
    scanf("%s", data);
    reverseString(data, res);
    printf("%s", res);
}