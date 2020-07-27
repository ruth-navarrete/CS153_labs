#include "types.h"
#include "stat.h"
#include "user.h"

int main (int argc, char *argv[]) {
    int pid = 0;

    printf(1, "\nStart update priority test\n");
    printf(1, "PID: %d, initial priority: 7\n", getpid());
    printf(1, "Default priority is 7. Will change priority to priority 0\n");

    updatePriority(getpid(), 0);

    printf(1, "Same PID: %d, new priority: 0\n", getpid());
//
    printf(1, "\nStart aging priority test\n");
    printf(1, "Parent PID: %d, initial priority: 0\n", getpid());
    printf(1, "Current priority is 0. Will change priority to priority 7\nChildren inherit priority\n");

    updatePriority(getpid(), 7);

    printf(1, "Same PID: %d, new priority: 7\n", getpid());
    printf(1, "Prep fork\n\tParent process will have priority 7\n\tChild process's priority will be changed to 2\n\tThis means the child process will be done prior to the parent\nForking\n");

    pid = fork();
    if (pid == -1) {
        printf(1, "error: fork1 failed . . . terminating and exiting\n");
        exit();
    }

    if (pid) { // parent process
        printf(1, "Parent process, priority 7\n");

        int i;
        for (i = 0; i < 100; i++) {
            printf(1, "%d ", i);
        }
    }
    else { // child process
        updatePriority(getpid(), 2);
        printf(1, "Child process, priority 2\n");

        int j;
        for (j = 0; j > -10; j--) {
            printf(1, "%d ", j);
        }
        exit();
        return 0;
    }
    wait();
    printf(1, "\n");
    exit();
    return 0;
}
