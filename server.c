#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// A macro to find the size of a category array
#define N_ARR(t) sizeof(t) / sizeof(RecipeCategory)

// A function to handle received signals
void sig_handler(int);

// A structure to store recipe categories
typedef struct
{
    int signal;
    char *category;
} RecipeCategory;

// Existing recipe categories
RecipeCategory arr[] = {{SIGINT, "Student"}, {SIGQUIT, "Azeri"}, {SIGTERM, "French"}};

int main()
{
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
        sleep(1000);

    return 0;
}

void sig_handler(int signal)
{
    // Iterate through the signal category array
    for (int i = 0; i < N_ARR(arr); i++)
    {
        // If the received signal is found, print category and stop the iteration
        if (arr[i].signal == signal)
        {
            printf("Recipe Category: %s\n", arr[i].category);
            break;
        }
    }
}