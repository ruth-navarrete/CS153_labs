#include "types.h"
#include "stat.h"
#include "user.h"

int main (int argc, char *argv[]) {
    printf(1, "\nStart waitpid test\n");
    int child_pid = 0, grandkid_pid = 0;
    int child_status, grandkid_status;

    child_pid = fork();
    if (child_pid == -1) {
        printf(1, "error: fork1 failed . . . terminating and exiting\n");
        exit();
        return 0;
    }

    if (child_pid) { // parent process
        printf(1, "In parent process, PID: %d\n", getpid());
        printf(1, "Waiting for child process to terminate\n");
        if (waitpid(child_pid, &child_status, 0) > 0) {
            printf(1, "Child process terminated with status %d\n", child_status);
        }
        else {
            printf(1, "error: exit1 failed . . . terminating and exiting\n");
            exit();
            return 0;
        }
    }
    else { // child process
        printf(1, "In child process, PID: %d, status: %d\n", getpid(), child_status);
        grandkid_pid = fork();
        if (grandkid_pid == -1) {
            printf(1, "error: fork2 failed . . . terminating and exiting\n");
            exit();
            return 0;
        }

        if (grandkid_pid) { // child process
            printf(1, "Waiting for grandchild process to terminate\n");
            if (waitpid(grandkid_pid, &grandkid_status, 0) > 0) {
                 printf(1, "Grandchild process terminated with status %d\n", grandkid_status);
            }
            else {
                printf(1, "error: exit2 failed . . . terminating and exiting\n");
                exit();
                return 0;
            }
        }
        else { // grandkid process
            printf(1, "In grandchild process, PID: %d, status: %d\n", getpid(), grandkid_status);
        }
    }
    if (child_pid) {
        printf(1, "End waitpid test\n");
    }
    exit();
    return 0;
}
