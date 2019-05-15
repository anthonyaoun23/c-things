#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void doSomeWork(char *name)
{
    const int NUM_TIMES = 2;
    for (int i = 0; i < NUM_TIMES; i++) {
        sleep(rand() % 4);
        printf("Done pass %d for %s\n", i, name);
    }
}

int main(int argc, char *argv[])
{
    printf("I am %d\n", (int) getpid());

    pid_t pid = fork();
    // srand((int) pid);
    printf("fork returned: %d\n", (int) pid);

    if (pid < 0) {
        perror("Fork failed");
    } 
    if (pid == 0) {
        printf("I am the child with pid %d\n", (int) getpid());
        doSomeWork("Child\n");
        printf("Child exiting.\n");
        exit(30);
    }
    
    // Must be parent
    printf("I am the parent, waiting for child to end.\n");
    sleep(30); // Sleep for 30 seconds. Child process will finish and remain in <defunct> which means the process has finished but has not yet been waited on 
    // known as a zombie process. Use ps -a to see all processes in terminal
    //doSomeWork("Parent\n");
    int status = 0;
    pid_t childpid = wait(&status);
    printf("Parent knows child %d finished with status %d.\n", (int) childpid, status);    
    int childReturnedValue = WEXITSTATUS(status);
    printf("       Return value was %d\n", childReturnedValue);
    return 0;
}
