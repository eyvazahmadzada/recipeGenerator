#include "../shared.h"
#include "reader.h"

// A global variable to store message id
int MSG_ID;

// Existing recipe categories
recipe_category arr[] = {{1, SIGINT, "Student"}, {2, SIGQUIT, "Azeri"}, {3, SIGTERM, "French"}};

// A function to handle received signals
void sig_handler(int);

int main()
{
    // Generate unique key
    key_t key = ftok("recipes", 10);

    // Create a message queue and return id
    MSG_ID = msgget(key, 0666 | IPC_CREAT);

    // Print process ID for the client to send signals
    printf("Process ID: %d\n", getpid());

    // Iterate through the expected signals and handle them
    for (int i = 0; i < N_ARR(arr); i++)
    {
        struct sigaction sa;
        sa.sa_handler = &sig_handler;
        sigaction(arr[i].signal, &sa, NULL);
    }

    // Wait for the signals
    printf("Waiting for the signals...\n");
    while (1)
        sleep(1);

    return 0;
}

void sig_handler(int signal)
{
    // Iterate through the signal category array and get category that is sent by client
    for (int i = 0; i < N_ARR(arr); i++)
    {
        // If the received signal is found, read recipes and stop the iteration
        if (arr[i].signal == signal)
        {
            read_recipes(MSG_ID, arr[i].type);
            break;
        }
    }
}