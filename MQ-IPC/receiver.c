#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <fcntl.h>
#include "common.h"

int main() {
    mqd_t mq;
    struct mq_attr attr;
    char buffer[MAX_SIZE + 1];

    // Open the message queue for reading
    mq = mq_open(QUEUE_NAME, O_RDONLY);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    // Get the message queue attributes
    if (mq_getattr(mq, &attr) == -1) {
        perror("mq_getattr");
        mq_close(mq);
        exit(EXIT_FAILURE);
    }

    // Receive the message from the queue
    if (mq_receive(mq, buffer, attr.mq_msgsize, NULL) == -1) {
        perror("mq_receive");
        mq_close(mq);
        exit(EXIT_FAILURE);
    }

    // Null-terminate the received message and print it
    buffer[attr.mq_msgsize] = '\0';
    printf("Receiver: Message received: %s\n", buffer);

    // Close and remove the message queue
    mq_close(mq);
    mq_unlink(QUEUE_NAME); // Remove the queue

    return 0;
}
