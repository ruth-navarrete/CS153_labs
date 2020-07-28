#include "types.h"
#include "stat.h"
#include "user.h"

int main (int argc, char *argv[]) {
    int pid1 = 0, status1 = 0, pid2 = 0, status2 = 0;

    printf(1, "\nStart update priority test\n");
    printf(1, "PID: %d, initial priority: 7\n", getpid());
    printf(1, "Default priority is 7. Will change priority to priority 0\n");

    updatePriority(getpid(), 0);

    printf(1, "Same PID: %d, new priority: 0\n", getpid());
//
    printf(1, "\nStart aging priority test\n");
    printf(1, "Parent PID: %d, initial priority: 0\n", getpid());
    printf(1, "Change priority to priority 5\nChildren will inherit priority\n");

    updatePriority(getpid(), 5);
 
    printf(1, "Same PID: %d, new priority: 5\n", getpid());
    printf(1, "Forking 4 children\n");

    pid1 = fork();
    if (!pid1) {
        pid2 = fork();
    }

    if ((pid1 == -1) || (pid2 == -1)) {
        printf(1, "error: fork1 failed . . . terminating and exiting\n");
        exit();
    }

    if (pid1) { // parent process
        updatePriority(getpid(), 9);
        printf(1, "Parent process, priority 9     ");
        char k;
        for (k = 'a'; k < 'z'; k++) {
            printf(1, "%c ", k);
        }
        printf(1, "\n");
    }
    else if (!pid1 && pid2) { // child
        printf(1, "Child1 process, priority 5    ");

        char i;
        for (i = 'a'; i < 'z'; i++) {
            printf(1, "%c ", i);
        }
        printf(1, "\n");
        waitpid(pid2, &status2, 0);
        exit();
        return 0;
    }
    else { // grandchild
        updatePriority(getpid(), 6);
        printf(1, "Child2 process, priority 6    ");

        char j;
        for (j = 'a'; j < 'z'; j++) {
            printf(1, "%c ", j);
        }
        printf(1, "\n");
        exit();
        return 0;
    }

    waitpid(pid1, &status1, 0);
    printf(1, "\n");
    exit();
    return 0;
}
