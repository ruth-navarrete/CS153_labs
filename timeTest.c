#include "types.h"
#include "stat.h"
#include "user.h"

int main (int argc, char* argv[]) {

	int pid1, pid2 = 0;
	int time1, time2 = 0;
	int status1, status2 = 0;

	printf(1, "\nStart timing test\n"); 

	pid1 = fork();
	if (!pid1)
		pid2 = fork();
	
	//build a number of forks to show the wait/turnaround times
	//have children to do printing or anything (adding nop instructions)
	//print out the pid to know which child is running and show the waiting/turn time 

	if (pid1) {
		time1 = turnaroundTime(getpid());
		printf(1,"\nProcess 1: pid is %d, turnaround time is %d \n", getpid(),time1);
		
		time2 = waitingTime(getpid());
		printf(1,"\nthe waiting time for the process was %d \n", time2);
	}
	else if (!pid1 && pid2) 
	{
		time1 = turnaroundTime(getpid());
		printf(1,"\nProcess 2: pid is %d, turnaround time is %d \n", getpid(),time1);
		
		time2 = waitingTime(getpid());
		printf(1,"\nthe waiting time for this process is %d \n", time2);
		waitpid(pid2, &status2, 0);
		exit();
		return 0;
		
	}
	else 
	{
		time1 = turnaroundTime(getpid());
		printf(1,"\nProcess 3: pid is %d, turnaround time is %d \n", getpid(),time1);
		
		time2 = waitingTime(getpid());
		printf(1,"\nthe waiting time for the process was %d \n", time2);
		exit();
		return 0;
	}


	waitpid(pid1,&status1,0);
	printf(1,"\n");
	exit();
	return 0;

}
