#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// A function to read category from message queue
void read_recipes(int, int);