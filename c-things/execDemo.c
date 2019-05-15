#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    printf("execDemo: My PID is %d\n", getpid());

    // With L: comma seperated arguments
    // With V: Vector (i.e., an array of strings)
    // With P: include normal search path for executable
    char *args[] = {"./helloExec", "Hello", "World",NULL};
    // when exec is called, the currently running process will be replaced with a new image; the image of the file you pass to exec
    execvp(args[0], args);
    // any code after exec will not be ran unless there is an error
    return 0;
}