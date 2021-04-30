#include "../shared.h"
#include "reader.h"

void read_recipes(int msg_id, int category)
{
    // Declare a message buffer
    msg_buffer msg;

    int length;

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