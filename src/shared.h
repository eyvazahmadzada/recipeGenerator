#ifndef SHARED_H
#define SHARED_H

// Max number of bytes to be read or written
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

#endif