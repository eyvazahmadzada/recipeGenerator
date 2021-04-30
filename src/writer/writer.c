#include "../shared.h"
#include "writer.h"

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

                printf("Recipe of type %d (%s) has been sent\n", recipe.type, recipe.category);
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