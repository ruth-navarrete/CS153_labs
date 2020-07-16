#include "types.h"
#include "stat.h"
#include "user.h"

int main (int argc, char *argv[]) {
    int waited_pid = 0;
    int child_pid = fork();
    int status;
    int i = 0 ;

    if (child_pid == -1) {
        printf(1, "fork failed. exiting\n");
        exit();
        return 0;
    }

    if (child_pid) {  // parent process
        printf(1, "Parent process, PID: %d", getpid());
        
        // loop to wait for child to terminate before parent
        for (i = 0; i < 10; i++) {
            waited_pid = waitpid(child_pid, &status, 0);

            if (waited_pid == -1) {
                printf(1, "waitpid error, exiting\n");
                exit();
                return 0;
            }
            else if (waited_pid == 0) {
                printf(1, "In parent process, waiting for child process to ternminate\n");
                sleep(1);
            }
            else {
                //printf(1, "Child has ended with status %d", status);
            }
        }
    }
    else {  // child process
        printf(1, "Child process, PID: %d", getpid());
        sleep(5); // let child terminate before parent
    }

    exit();
    return 0;
}
