#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

// A global variable to store message id
int MSG_ID;

// A function to read category from message queue
void read_recipes(int);