#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    // Check if the PID is entered, show an error message if not
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s PID\n", argv[0]);
        exit(0);
    }

    // List of the possible signals
    int signals[3] = {SIGINT, SIGQUIT, SIGTERM};

    // Set the random generator to a different starting point
    srand(time(0));

    for (int i = 0; i < 100; i++)
    {
        // Randomly select a signal and send it to the entered PID
        int ran_signal = signals[rand() % 3];
        printf("(%d) Sending signal %d to the server...\n", (i + 1), ran_signal);
        kill(atoi(argv[1]), ran_signal);

        // Sleep for a second
        sleep(1);
    }

    return 0;
}