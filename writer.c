#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/ipc.h>

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

// A function to write recipe to message queue
void write_recipes(int, recipe_category);

// A function to read file and store its content
int read_file(char[], char *);

// Existing recipe categories
recipe_category arr[] = {{1, "Student"}, {2, "Azeri"}, {3, "French"}};

int main(int argc, char **argv)
{
    // Generate unique key
    key_t key = ftok("recipes", 19);

    // Create a message queue and return id
    int msg_id = msgget(key, 0666 | IPC_CREAT);

    // Iterate through the categories and write recipes
    for (int i = 0; i < N_ARR(arr); i++)
        write_recipes(msg_id, arr[i]);

    return 0;
}

void write_recipes(int msg_id, recipe_category recipe)
{
    // Declare message buffer
    msg_buffer msg;

    // Declare variables to open directory of given category type
    DIR *d;
    struct dirent *dir;

    // Path to the directory
    char dir_path[50];
    sprintf(dir_path, "recipes/%s", recipe.category);
    d = opendir(dir_path);

    // Check if directory exists
    if (d)
    {
        // Iterate through directory files
        while ((dir = readdir(d)))
        {
            // Do not read hidden files
            if (dir->d_name[0] != '.')
            {
                // Path to the file
                char file_path[300];
                sprintf(file_path, "%s/%s", dir_path, dir->d_name);

                // Read file and store to message text
                read_file(msg.text, file_path);
                msg.type = recipe.type;

                // Send the message, show an error if msgsnd fails
                if (msgsnd(msg_id, &msg, strlen(msg.text), 0) == -1)
                {
                    fprintf(stderr, "msgsnd failed\n");
                    exit(-1);
                }

                printf("Recipe of type %ld has been sent\n", msg.type);
            }
        }

        closedir(d);
    }
}

int read_file(char out[], char *path)
{
    FILE *fptr = fopen(path, "r");
    char ch;
    int i = 0;

    // Check if file exists
    if (fptr)
    {
        while ((ch = fgetc(fptr)) != EOF)
            out[i++] = ch;
        out[i] = '\0';

        fclose(fptr);
    }
}