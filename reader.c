#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Max number of bytes
#define MAX 10000

// A structure to store message buffer
typedef struct
{
    long type;
    char text[MAX];
} msg_buffer;

// A function to read category from message queue
void read_recipes(int, int);

int main(int argc, char **argv)
{
    // Check if the category is entered, show an error message if not
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s category type\n", argv[0]);
        exit(0);
    }

    // Generate unique key
    key_t key = ftok("recipes", 19);

    // Create a message queue and return id
    int msg_id = msgget(key, 0666 | IPC_CREAT);

    // Read recipes of given type
    read_recipes(msg_id, atoi(argv[1]));

    return 0;
}

void read_recipes(int msg_id, int category)
{
    // Declare a message buffer
    msg_buffer msg;

    int length;

    printf("Messages received of type %d:\n\n", category);

    // Iterate through the messages and print them
    while ((length = msgrcv(msg_id, &msg, MAX, category, 0)) > 0)
        printf("%s\n\n\n", msg.text);

    // Send the message, show an error if msgsnd fails
    if (length == -1)
    {
        fprintf(stderr, "msgrcv failed\n");
        exit(-1);
    }
}