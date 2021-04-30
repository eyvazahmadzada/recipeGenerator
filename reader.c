#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Max number of bytes
#define MAX 10000

// A macro to find the size of a category array
#define N_ARR(t) sizeof(t) / sizeof(recipe_category)

// A structure to store message buffer
typedef struct
{
    long type;
    char text[MAX];
} msg_buffer;

// A structure to store recipe categories
typedef struct
{
    int type;
    char *category;
} recipe_category;

// A function to read category from message queue
void read_recipes(int, int);

// Existing recipe categories
recipe_category arr[] = {{1, "Student"}, {2, "Azeri"}, {3, "French"}};

int main(int argc, char **argv)
{
    // Check if the category is entered, show an error message if not
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s category(Azeri, French or Student)\n", argv[0]);
        exit(0);
    }

    // Generate unique key
    key_t key = ftok("recipes", 19);

    // Create a message queue and return id
    int msg_id = msgget(key, 0666 | IPC_CREAT);

    // Default recipe type
    int type = 1;

    // Iterate through the recipe categories and find added type
    for (int i = 0; i < N_ARR(arr); i++)
    {
        if (arr[i].category == argv[1])
        {
            type = arr[i].type;
            break;
        }
    }

    // Read and print recipes of given type
    printf("Messages received of type %d (%s):\n\n", type, argv[1]);
    read_recipes(msg_id, type);

    return 0;
}

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