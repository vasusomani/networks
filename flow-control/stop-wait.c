#include <stdio.h>
#include <stdlib.h>

void stopAndWaitProtocol(int totalFrames)
{
    int transmittedFrames = 0;
    for (int i = 1; i <= totalFrames;)
    {
        printf("Sending Frame %d...\n", i);
        transmittedFrames++;
        int acknowledgment = rand() % 3;
        if (acknowledgment != 0)
        {
            printf("Acknowledgment received for Frame %d.\n", i);
            i++;
        }
        else
        {
            printf("Timeout for Frame %d. Retransmitting...\n", i);
        }
        printf("\n");
    }
    printf("Total frames sent (including retransmissions): %d\n", transmittedFrames);
}
int main()
{
    int totalFrames;
    printf("Enter the total number of frames: ");
    scanf("%d", &totalFrames);
    stopAndWaitProtocol(totalFrames);
    return 0;
}