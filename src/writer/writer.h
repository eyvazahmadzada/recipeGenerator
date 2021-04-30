#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <dirent.h>
#include <string.h>

// A function to write recipe to message queue
void write_recipes(int, recipe_category);

// A function to read file and store its content
int read_file(char[], char *);