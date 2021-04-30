#include "../shared.h"
#include "writer.h"

// Existing recipe categories
recipe_category arr[] = {{1, "Student"}, {2, "Azeri"}, {3, "French"}};

int main(int argc, char **argv)
{
    // Generate unique key
    key_t key = ftok("progfile", 20);

    // Create a message queue and return id
    int msg_id = msgget(key, 0666 | IPC_CREAT);

    // Iterate through the categories and write recipes
    for (int i = 0; i < N_ARR(arr); i++)
        write_recipes(msg_id, arr[i]);

    return 0;
}