#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define QUEUE_SIZE 100

typedef struct {
    int items[QUEUE_SIZE];
    int front;
    int rear;
} Queue;

void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

int isFull(Queue *q) {
    return (q->rear + 1) % QUEUE_SIZE == q->front;
}

void enqueue(Queue *q, int value) {
    if (isFull(q)) {
        printf("Queue is full. Cannot enqueue %d\n", value);
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % QUEUE_SIZE;
    q->items[q->rear] = value;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1;
    }
    int item = q->items[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % QUEUE_SIZE;
    }
    return item;
}

void sendFrames(Queue *queue, int window_size, int total_frames, int *total_sent, int *frames_to_ack, int *frames_sent) {
    printf("\nSending frames:\n");
    *frames_sent = 0;
    for (int i = 0; i < window_size && !isEmpty(queue); i++) {
        int frame = dequeue(queue);
        printf("Sending Frame %d...\n", frame);
        (*total_sent)++;
        frames_to_ack[*frames_sent] = frame; // Track frames for acknowledgment
        (*frames_sent)++;
    }
}

void acknowledgeFrames(Queue *queue, int frames_sent, int *frames_to_ack, int *total_ack, int total_frames) {
    printf("\nAcknowledging frames:\n");
    for (int i = 0; i < frames_sent; i++) {
        int frame = frames_to_ack[i];
        int success = rand() % 2; // Simulate acknowledgment (0 for failure, 1 for success)

        if (success) {
            printf("Acknowledgment received for Frame %d.\n", frame);
            (*total_ack)++;
        } else {
            printf("Frame %d lost. Adding back to queue for retransmission.\n", frame);
            enqueue(queue, frame); // Re-enqueue lost frame
        }
    }
}

void transmission(int window_size, int total_frames) {
    Queue queue;
    initQueue(&queue);

    for (int i = 1; i <= total_frames; i++) {
        enqueue(&queue, i); // Enqueue all frames initially
    }

    int total_sent = 0;
    int total_ack = 0;
    int frames_to_ack[QUEUE_SIZE];
    int frames_sent;

    while (!isEmpty(&queue)) {
        sendFrames(&queue, window_size, total_frames, &total_sent, frames_to_ack, &frames_sent);
        acknowledgeFrames(&queue, frames_sent, frames_to_ack, &total_ack, total_frames);
    }

    printf("\nTransmission complete.\n");
    printf("Total frames sent: %d\n", total_sent);
    printf("Total frames acknowledged: %d\n", total_ack);
    printf("Total frames needing retransmission: %d\n", total_sent - total_ack);
}

int main() {
    int total_frames, window_size;
    srand(time(NULL));

    printf("Enter the total number of frames: ");
    scanf("%d", &total_frames);
    printf("Enter the Window Size: ");
    scanf("%d", &window_size);

    transmission(window_size, total_frames);

    return 0;
}
