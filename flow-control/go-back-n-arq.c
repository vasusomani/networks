#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int transmitFrames(int windowSize, int totalFrames)
{
    int currFrame = 1;
    int totalTransmissions = 0;

    while (currFrame <= totalFrames)
    {
        int ackFrames = 0;

        // Sending frames in the current window
        for (int frame = currFrame; frame < currFrame + windowSize && frame <= totalFrames; frame++)
        {
            printf("Sending Frame %d...\n", frame);
            totalTransmissions++;
        }

        // Checking acknowledgments for the sent frames
        for (int frame = currFrame; frame < currFrame + windowSize && frame <= totalFrames; frame++)
        {
            int acknowledgment = rand() % 2; // Random acknowledgment (0 for success, 1 for timeout)

            if (acknowledgment == 0)
            {
                printf("Acknowledgment received for Frame %d.\n", frame);
                ackFrames++;
            }
            else
            {
                printf("Timeout for Frame %d. Retransmitting...\n", frame);
                break; // Stop and retransmit the remaining frames in the window
            }
        }

        printf("\n");

        // Move the current frame index forward by the number of acknowledged frames
        currFrame += ackFrames;
    }

    return totalTransmissions;
}

int main()
{
    int totalFrames, windowSize;
    srand(time(NULL));

    // Input: total number of frames and window size
    printf("Enter the total number of frames: ");
    scanf("%d", &totalFrames);
    printf("Enter the window size: ");
    scanf("%d", &windowSize);

    // Start the frame transmission process and get the total number of transmissions
    int totalTransmissions = transmitFrames(windowSize, totalFrames);

    // Output the total number of transmissions
    printf("Total number of frames sent (including retransmissions): %d\n", totalTransmissions);

    return 0;
}
