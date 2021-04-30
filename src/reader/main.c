#include "../shared.h"
#include "reader.h"

int main(int argc, char **argv)
{
    // Check if the category is entered, show an error message if not
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s [category type] (1 - Student, 2 - Azeri, 3 - French)\n", argv[0]);
        exit(0);
    }

    // Generate unique key
    key_t key = ftok("progfile", 20);

    // Create a message queue and return id
    int msg_id = msgget(key, 0666 | IPC_CREAT);

    // Read and print recipes of given type
    printf("Recipes received of type %s:\n\n", argv[1]);
    read_recipes(msg_id, atoi(argv[1]));

    return 0;
}