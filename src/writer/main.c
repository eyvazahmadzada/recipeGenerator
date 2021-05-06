#include "../shared.h"
#include "writer.h"

// Existing recipe categories
recipe_category arr[] = {{1, SIGINT, "Student"}, {2, SIGQUIT, "Azeri"}, {3, SIGTERM, "French"}};

int main(int argc, char **argv)
{
    // Check if the category is entered, show an error message if not
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s [PID of server] [category type] (1 - Student, 2 - Azeri, 3 - French)\n", argv[0]);
        exit(0);
    }

    // Generate unique key
    key_t key = ftok("recipes", 15);

    // Create a message queue and return id
    int msg_id = msgget(key, 0666 | IPC_CREAT);

    // Iterate through the categories and write recipes
    for (int i = 0; i < N_ARR(arr); i++)
        write_recipes(msg_id, arr[i]);

    // Find the signal of given category
    int signal;
    for (int i = 0; i < N_ARR(arr); i++)
    {
        if (arr[i].type == atoi(argv[2]))
        {
            signal = arr[i].signal;
            break;
        }
    }
    // Send the signal to the specified PID
    kill(atoi(argv[1]), signal);

    return 0;
}