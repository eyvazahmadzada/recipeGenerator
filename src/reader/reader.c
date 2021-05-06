#include "../shared.h"
#include "reader.h"

void read_recipes(int category)
{

    // Declare a message buffer
    msg_buffer msg;

    int length;

    printf("Recipes received of type %d:\n\n", category);

    // Iterate through the messages and print them
    while ((length = msgrcv(MSG_ID, &msg, MAX, category, 0)) > 0)
        printf("%s\n\n\n", msg.text);

    // Send the message, show an error if msgsnd fails
    if (length == -1)
    {
        fprintf(stderr, "msgrcv failed\n");
        exit(-1);
    }
}